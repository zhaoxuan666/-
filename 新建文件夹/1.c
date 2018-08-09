#include<vector>
#include <algorithm>
#include <iostream>
using namespace std;
int main()
{
    int n;
    cin >> n;
    vector<vector<int>>a;
    for (int i = 0; i < n; i++)
    {
        int m;
        int k;
        cin >> m;
         
        vector<int>b;
        for (int j = 0; j < m; j++)
        {
            cin >> k;
            b.push_back(k);
        }
        vector<int>c;
        //c.push_back(b[m - 1]);
        for (int j = m - 1; j >= 0;j--)
        {
             
            vector<int>::iterator mm = find(c.begin(), c.end(), b[j]);
            if (mm == c.end()) //√ª’“µΩ
                c.push_back(b[j]);
             
             
        }
         
        a.push_back(c);
    }
    for (int i = 0; i < n;i++)
    {
        int size1 = a[i].size();
        for (int j = 0; j < size1;j++)
            cout << a[i][j]<<" ";
        cout << endl;
    }
    //system("pause");
}