/*题目描述
给定一个十进制的正整数number，选择从里面去掉一部分数字，希望保留下来的数字组成的正整数最大。
输入描述:
输入为两行内容，第一行是正整数number，1 ≤ length(number) ≤ 50000。
第二行是希望去掉的数字数量cnt 1 ≤ cnt < length(number)。
输出描述:
输出保留下来的结果。
示例1
输入
325 1
输出
35*/
//贪心策略：
//每删一次 从右边遍历，如果出现升序，删除最小那个 
#include<iostream>
#include<string.h>
using namespace std;
#define max 50000
void del(char *str)
{
	int key=0;//判断到最后一个数字  是否删了数 
	for(int i=0;i<strlen(str);i++)
	{
		if(str[i]!='a')
		{
			if(i==(strlen(str)-1))//删最后一位数 
			{
				str[i]='a';
				key=1;
				break;
			}
			int j=i+1;
			while(str[j]=='a'&&(j<strlen(str)))
			{
				j++;
			}

			if(str[j]>=str[i])
			{
				str[i]='a';
				key=1;
				break;
			}
			else
			{
				continue;
			}
		}

	}
	if(key==0)
	{
		int k=strlen(str)-1;
		while(k>=0)
		{
			if(str[k]!='a')
			{
				str[k]='a';
				break;
			}
			k--;
		}
	}
}
int main() 
{
	char str[max];
	cin>>str;
	int k;
	cin>>k;
	for(int i=1;i<=k;i++)
		del(str);
	for(int i=0;i<strlen(str);i++)
	{
		if(str[i]!='a')
		{
			cout<<str[i];
		}
	}	
	cout<<endl;	
} 
