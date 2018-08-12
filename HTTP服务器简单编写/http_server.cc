#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
typedef struct sockaddr sockaddr;
typedef struct sockaddr_in sockaddr_in;

int ReadLine(int sock,char buf[],ssizr_t size)
{//一次从sock中读取一行数据 ，放到buf  失败返回-1
	//1,从sock一次度一个字符
	char c='\0';
	ssizr_t i=0;//当前读了多少个
	while(i < size-1 && c != '\n')
	{
		ssizr_t read_size=recv(sock,&c,1,0);
		if(read_size<0)
		{
			return -1;
		}
		if(read_size==0)
		{//预期要读 \n 还没读到 就读到了EOF 这样认为失败
			return -1;
		}
		if (c=='\r')
		{
			/*判断下个是否为\n*/
			recv(sock,&c,1,MSG_PEEK)//MSG_PEEK是从内核中i哦那个的缓冲区读数据，读到的数据不会从缓冲区删除
			if(c=='\n')
			{
				//此时分隔符为\r\n
				recv(sock,&c,1,0);
			}else{
				//当前是分隔符确定是\r, 转换为\n
				c='\n';
			}
		}
		//只要c读到了\r if后都变成\n
		buf[i++]=c;
	}
	buf[i]='\0';
	return i;//i为真正放缓冲区的个数
	//2.如果读到换行\n 就返回
	//\n \r \r\n
}
int Split(char input[],char *split_char,char *output[],int output_size)//	切分函数
{
	//使用strtok函数
	char *pch;
	int i=0;
	//pch=strtok(input,split_char);
	char *tmp=NULL;//保存临时的解决线程不安全
	pch=strtok_r(input,split_char,&tmp);
	while(pch!=NULL)
	{
		if(i>=output_size)
		{
			return i;
		}
		output[i++]=pch;
		pch=strtok_r(NULL,split_char,&tmp);
	}
	return i;
}
//解析首行
int ParseFirstLine(char first_line[],char ** p_url,char **p_method)//二级指针为了修改指向
{
	//把首行按照空格进行切分
	char *tok[10];

	int tok_size=Split(first_line," ",tok,10);
	if (tok_size!=3)
	{
		/* code */
		printf("Split fail %d\n",tok_size);
		return -1;
	}
	*p_method=tok[0];
	*p_url=tok[1];
	return 0;
}
int ParseQueryString(char *url,char **p_url_path,char **p_query_string)
{
	char *p=url;
	*p_url_path=url;
	for (;*p!='\0' ; ++p)
	{
		/* code */
		if(*p=='?')
		{
			*p='\0';
			*p_query_string=p+1;
			return 0;
		}
	}
	*p_query_string=NULL;
	//循环结束都没找到? 这个亲求不带query_string
	return 0;
}
 int ParsHeader(int sock,int *content_length)
 {
 	//1.循环从socket中读取一行
 	//2.判定当前行是不是conten_length
 	//读到空行结束
 	char buf[SIZE]={0};
 	while(1)
 	{
 		ssizr_t read_size=ReadLine(sock,buf,sizeof(buf));
 		if (read_size<=0)
 		{
 			return -1;
 			/* code */
 		}
 		//处理读完的情况
 		if (strcmp(buf,"\n")==0)
 		{
 			/* code */
 			return 0;
 		}
 		//处理读到的数据是不是content-length
 		if (content_length!=NULL && strncmp(buf,"Content-Length: ",16)==0)
 		{
 				*content_length=atoi(buf+16);

 		}
 	}
 	return 0;
 }
 void Hander404(int sock)
 {
 	//构造一i个完整的HHTTP响应
 	//状态吗 404
 	//body部分应该也是错误页面
 	const char* first_line="HTTP/1.1 404 Not Found\n";
 	const char* black_line="\n";
 	const char* type_line="Content-Type: text/html;charset=utf-8\n";
 	const char* html="<h1>页面没找到</h1>";
 	send(sock,first_line,strlen(first_line),0);
 	send(sock,type_line,strlen(type_line),0);
 	send(sock,black_line,strlen(black_line),0);//空行
 	send(sock,html,strlen(html),0);
 	return;
 }
int IsDir(const char* file_path)
{
	struct stat st;
	int ret=stat(file_path,&st);
	if(ret<0)
	{
		return 0;
	}
	if(S_ISDIR(st.st_mode))
	{
		return 1;
	}
	return 0;
}
 void HanderFilePath(const char*url_path,char file_path[])
 {
 	//给url_path加上前缀（http服务器的根目录）
 	//url_path=> /index.html
 	//file_path=> ./wwwroot/index.html
 	sprintf(file_path,"./wwwroot%s",url_path);
 	//url_path如果是目录，则追加一个index.html
 	if (file_path[strlen(file_path)-1]=='/')
 	{
 		srtcat(file_path,"index.html");
 	}
 	//例如url_path => /image
 	if(IsDir(file_path))//判断是文件还是目录
 	{
 		strcat(file_path,"/index.html");
 	}
 	return;
 }
 int HandlerStaticFile(int sock,Request *req)
 {
 	//1.根据url_path获取到文件在服务器上的真实路劲
 	char file_path[SIZE]={0};
 	HanderFilePath(req->url_path,file_path);
 	//2.读取文件，把文件的内容直接写到socket之中
 	int err_code=WriteStaticFile(sock,file_path);
 	return err_code;
 }
void HeadlerRequest(int new_sock)
{
	int err_code=200;
	//1.读取解析请求
	Request req;
	memset(&req,0,sizof(req));
		//a.从socket中读出首行
	if(ReadLine(new_sock,req.fist_line,sizof(req.fist_line))<0)
	{
		//读取失败
		err_code=404;
		goto END;

	}
		//b.首行读完解析首行，从中解析出url和method
	if(ParseFirstLine(req.fist_line,&req.url,&req.method)<0)
	{
		//失败处理
		err_code=404;
		goto END;
	}
		//c.解析url从中得出url_path,url_string
	if(ParseQueryString(req.url,&req.url_path,&req.query_string)<0)
	{
		//
		err_code=404;
		goto END;
	}
		//d.处理head 丢弃了大部分header，只读取Content-length
	if(ParsHeader(sock,&req.content_length)<0)
	{
		//
		err_code=404;
		goto END;
	}

	//2.静态/动态方式生产页面,把生成从结果写到客户端上
	if (strcasecmp(req.method,"GET")==0   //不区分大小写
		&&req.query_string==NULL)
	{//a.如果请求是GET，并且没有query_string,呢么就返回静态页面
		err_code=HandlerStaticFile(new_sock,，&req);
	}else if(strcasecmp(req.method,"GET")==0
		&&req.query_string==NULL)
	{//b.如果请求是GET，并且有query_string,呢么就返回动态页面
		err_code=HandlerCGI();
	}else if(strcasecmp(req.method,"POSS")==0)
	{//c.如果是post请求（一定是带参数的，参数是通过body来传递给服务器的，也是动态页面
		err_code=HandlerCGI();
	}else
	{
		//错误处理
		err_code=404;
		goto END;
	}
	
	
	//错误处理：直接返回一个404的HTTP响应
END:
	if(err_code!=200)
	{
		Hander404(new_sock);
	}
	close(new_sock);

	return;
	
}

void* ThreadEntry(void* arg)
{
	//int64_t
	int new_sock=(int)arg;
	HeadlerRequest(new_sock);//使用进行完成具体的处理请求过程。方便改成多进程或IO多路复用
	return NULL;
}



void HttpServerStart(const char *ip,short port)
{
	int listen_sock=socket(AF_INET,SOCK_STREAM,0)
	if(listen_sock<0)
	{
		return;
	}
	//重用 TIME_WAIT 链接
	int opt=1;//服务器主动断开
	setsockopt(listen_sock,SOL_SOCKET,SO_REQUESADDR,&opt,sizeof(opt))//防止断开后要等待一段时间后 端口才被使用。直接关闭并使用
	
	sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_port=hyons(port);
	addr.sin_addr.s_addr=inet_addr(ip);
	int ret=bind(listen_sock,(sockaddr*)&addr,sizeof(addr))
	if(ret<0)
	{
		return;
	}
	printf("Serverinit ok\n");
	while(1)
	{
		sockaddr_in peer;
		socklen_t len=sizof(peer);
		int new_sock=accept(listen_sock,(sockaddr*)&peer,&len);
		if (new_sock<0)
		{
			/* code */
			return;
		}
	}
	//多线程实现
	pthread_t tid;
	pthread_create(&tid,NULL,ThreadEntry,(void)new_sock);
	pthread_detch(tid);//自动回收



















}
int main(int argc,char *argv[])
{
	if(argc!=3)
	{
		printf("Usage ./http_server [ip][]port\n");
		return 1;
	}
	HttpServerStart(arv[1],atoi(arv[2]));
	return 0;
}