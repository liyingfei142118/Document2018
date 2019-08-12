/*题目描述
继MIUI8推出手机分身功能之后，MIUI9计划推出一个电话号码分身的功能：
首先将电话号码中的每个数字加上8取个位，
然后使用对应的大写字母代替 （"ZERO", "ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE"）， 
然后随机打乱这些字母，所生成的字符串即为电话号码对应的分身。
输入描述:
第一行是一个整数T（1 ≤ T ≤ 100)表示测试样例数；接下来T行，每行给定一个分身后的电话号码的分身（长度在3到10000之间）。
输出描述:
输出T行，分别对应输入中每行字符串对应的分身前的最小电话号码（允许前导0）
输入
4
EIGHT
ZEROTWOONE
OHWETENRTEO
OHEWTIEGTHENRTEO
输出
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
