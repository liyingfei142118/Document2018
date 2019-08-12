#include<iostream>
using namespace std;
#include<malloc.h> 
#include<cstdlib>
#include<string.h>
#include<stack>
//�Ƚ�lhs�����ȼ��Ƿ񲻸���rhs��rhs��ʾջ���ķ���
bool priority(char lhs,char rhs)
{
		if (rhs=='(')
			return false;
		if (lhs=='+'||lhs=='-')
			return true;
		if ((lhs=='*'||lhs=='/')&&(rhs=='*'||rhs=='/'))
			return true;
		return false;
}

//����׺���ʽת���ɺ�׺ʽ
string inPrefix2postPrefix(string str)
{
	string res;//��׺���ʽ���
	stack<char> s;
	for (int i=0;i<str.size();i++)
	{
		//��������֣�ֱ�Ӽ����׺���ʽ�����
		if (isdigit(str[i]))
		{
			while (i<str.size()&&isdigit(str[i]))
			{
					res+=str[i];
					i++;
			}
			i--;//ע������Ҫ��i��1����Ϊ�����ѭ����i��������һλ���������1����©��һλ
			res+=" ";
		}
		else //����Ƿ��ţ���Ҫ��ջ����Ԫ�ؽ��бȽ�
		{
			 //���ջΪ�գ�����ֱ��ѹ��ջ��;�����������(��Ҳֱ�ӽ���ѹ��ջ��
				if (s.empty()||str[i]=='(')
						s.push(str[i]);
				else
				{
						//������������ʱ����ջ�е����ݳ�ջ��ֱ�����������ţ�ע���������Ŷ�����Ҫ������res��
						if (str[i]==')')
						{
								while (!s.empty()&&s.top()!='(')//ע���ڶ�ջִ��top����֮ǰ��Ҫ�ж�ջ�Ƿ�Ϊ��
								{
									res+=s.top();
									res+=" ";
									s.pop();
								}
								s.pop();
						}
						else  
						{
								//��ʱ��ʾ���ַ�Ϊ���ţ����Ҳ�Ϊ'('��')'
								if (priority(str[i],s.top()))//����������ȼ�������ջ�����ţ���ô��ջ�����ų�ջ
								{
										while(!s.empty()&&priority(str[i],s.top()))
										{
												res+=s.top();
												res+=" ";
												s.pop();
										}
										s.push(str[i]);//���ǵý��÷�����ջ
								}
								else //����������ȼ���ջ�����Ÿߣ���ôֱ����ջ
										s.push(str[i]);
						}
				}
		}
	}
	while(!s.empty())//�������ַ�����ջ��ʣ���Ԫ�ؼ���������
	{
		res+=s.top();
		res+=" ";
		s.pop();
	}
	return res;
}
int operate(int first,int second,char op)
{
	int res=0;
	switch (op)
	{
		case '+':
			res= first+second;
			break;
		case '-':
			res=first-second;
			break;
		case '*':
			res=first*second;
			break;
		case '/':
			res=first/second;
			break;
		default:
			break;		
	}
	return res;
}
int   calculateByPostPrefix(string input)
{
	stack<int> s;
	int tmp=0;
	for (int i=0;i<input.size();i++)
	{
		if (isdigit(input[i]))//��������������֣��ͽ�������ջ
		{
			while(i<input.size()&&isdigit(input[i]))
			{
				tmp=10*tmp+input[i]-'0';
				i++;
			}
			//�õ������Ժ��������ѹ��ջ��
			s.push(tmp);
			i--;
		}
		else if(input[i]==' ')//��������ո񣬾ͽ�tmp����Ϊ0
			tmp=0;
		else//��ʱ�����ľ��Ƿ���
		{
			   //ȡ�������������������м���
				int second=s.top();
				s.pop();
				int first=s.top();
				s.pop();
				int local=operate(first,second,input[i]);
				s.push(local);
		}
	}
	return s.empty()?0:s.top();
}
int main()
{
	string str;//9+(3-1)*3+10/2
	cout<<"������Ϸ��ı��ʽ(֧��������+,-,*,/,��������)��"<<endl;
	while(getline(cin,str))
	{
		string ot=inPrefix2postPrefix(str);
		cout<<"��׺���ʽΪ��"<<ot<<endl;
		cout<<"������Ϊ��"<<calculateByPostPrefix(ot)<<endl;
		cout<<"��������ʽ��"<<endl;
	}
	system("pause");
	return 0;
}
