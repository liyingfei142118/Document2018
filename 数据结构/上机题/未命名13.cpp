#include<iostream>
using namespace std;
#include<malloc.h> 
#include<cstdlib>
#include<string.h>
#include<stack>
//比较lhs的优先级是否不高于rhs，rhs表示栈顶的符号
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

//将中缀表达式转换成后缀式
string inPrefix2postPrefix(string str)
{
	string res;//后缀表达式结果
	stack<char> s;
	for (int i=0;i<str.size();i++)
	{
		//如果是数字，直接加入后缀表达式结果中
		if (isdigit(str[i]))
		{
			while (i<str.size()&&isdigit(str[i]))
			{
					res+=str[i];
					i++;
			}
			i--;//注意这里要将i减1，因为上面的循环将i多右移了一位，如果不减1，会漏掉一位
			res+=" ";
		}
		else //如果是符号，需要与栈顶的元素进行比较
		{
			 //如果栈为空，将其直接压入栈中;如果是左括号(，也直接将其压入栈中
				if (s.empty()||str[i]=='(')
						s.push(str[i]);
				else
				{
						//当碰到右括号时，将栈中的数据出栈，直到碰到左括号，注意左右括号都不需要加入结果res中
						if (str[i]==')')
						{
								while (!s.empty()&&s.top()!='(')//注意在对栈执行top操作之前需要判断栈是否为空
								{
									res+=s.top();
									res+=" ";
									s.pop();
								}
								s.pop();
						}
						else  
						{
								//此时表示该字符为符号，并且不为'('和')'
								if (priority(str[i],s.top()))//如果它的优先级不高于栈顶符号，那么将栈顶符号出栈
								{
										while(!s.empty()&&priority(str[i],s.top()))
										{
												res+=s.top();
												res+=" ";
												s.pop();
										}
										s.push(str[i]);//最后记得将该符号入栈
								}
								else //如果它的优先级比栈顶符号高，那么直接入栈
										s.push(str[i]);
						}
				}
		}
	}
	while(!s.empty())//遍历完字符串后将栈中剩余的元素加入结果集中
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
		if (isdigit(input[i]))//如果遇到的是数字，就将数字入栈
		{
			while(i<input.size()&&isdigit(input[i]))
			{
				tmp=10*tmp+input[i]-'0';
				i++;
			}
			//得到数字以后将这个输入压入栈中
			s.push(tmp);
			i--;
		}
		else if(input[i]==' ')//如果遇到空格，就将tmp重置为0
			tmp=0;
		else//此时遇到的就是符号
		{
			   //取出两个操作数，并进行计算
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
	cout<<"请输入合法的表达式(支持整数的+,-,*,/,括号运算)："<<endl;
	while(getline(cin,str))
	{
		string ot=inPrefix2postPrefix(str);
		cout<<"后缀表达式为："<<ot<<endl;
		cout<<"计算结果为："<<calculateByPostPrefix(ot)<<endl;
		cout<<"请输入表达式："<<endl;
	}
	system("pause");
	return 0;
}
