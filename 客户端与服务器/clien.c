#include <stdlib.h>
#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<errno.h>
#include<sys/types.h>
#define SERVER_PORT 1234
#define SERVER_IP "127.0.0.1"

int main(int argc,char *argv[])
{
  if(argc!=2)
  {
    printf("客户端 ip\n");
    return 1;
  }
  char *str=argv[1];
  char buf[1024];
  memset(buf,'\0',sizeof(buf));
  struct sockaddr_in server;
  int sock=socket(AF_INET,SOCK_STREAM,0);
  bzero(&server,sizeof(server));
  server.sin_family=AF_INET;
  inet_pton(AF_INET,SERVER_IP,&server.sin_addr);
  server.sin_port=htons(SERVER_PORT);

  int ret=connect(sock,(struct sockaddr*)&server,sizeof(server));
  if(ret<0)
  {
    printf("连接失败！！\n");
    return 1;
  }
  printf("连接成功！！！\n");
  while(1)
  {
    printf("客户端：");
    fgets(buf,sizeof(buf),stdin);
    buf[strlen(buf)-1]='\0';
    write(sock,buf,sizeof(buf));
    if(strncasecmp(buf,"quit",4)==0)
    {
      printf("退出！\n");
      break;
    }
    printf("请等待。。。\n");
    read(sock,buf,sizeof(buf));
    printf("服务器：%s\n",buf);

    
  }
  close(sock);

}
