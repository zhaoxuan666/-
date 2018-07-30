#include <stdio.h>
#include <Windows.h>
#include <stdarg.h>
int my_max(int num,...)
{
	int i=0;
	int m=0;
	va_list arg;
	va_start(arg,num);
		for (i=0;i<num;i++)
		{
			int var=va_arg(arg,int);
			if (var>m)
			{
				m=var;
			}
		}
		va_end(arg);
		return m;
}
int my_eve(int num,...)
{
	int sum=0;
	int i=0;
	va_list arg;
	va_start(arg,num);
	for (;i<num;i++)
	{
		sum+=va_arg(arg,int);
	}
	va_end(arg);
	return sum/num;
}
print(char *format, ...) 
{
	char *c;
	va_list arg;
	va_start(arg,format);
	while(*format){
		switch(*format)
		{
		case 'c':putchar(va_arg(arg,char));break;
		case 's':
			c=va_arg(arg,char*);
			while(*c)
				 {
					 putchar(*c);
					 c++;
				 }

			break;
		case 'd':printf("%d",va_arg(arg,int));break;
		default :  
			putchar(*format); 
		}
		format++;
	}
	va_end(arg);
}

int main()
{
	
	//int m=my_max(5,1,2,3,4,5);
	//int m=my_eve(5,1,2,3,4,5);
	//printf("%d",m);
	print("s ccc d.\n","hello",'b','i','t',100); 
	system("pause");
	return 0;
}