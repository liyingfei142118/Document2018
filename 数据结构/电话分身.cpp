/*��Ŀ����
��MIUI8�Ƴ��ֻ�������֮��MIUI9�ƻ��Ƴ�һ���绰�������Ĺ��ܣ�
���Ƚ��绰�����е�ÿ�����ּ���8ȡ��λ��
Ȼ��ʹ�ö�Ӧ�Ĵ�д��ĸ���� ��"ZERO", "ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE"���� 
Ȼ�����������Щ��ĸ�������ɵ��ַ�����Ϊ�绰�����Ӧ�ķ���
��������:
��һ����һ������T��1 �� T �� 100)��ʾ������������������T�У�ÿ�и���һ�������ĵ绰����ķ���������3��10000֮�䣩��
�������:
���T�У��ֱ��Ӧ������ÿ���ַ�����Ӧ�ķ���ǰ����С�绰���루����ǰ��0��
����
4
EIGHT
ZEROTWOONE
OHWETENRTEO
OHEWTIEGTHENRTEO
���
0
234
345
0345*/
#include<iostream>
using namespace std;
#include<string.h>
int main()
{
	char str[101][10000];
	int T;
	cin>>T;
	for(int i=1;i<=T;i++)
	{
		cin>>str[i];
	}
	for(int i=1;i<=T;i++)
	{
	int j=0;
	while((j<=strlen(str[i]))&&(str[i][j]>='A')&&(str[i][j]<='Z'))
		{
			switch(str[i][j])
			{
				
				case 'Z':
					{
						cout<<"2";
						j+=4;
						break;
					}
				case 'O':
					{
						cout<<"3";
						j+=3;
						break;
					}
				case 'T':
					{
						if(str[i][j+1]=='W')
						{
							cout<<"4";
							j+=3;
						}
						else
						{
						cout<<"5";
						j+=5;
						}
						break;
					}
				case 'F':
					{
						if(str[i][j+1]=='O')
						{
							cout<<"6";
							j+=4;
						}
						else
						{
						cout<<"7";
						j+=4;
						}	
						break;
					}
				case 'S':
					{
						if(str[i][j+1]=='I')
						{
							cout<<"8";
							j+=3;
						}
						else
						{
						cout<<"9";
						j+=5;
						}	
						break;
					}
				case 'E':
					{
						cout<<"0";
						j+=5;
						break;
					}
				case 'N':
					{
						cout<<"1";
						j+=4;
						break;
					}
			}
		}
		cout<<endl;
	}
}
