/*得到“答案正确”的条件是：
1. 字符串中必须仅有P, A, T这三种字符，不可以包含其它字符；
2. 任意形如 xPATx 的字符串都可以获得“答案正确”，
其中 x 或者是空字符串，或者是仅由字母 A 组成的字符串；
3. 如果 aPbTc 是正确的，那么 aPbATca 也是正确的，
其中 a, b, c 均或者是空字符串，或者是仅由字母 A 组成的字符串。
现在就请你为PAT写一个自动裁判程序，判定哪些字符串是可以获得“答案正确”的。
输入格式： 每个测试输入包含1个测试用例。
第1行给出一个自然数n (<10)，是需要检测的字符串个数。
接下来每个字符串占一行，字符串长度不超过100，且不包含空格。
输出格式：每个字符串的检测结果占一行，如果该字符串可以获得“答案正确”，则输出YES，否则输出NO。*/
#include<iostream>
using namespace std;
#include<string.h>

int Judge2(char ch[])
{
	int s=strlen(ch);
	int key=0,word=0;
	for(int i=0;i<s;i++)
	{
		if(ch[i]=='A')
		{
			key++;
		}
		else if(ch[i]=='P')
		{
			int temp=0;
			for(int j=i+1;j<i+key;j++)
			{
				if(ch[j]!='A')
				{
					temp=1;
					break;
				}
			}
			if(temp==1)
			{
				word=1;
			}
			else
			{
				
				if(ch[i+key+1]=='T')
				{
				
					int temp1=0;
					for(int j=i+2*key;j<s;j++)
					{
						
						if(ch[j]!='A')
						{
							temp1=1;
							break;
						}
					}
					if(temp1==1)
					{
						word=1;
					}
				}
				else
				{
					word=1;
				}
			}
		}
		else
		{
			word=1;
			break;
		}
		break;
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
int Judge1(char ch[])
{
	int s=strlen(ch);
	if(s%2==0)
	{
		return 0;
	}
	else if(s==3&&ch[1]=='A'&&ch[0]=='P'&&ch[2]=='T')
	{
	
		return 1;
	}
	else
	{
		int k=s/2+1;
		if(ch[k-1]=='A'&&ch[k-2]=='P'&&ch[k]=='T')
		{
			int key=0;
			for(int j=0;j<k-2;j++)
			{
				if(ch[j]!=ch[s-j-1])
					{
						key=1;
					}
			}
			if(key==1)
			{
			
				return 0;
			}
			else
			{
				
				return 1;
			}
		}
		else
		{
			return 0;
		}
	}
}
int Judge(char ch[])
{
		int s=strlen(ch),key=0;
		if(s<3)
		{
			return 0;
		 } 
		 else
		 {
				 	for(int j=0;j<s;j++)
					{
						if(ch[j]!='P'&&ch[j]!='A'&&ch[j]!='T')
						{
							key=1;
						}
					}
				if(key==1)
				{
					return 0;
				}
				else
				{
					return 1;
				}
		 }
}
int main()
{
	char c[10][101];	
	int n;
	cin>>n;
	for(int i=0;i<n;i++)//得到字符串 
	{
		cin>>c[i];
	}
	for(int i=0;i<n;i++)
	{
		int t=Judge(c[i]);//判断1 
		if(t==0)
		{
			cout<<"NO"<<endl;
		}
		else
		{
			int t1=Judge1(c[i]);//判断2 
			if(t1==1)
			{
				cout<<"YES"<<endl;
			}
			else
			{
				int t2=Judge2(c[i]);
				if(t2==1)
				{
					cout<<"YES"<<endl;
				}
				else
				{
					cout<<"NO"<<endl;
				}
			}
		}
	}
	
}
