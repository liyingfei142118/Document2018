/*�����Ƕ��� dn Ϊ��dn = pn+1 - pn������ pi �ǵ�i��������
��Ȼ�� d1=1 �Ҷ���n>1�� dn ��ż����
�������Բ��롱��Ϊ�����������������Ҳ�Ϊ2����������
�ָ�������������N (< 105)������㲻����N���������������Եĸ�����
�����ʽ��ÿ�������������1����������������������N��
�����ʽ��ÿ���������������ռһ�У�������N���������������Եĸ�����
����������
20
���������
4*/
//��˼:�ҵ�С��n �����ڵĲ�Ϊ2�Ķ��� ��3��ʼ�� 
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

