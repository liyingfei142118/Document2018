/*��Ŀ����
����һ��ʮ���Ƶ�������number��ѡ�������ȥ��һ�������֣�ϣ������������������ɵ����������
��������:
����Ϊ�������ݣ���һ����������number��1 �� length(number) �� 50000��
�ڶ�����ϣ��ȥ������������cnt 1 �� cnt < length(number)��
�������:
������������Ľ����
ʾ��1
����
325 1
���
35*/
//̰�Ĳ��ԣ�
//ÿɾһ�� ���ұ߱����������������ɾ����С�Ǹ� 
#include<iostream>
#include<string.h>
using namespace std;
#define max 50000
void del(char *str)
{
	int key=0;//�жϵ����һ������  �Ƿ�ɾ���� 
	for(int i=0;i<strlen(str);i++)
	{
		if(str[i]!='a')
		{
			if(i==(strlen(str)-1))//ɾ���һλ�� 
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
