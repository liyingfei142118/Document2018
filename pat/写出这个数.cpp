/*����һ����Ȼ��n���������λ����֮�ͣ��ú���ƴ��д���͵�ÿһλ���֡�
�����ʽ��ÿ�������������1��������������������Ȼ��n��ֵ�����ﱣ֤nС��10^100��
�����ʽ����һ�������n�ĸ�λ����֮�͵�ÿһλ��ƴ�����ּ���1 �ո񣬵�һ�������һ��ƴ�����ֺ�û�пո�
����������
1234567890987654321123456789
���������
yi san wu*/
#include<iostream>
using namespace std;
#include<string.h>
int main()
{
	char n[101];
	cin>>n;
	int s=strlen(n);
	long int count=0;
	for(int i=0;i<s;i++)
	{
		count+=n[i]-'0';
	}	 
	 char a[101];
	 int t=0;
	 
	 while(count!=0)
	 {
	 	int a1=count%10;
	 	count=count/10;
	 	a[t]=a1+'0';
	 	t++;
	 }
	 int j=t;
	 while(j>=0)
	 {
	 	
	 	switch(a[j]-'0')
		 {
			case 0:
				cout<<"ling";
				if(j>0)
				 {
				 	cout<<" ";
				 }
				break;
			case 1:
				cout<<"yi";
				if(j>0)
				 {
				 	cout<<" ";
				 }
		 		break;
			case 2:
				cout<<"er";
				if(j>0)
				 {
				 	cout<<" ";
				 }
		 		break;
			case 3:
				cout<<"san";
				if(j>0)
				 {
				 	cout<<" ";
				 }
		 		break;
			case 4:
				cout<<"si";
				if(j>0)
				 {
				 	cout<<" ";
				 }
		 		break;
			case 5:
				cout<<"wu";
				if(j>0)
				 {
				 	cout<<" ";
				 }
		 		break;
			case 6:
				cout<<"liu";
				if(j>0)
				 {
				 	cout<<" ";
				 }
		 		break;
			case 7:
				cout<<"qi";
				if(j>0)
				 {
				 	cout<<" ";
				 }
		 		break;
			case 8:
				cout<<"ba";
				if(j>0)
				 {
				 	cout<<" ";
				 }
		 		break;
			case 9:
				cout<<"jiu";
				if(j>0)
				 {
				 	cout<<" ";
				 }
		 		break;	
		}
		j--;

	 }
}
