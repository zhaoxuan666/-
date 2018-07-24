#include <stdio.h>
#include <Windows.h>
#include <iostream>
using namespace std;
int main()
{
	int a = 0;
	int b = 1;
	int c;
	int m;
	cin >> m;
	int con=0;
	while (1)
	{
		c = a + b;
		a = b;
		b = c;
		if (a==m||b==m)
		{
			break;
		}
		if (a < m&&m < b)
		{
			 con = (m - a)<(b - m) ? (m - a) : (b - m);
			 break;
		}
	}
	cout << con;
	system("pause");
	return 0;
	
}