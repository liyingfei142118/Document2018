/*11、算术表达式求值 (选做) （栈）
[问题描述]
　　一个算术表达式是由操作数(operand)、运算符(operator)和界限符(delimiter)组成的。假设操作数是正实数，运算符只含加减乘除等四种运算符，界限符有左右括号和表达式起始、结束符“#”，如：#6+15*（21-8/4）#。引入表达式起始、结束符是为了方便。编程利用“运算符优先法”求算术表达式的值。
[基本要求]
（1） 从键盘或文件读入一个合法的算术表达式，输出正确的结果。
（2） 显示输入序列和栈的变化过程。
（3） 考虑算法的健壮性，当表达式错误时，要给出错误原因的提示。
（4） 实现非整数的处理。*/
#include<iostream>
using namespace std;
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>
#include<fstream>
#define MAX 100

typedef struct
{
	char *base;
	char *top;
	int stacksize;
}SqStack;
void InitStack(SqStack &S)//初始化 
{
	S.base=(char*)malloc(MAX*sizeof(char));
	if(!S.base)exit(0);
	S.top=S.base;
	S.stacksize=MAX;
}
void Push(SqStack &S,char e)//入栈 
{
	if(S.top-S.base==S.stacksize)exit(0);//栈满 
	*S.top=e;//元素e压入栈顶，栈顶指针加1; 
	S.top++;
 } 
int Empty(SqStack S)
{
	if(S.base=S.top)
	return 1;
	else
	return 0;
}
void Pop(SqStack &S,char &e)//出栈 
{
	if(S.top==S.base)exit(0);//栈空 
	S.top--;
	e=*S.top;//栈顶指针减一，将栈顶元素赋给e; 
}
void PrintStack(SqStack s)//打印栈 
{
	cout<<"the SqStack element:";
	cout<<s.top-s.base<<endl;
	SqStack s1;
	s1.base=s.base;
	for(int i=0; i<s.top-s.base; i++)//元素的长度length=s.top-s.base 
	{
		cout<<*s1.base++<<" ";
	} 	
	cout<<endl;
}
char GetTop(SqStack S)//取栈顶元素 
{
	if(S.top!=S.base)//栈非空 
	return *(S.top-1);//返回栈顶元素的值，栈顶指针不变 
}
int In(char e)//判断读入字符是否为运算符 
{
	if(e=='+'||e=='-'||e=='*'||e=='/'||e=='('||e==')'||e=='#')
	    return 1;//是 
	else 
	    return 0; //不是 
}

char Precede(char a,char b)//比较运算符的优先级 
{
	char f;
	if(a=='+'||a=='-')//比较加减 
	{
		if(b=='+'||b=='-'||b==')'||b=='#')
		    f='>';
		else if(b=='*'||b=='/'||b=='(')
		    f='<';
	}
	else if(a=='*'||a=='/')//比较乘除 
	{
		if(b=='+'||b=='-'||b=='*'||b=='/'||b==')'||b=='#')
		   f='>';
		else if(b=='(')
		   f='<';
	}
	else if(a=='(')//比较左括号 
	{
		if(b=='+'||b=='-'||b=='*'||b=='/'||b=='(')
		   f='<';
		else if(b==')')
		   f='=';
	}
	else if(a==')')//比较右括号 
	{
		if(b=='+'||b=='-'||b=='*'||b=='/'||b==')'||b=='#')
		   f='>';
	}
	else if(a=='#')//比较结束标志 
	{
		if(b=='+'||b=='-'||b=='*'||b=='/'||b=='(')
		   f='<';
		else if(b=='#')
		   f='=';
	}
	return f;
}
char Operate(char a,char t,char b)//运算 
{//需要转换成整数 
	char c;
	a=a-'0';
	b=b-'0';
	if(t=='+')
	  c=a+b+'0';
	else if(t=='-')
	  c=a-b+'0';
	else if(t=='*')
	  c=a*b+'0';
	else if(t=='/')
	  c=a/b+'0';	  
	return c; 
}

void Change(SqStack s,int key)
{ 	
	int sum=0;
	char ch;
	Pop(s,ch);
	while(key!=0)
	{
		
		sum=sum*10+(ch-'0');
		key--;
		if(key!=0)
			Pop(s,ch);
	}
	Push(s,sum+'0');
}
int EvaluateExpression()
{



	SqStack s,s1;
	char ch,a,b,t,x;
	InitStack(s);//s存 数和运算结果 
	InitStack(s1);//s1存 运算符 
	Push(s1,'#');//起始标志入栈 
	ch=getchar();
	int key=0; 
	while(ch!='#'||GetTop(s1)!='#')
	{
		if(!In(ch))//如果不是运算符入栈 
		{
			Push(s,ch);
				ch=getchar();	
		}
		else//如果是运算符
		{
			switch(Precede(GetTop(s1),ch))//比较栈顶运算符和当前运算符 
			{
				case '<'://运算符栈顶优先权底 
					{
					Push(s1,ch);//入栈 
				    	ch=getchar(); 
					cout<<ch<<" ";   
					break;
					}
				case '='://如果相等，脱括号并接收下一个元素 
					{
					Pop(s1,x);
				    ch=getchar();
					cout<<ch<<" ";	   
					break;
					}
				case '>':
					{
					Pop(s1,t);////运算符栈顶优先权高
					Pop(s,b);
					Pop(s,a);//出栈里的两个元素a b 
					//计算值并入栈 
					Push(s,Operate(a,t,b));
					break;
					}
				default:
						cout<<"data is error!"<<endl;
			}
		} 
	}
	return GetTop(s)-'0';
}

int main()
{

	cout<<"请输入算术表达式,并以#结束:"<<endl;
	cout<<"结果是: "<<EvaluateExpression()<<endl;;
	return 0;
}


