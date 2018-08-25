#include <stdio.h>
#include <mysql/mysql.h>

int main()
{
	//1.获取quer_string
	char query_string[1024*4]={0};
	int ret=GetQueryString(query_string);
	if (ret<0)
	{
		fprintf(stderr, "GetQueryString faild\n");
		return 1;
	}
	char city[1024*4]={0};
	sscanf(query_string,"city=%s",city);

	//2.从数据库中获取时间差
	MYSQL* connect_fd=mysql_init(NULL);
	MYSQL* connect_ret=mysql_real_connect(connect_fd,"127.0.0.1","","studentDB",3306,NULL,0);
	if (connect_ret==NULL)
	{
		fprintf(stderr, "mysql connect failed\n");
		return 1;
	}
	fprintf(stderr, "mysql connect ok!\n");
	//2.拼装sql语句
	char sql[1024*4]={0}
	sprinft(sql,"select time from xinxi where city='%s'",city);//查一列
	//发送
	int ret=mysql_query(connect_fd,sql);
	if (ret<0)
	{
		fprintf(stderr, "mysql_query failed!%s\n",sql);
		return 1;
	}
	//4.读取遍历服务器返回的结果
	MYSQL_RES* result=mysql_store_result(connect_fd);
	if (result==NULL)
	{
		fprintf(stderr, "mysql_store_result failed\n");
		return 1;
	}
	
	//c.获取每个元素的具体值
	
	MYSQL_ROW row=mysql_fetch_row(result);
		if (row==NULL)
		{	
			fprintf(stderr, "mysql chaxun shibai\n");
			return 1;
		}
		double time_diff=atof(row[0]);
	mysql_close(connect_fd);
	//3.获取系统时间，根据时间差进行计算，得到对方城市的时间
	//当前时间戳
	time_t t=time(NULL);
	t+=time_diff*3600;
	struct tm* to=locaktime($t);
	//4.响应结果

	printf("<html>\n");
	printf("%02d:%02d", tp->tm_hour,tp->tm_min);
	printf("</html>\n");
}