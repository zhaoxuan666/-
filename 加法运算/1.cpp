class Solution {
public:
    int Add(int num1, int num2)
    {
        //���Բ���λ���㣨��ͬΪ0����Ϊ1���������ÿһλ�ļ�  ���ǲ���λ
        
        //������ �� ����������1λ ��λ  ����Ϊ0ʱ˵��û�н�λ
        
        do{   int n=num1^num2;
            int m=(num1&num2)<<1;
            num1=n;
            num2=m;
        }while(num2!=0);
        return num1;
    }
};