/*读入一个自然数n，计算其各位数字之和，用汉语拼音写出和的每一位数字。
输入格式：每个测试输入包含1个测试用例，即给出自然数n的值。这里保证n小于10^100。
输出格式：在一行内输出n的各位数字之和的每一位，拼音数字间有1 空格，但一行中最后一个拼音数字后没有空格。
输入样例：
1234567890987654321123456789
输出样例：
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
