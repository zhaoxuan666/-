#include <iostream>
#include <string>
#include <vector>
using namespace std;
bool IsPopOrder(vector<int> pushV, vector<int> popV)
{
	//判断是否是pushV的出栈序列 可以创建一个临时空间
	vector<int> s;
	//vector支持随机访问
	int j = 0;
	for (int i = 0; i < pushV.size(); i++)
	{
		s.push_back(pushV[i]);//首先添加元素
		while (j<popV.size()&&popV[j]==s.back())//当pooV的元素与s尾部元素相同时 ”退栈“
		{
			s.pop_back();
			j++;
		}
	}
	return s.empty();
}
int main()
{
	vector<int> pushV = { 1, 2, 3, 4, 5 };
	vector<int>popV = { 4, 5, 3, 2,1 };
	cout<<IsPopOrder(pushV, popV);
	system("pause");
	
}