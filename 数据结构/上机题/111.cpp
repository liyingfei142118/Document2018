/*11���������ʽ��ֵ (ѡ��) ��ջ��
[��������]
����һ���������ʽ���ɲ�����(operand)�������(operator)�ͽ��޷�(delimiter)��ɵġ��������������ʵ���������ֻ���Ӽ��˳�����������������޷����������źͱ��ʽ��ʼ����������#�����磺#6+15*��21-8/4��#��������ʽ��ʼ����������Ϊ�˷��㡣������á���������ȷ������������ʽ��ֵ��
[����Ҫ��]
��1�� �Ӽ��̻��ļ�����һ���Ϸ����������ʽ�������ȷ�Ľ����
��2�� ��ʾ�������к�ջ�ı仯���̡�
��3�� �����㷨�Ľ�׳�ԣ������ʽ����ʱ��Ҫ��������ԭ�����ʾ��
��4�� ʵ�ַ������Ĵ���*/
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
void InitStack(SqStack &S)//��ʼ�� 
{
	S.base=(char*)malloc(MAX*sizeof(char));
	if(!S.base)exit(0);
	S.top=S.base;
	S.stacksize=MAX;
}
void Push(SqStack &S,char e)//��ջ 
{
	if(S.top-S.base==S.stacksize)exit(0);//ջ�� 
	*S.top=e;//Ԫ��eѹ��ջ����ջ��ָ���1; 
	S.top++;
 } 
int Empty(SqStack S)
{
	if(S.base=S.top)
	return 1;
	else
	return 0;
}
void Pop(SqStack &S,char &e)//��ջ 
{
	if(S.top==S.base)exit(0);//ջ�� 
	S.top--;
	e=*S.top;//ջ��ָ���һ����ջ��Ԫ�ظ���e; 
}
void PrintStack(SqStack s)//��ӡջ 
{
	cout<<"the SqStack element:";
	cout<<s.top-s.base<<endl;
	SqStack s1;
	s1.base=s.base;
	for(int i=0; i<s.top-s.base; i++)//Ԫ�صĳ���length=s.top-s.base 
	{
		cout<<*s1.base++<<" ";
	} 	
	cout<<endl;
}
char GetTop(SqStack S)//ȡջ��Ԫ�� 
{
	if(S.top!=S.base)//ջ�ǿ� 
	return *(S.top-1);//����ջ��Ԫ�ص�ֵ��ջ��ָ�벻�� 
}
int In(char e)//�ж϶����ַ��Ƿ�Ϊ����� 
{
	if(e=='+'||e=='-'||e=='*'||e=='/'||e=='('||e==')'||e=='#')
	    return 1;//�� 
	else 
	    return 0; //���� 
}

char Precede(char a,char b)//�Ƚ�����������ȼ� 
{
	char f;
	if(a=='+'||a=='-')//�ȽϼӼ� 
	{
		if(b=='+'||b=='-'||b==')'||b=='#')
		    f='>';
		else if(b=='*'||b=='/'||b=='(')
		    f='<';
	}
	else if(a=='*'||a=='/')//�Ƚϳ˳� 
	{
		if(b=='+'||b=='-'||b=='*'||b=='/'||b==')'||b=='#')
		   f='>';
		else if(b=='(')
		   f='<';
	}
	else if(a=='(')//�Ƚ������� 
	{
		if(b=='+'||b=='-'||b=='*'||b=='/'||b=='(')
		   f='<';
		else if(b==')')
		   f='=';
	}
	else if(a==')')//�Ƚ������� 
	{
		if(b=='+'||b=='-'||b=='*'||b=='/'||b==')'||b=='#')
		   f='>';
	}
	else if(a=='#')//�ȽϽ�����־ 
	{
		if(b=='+'||b=='-'||b=='*'||b=='/'||b=='(')
		   f='<';
		else if(b=='#')
		   f='=';
	}
	return f;
}
char Operate(char a,char t,char b)//���� 
{//��Ҫת�������� 
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
	InitStack(s);//s�� ���������� 
	InitStack(s1);//s1�� ����� 
	Push(s1,'#');//��ʼ��־��ջ 
	ch=getchar();
	int key=0; 
	while(ch!='#'||GetTop(s1)!='#')
	{
		if(!In(ch))//��������������ջ 
		{
			Push(s,ch);
				ch=getchar();	
		}
		else//����������
		{
			switch(Precede(GetTop(s1),ch))//�Ƚ�ջ��������͵�ǰ����� 
			{
				case '<'://�����ջ������Ȩ�� 
					{
					Push(s1,ch);//��ջ 
				    	ch=getchar(); 
					cout<<ch<<" ";   
					break;
					}
				case '='://�����ȣ������Ų�������һ��Ԫ�� 
					{
					Pop(s1,x);
				    ch=getchar();
					cout<<ch<<" ";	   
					break;
					}
				case '>':
					{
					Pop(s1,t);////�����ջ������Ȩ��
					Pop(s,b);
					Pop(s,a);//��ջ�������Ԫ��a b 
					//����ֵ����ջ 
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

	cout<<"�������������ʽ,����#����:"<<endl;
	cout<<"�����: "<<EvaluateExpression()<<endl;;
	return 0;
}


