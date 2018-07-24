#include <iostream>
using namespace std;
int main()
{
	int n;
	int a[100];
	int sum=0;
	cin >> n;
	for (int i = 0; i < n;i++)
	{
		cin >> a[i];
		sum += a[i];
	}
	if (sum%n!=0)
	{
		printf("%d",-1);
		return 0;
	}
	int ave = sum / n;
	int coun = 0;
	for (int i = 0; i < n;i++)
	{
		if (a[i]>ave)
		{
			if ((a[i]-ave)%2==1)
			{
				cout << -1;
				return 0;
			}
			int c = (a[i] - ave) / 2;
			coun += c;
		}
	}
	cout<< coun;
	system("pause");
}