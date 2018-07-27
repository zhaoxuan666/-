class Solution {
public:
    int Add(int num1, int num2)
    {
        //可以采用位运算（相同为0相异为1）可以算出每一位的加  但是不进位
        
        //用俩数 与 并且向左移1位 进位  当数为0时说明没有进位
        
        do{   int n=num1^num2;
            int m=(num1&num2)<<1;
            num1=n;
            num2=m;
        }while(num2!=0);
        return num1;
    }
};