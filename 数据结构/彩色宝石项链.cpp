/*题目描述
有一条彩色宝石项链，是由很多种不同的宝石组成的，包括红宝石，蓝宝石，钻石，翡翠，珍珠等。
有一天国王把项链赏赐给了一个学者，并跟他说，你可以带走这条项链，
但是王后很喜欢红宝石，蓝宝石，紫水晶，翡翠和钻石这五种，我要你从项链中截取连续的一小段还给我，
这一段中必须包含所有的这五种宝石，剩下的部分你可以带走。如果无法找到则一个也无法带走。
请帮助学者找出如何切分项链才能够拿到最多的宝石。
输入描述:
我们用每种字符代表一种宝石，A表示红宝石，B表示蓝宝石，C代表紫水晶，D代表翡翠，E代表钻石，F代表玉石，G代表玻璃等等，
我们用一个全部为大写字母的字符序列表示项链的宝石序列，注意项链是首尾相接的。每行代表一种情况。
输出描述:
输出学者能够拿到的最多的宝石数量。每行一个
示例1
输入
ABCYDYE
ATTMBQECPD
输出
1
3*/
#include<iostream>
#include<string.h>
using namespace std;
#define max 100000
int search(char str[],int j,char c)
{
	int key=0;
	for(int k=j;;k++)
	 {
	 	if(k>=strlen(str))
	 	{
	 		k=0;
		 }
		 if(str[k]==c)
		 	{
		 		key=k;
		 		break;
			 }
	 }
	 return key;
}
int main()
{
	 char str[max];
	 cin>>str;
	 int len=strlen(str);
	 int f[len+1];//存放每个位置的保留长度 
	 for(int i=1;i<=len;i++)
	 {
	 	f[i]=0;
	 	int j=i-1;
	 	int t[6];
	 	for(int s=1;s<=5;s++)
			{
					t[s]=0;
			}
//根据当前元素j，找到最后一个元素位置t 
// 根据数组长度，求出 
	 	if((str[j]=='A')||(str[j]=='B')||(str[j]=='C')||(str[j]=='D')||(str[j]=='E'))
			{
				int m1=0,m2=-1;
//分别找到每个字母的位置 
				t[1]=search(str,j,'A');
				t[2]=search(str,j,'B');
				t[3]=search(str,j,'C');
				t[4]=search(str,j,'D');
				t[5]=search(str,j,'E');			
				
				for(int s=1;s<=5;s++)
				{
					if(t[s]>j)//最后元素位置在j后 
					{
						if(t[s]>m1)
							m1=t[s];
					}
					if(t[s]<j)//最后元素在j前 
					{
						if(t[s]>m2)
							m2=t[s];
					}
				}
				if(m2>=0)//如果最后元素位置在j前，即可以求出位置 
				{
					f[i]=j-m2-1;
				}
				else//如果最后元素位置在j后，根据数组长度即可以求出位置 
				{
					f[i]=len-(m1-j+1);	
				}
			}
	 	cout<<f[i]<<endl;
	 }
	 int temp=0;
for(int i=1;i<=len;i++)//找到最大值 
	 {
	 	if(f[i]>temp)
	 		temp=f[i];
	 }
	 cout<<"temp:"<<temp<<endl;
}
