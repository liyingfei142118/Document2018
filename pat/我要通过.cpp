/*�õ�������ȷ���������ǣ�
1. �ַ����б������P, A, T�������ַ��������԰��������ַ���
2. �������� xPATx ���ַ��������Ի�á�����ȷ����
���� x �����ǿ��ַ����������ǽ�����ĸ A ��ɵ��ַ�����
3. ��� aPbTc ����ȷ�ģ���ô aPbATca Ҳ����ȷ�ģ�
���� a, b, c �������ǿ��ַ����������ǽ�����ĸ A ��ɵ��ַ�����
���ھ�����ΪPATдһ���Զ����г����ж���Щ�ַ����ǿ��Ի�á�����ȷ���ġ�
�����ʽ�� ÿ�������������1������������
��1�и���һ����Ȼ��n (<10)������Ҫ�����ַ���������
������ÿ���ַ���ռһ�У��ַ������Ȳ�����100���Ҳ������ո�
�����ʽ��ÿ���ַ����ļ����ռһ�У�������ַ������Ի�á�����ȷ���������YES���������NO��*/
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
	for(int i=0;i<n;i++)//�õ��ַ��� 
	{
		cin>>c[i];
	}
	for(int i=0;i<n;i++)
	{
		int t=Judge(c[i]);//�ж�1 
		if(t==0)
		{
			cout<<"NO"<<endl;
		}
		else
		{
			int t1=Judge1(c[i]);//�ж�2 
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
