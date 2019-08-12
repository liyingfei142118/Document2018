/*让我们用字母B来表示“百”、字母S表示“十”，
用“12...n”来表示个位数字n（<10），
换个格式来输出任一个不超过3位的正整数。
例如234应该被输出为BBSSS1234，
因为它有2个“百”、3个“十”、
以及个位的4。
输入格式：每个测试输入包含1个测试用例，给出正整数n（<1000）。
输出格式：每个测试用例的输出占一行，用规定的格式输出n。
输入样例1：
234
输出样例1：
BBSSS1234
输入样例2：
23
输出样例2：
SS123*/
#include<iostream>
using namespace std;

int main()
{
	int n;
	cin>>n;
	int c;
	c=n%10;
	n=n/10;
	if(n==0)
	{
		for(int i=1;i<=c;i++)
		{
			cout<<i;
		}
	}
	else
	{
			int t=n%10;
			n=n/10;
			if(n==0)
			{
				for(int j=1;j<=t;j++)
				{
					cout<<"S";
				}
				for(int i=1;i<=c;i++)
				{
					cout<<i;
				}
			}
			else
			{
				
				for(int j=1;j<=n;j++)
				{
					cout<<"B";
				}
				for(int k=1;k<=t;k++)
				{
					cout<<"S";
				}
				for(int i=1;i<=c;i++)
				{
					cout<<i;
				}
			}
	}
}
