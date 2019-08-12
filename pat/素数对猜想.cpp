/*让我们定义 dn 为：dn = pn+1 - pn，其中 pi 是第i个素数。
显然有 d1=1 且对于n>1有 dn 是偶数。
“素数对猜想”认为“存在无穷多对相邻且差为2的素数”。
现给定任意正整数N (< 105)，请计算不超过N的满足猜想的素数对的个数。
输入格式：每个测试输入包含1个测试用例，给出正整数N。
输出格式：每个测试用例的输出占一行，不超过N的满足猜想的素数对的个数。
输入样例：
20
输出样例：
4*/
//意思:找到小于n 且相邻的差为2的对数 从3开始找 
#include<iostream>
using namespace std;
int count=0;
int sushu(int s)
{
	int word=0;
	for(int	i=3;i<s;i=i+2)
	{
		if(s%i==0)
			word=1;
	}
	if(word==1)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
int Judge(int a,int b)
{
	int m=sushu(a);
	int n=sushu(b);
	//cout<<a<<" "<<b<<endl;
	//cout<<m<<" "<<n<<endl;
	if(n==1&&m==1)
	{
		if(b-a==2)
			return 1;
		else
			return 0;
	}
	else
		return 0;
}
int main()
{
	int n;
	cin>>n;
	int t=3;
	while(t<=n)
	{
		if(t+2<=n)
		{
			int key=Judge(t,t+2);
			if(key==1)
			{
				count++;
			}
			t+=2;
		}
		else
		{
			break;
		}
		
		
	}
	cout<<count;
}

