#include <iostream>
#include <string>
#include <vector>
using namespace std;
bool IsPopOrder(vector<int> pushV, vector<int> popV)
{
	//�ж��Ƿ���pushV�ĳ�ջ���� ���Դ���һ����ʱ�ռ�
	vector<int> s;
	//vector֧���������
	int j = 0;
	for (int i = 0; i < pushV.size(); i++)
	{
		s.push_back(pushV[i]);//�������Ԫ��
		while (j<popV.size()&&popV[j]==s.back())//��pooV��Ԫ����sβ��Ԫ����ͬʱ ����ջ��
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