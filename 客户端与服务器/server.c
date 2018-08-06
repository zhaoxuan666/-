#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<sys/epoll.h>

void ProcessConnet(int sockfd,int epoll_fd)
{
  struct sockaddr_in client_addr;
  socklen_t len=sizeof(client_addr);
  int connet_fd=accept(sockfd,(struct sockaddr*)&client_addr,&len);
  if(connet_fd<0)
  {
    perror("accept");
    return ;
  }
  printf("客户端 %s:%d 连接\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
  struct epoll_event ev;
  ev.data.fd=connet_fd;
  ev.events=EPOLLIN;
  int ret=epoll_ctl(epoll_fd,EPOLL_CTL_ADD,connet_fd,&ev);
  if(ret<0)
  {
    perror("epoll_ctl");
    return ;
  }
  return; 

}
void ProcessRequest(int connet_fd,int epoll_fd)
{
  char buf[1024]={0};
  ssize_t read_size=read(connet_fd,buf,sizeof(buf));
  if(read_size<0)
  {
    perror("read");
    return ;
  }
  if(read_size==0)
  {
    close(connet_fd);
    epoll_ctl(epoll_fd,EPOLL_CTL_DEL,connet_fd,NULL);
    printf("这个客户端退出！！\n");
    return;
  }
  printf("客户端：%s",buf);
  write(connet_fd,buf,strlen(buf));
}












int main(int argc,char *argv[])
{
  if(argc!=3)
  {
    printf("使用./  ip + 端口号");
    return 1;
  }
  struct sockaddr_in addr;
  addr.sin_addr.s_addr=inet_addr(argv[1]);
  addr.sin_port=htons(atoi(argv[2]));
  addr.sin_family=AF_INET;
  int sockfd=socket(AF_INET,SOCK_STREAM,0);
  if(sockfd<0)
  {
    perror("socket");
    return 1;
  }
  int ret=bind(sockfd,(struct sockaddr*)&addr,sizeof(addr));
  if(ret<0)
  {
    perror("bind");
    return 1;
  }
  ret=listen(sockfd,5);
  if(ret<0)
  {
    perror("listen");
    return 1;
  }
  //创建epoll
  int epoll_fd=epoll_create(10);
  if(epoll_fd<0)
  {
    perror("epoll_create");
    return 1;
  }
  //创建epoll事件
  struct epoll_event event;
  event.events=EPOLLIN;
  event.data.fd=sockfd;
  ret=epoll_ctl(epoll_fd,EPOLL_CTL_ADD,sockfd,&event);//注册事件
  if(ret<0)
  {
    perror("epoll_ctl");
    return 1;
  }
  for(;;)
  {
    struct epoll_event events[10];
    int size=epoll_wait(epoll_fd,events,sizeof(events)/sizeof(events[0]),-1);
    if(size<0)
    {
      perror("epoll_wait");
      return 1;
    }
    if(size==0)
    {
      printf("epoll 超时");
      continue;
    }
    for(int i=0;i<size;i++)
    {
      if(!(events[i].events&EPOLLIN))
      {
        continue;
      }
      if(events[i].data.fd==sockfd)
      {
        //处理监听
        ProcessConnet(sockfd,epoll_fd);
      }
      else{
        //处理connect_fd
        ProcessRequest(events[i].data.fd,epoll_fd);
      }
    }
  }
}
