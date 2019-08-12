#include<iostream>
using namespace std;
#include<malloc.h>
#define STACK_INIT_SIZE 100
#define STACKINCREAT 10
typedef struct 
{
	int *base;
	int *top;
	int stacksize;
}SqStack;
void InitStack(SqStack &s)//�����ջ�͸�ֵ 
{
	s.base=(int *)malloc(STACK_INIT_SIZE*sizeof(int));
	if(!s.base)exit(0);
	s.top=s.base;
	s.stacksize=STACK_INIT_SIZE;
	int n;
	cout<<"The element number:";
	cin>>n;
	cout<<"Please input every number:";
	for(int i=0;i<n;i++)
	{
		cin>>*s.top++;
	} 
}
void Print_Stack(SqStack s)//��ӡջ 
{
	cout<<"the SqStack element:";
	cout<<s.top-s.base<<endl;
	SqStack s1;
	s1.base=s.base;
	for(int i=0; i<s.top-s.base; i++)//Ԫ�صĳ���length=s.top-s.base 
	{
		cout<<*s1.base++<<" ";
	} 	
}
void DestroyStack(SqStack &s)//����ջ 
{
	free(s.base);
	s.top=s.base=NULL;
}
void ClearStack(SqStack &s)//���ջ 
{
	free(s.base);
	s.top=s.base=NULL;
}
bool StackEmpty(SqStack &s)//���ջ 
{
	if(s.base==NULL)
	return false;
}
int StackLength(SqStack s)//����ջ�ĳ��� 
{
	return (s.top-s.base);
}
void GetTop(SqStack s,int &e)//�õ�ջ����Ԫ�� 
{
	if(s.base==s.top)exit(0);
	e=*(s.top-1);
}
void Push(SqStack &s,int e)//���һ��Ԫ�� 
{
	if(s.top-s.base>=s.stacksize) 
	{
	s.base=(int *)realloc(s.base,(s.stacksize+STACKINCREAT)*sizeof(int));	
		if(!s.base)exit(0);
	s.top=s.base+s.stacksize;
	s.stacksize+=STACKINCREAT;
	}
	*s.top=e;
	s.top++;
}
void Pop(SqStack &s,int &e)//ɾ��һ��Ԫ�� 
{
	if(s.base==s.top)exit(0);
	--s.top;
	e=*s.top;
}
void visit(int e)
{
	cout<<e<<" ";
}
void StackTraverse(SqStack s)//��ջ����visit()���� 
{
	for(int i=0; i<s.top-s.base; i++)//Ԫ�صĳ���length=s.top-s.base 
	{
		visit(*s.base);
		*s.base++;
	} 
}
int main()
{
	SqStack s;
	InitStack(s);
	Print_Stack(s);
	
//	DestroyStack(s);
//	Print_Stack(s);

//	StackEmpty(s);

/*	int e;
	GetTop(s,e);
	cout<<"e:"<<e<<endl;*/
	
/*	int e;
	cout<<"please input e:";
	cin>>e;
	Push(s,e);
	cout<<"s:"<<endl;
	Print_Stack(s);*/
	
/*	int k;
	Pop(s,k);
	cout<<"k:"<<k;
	Print_Stack(s);*/
		
	return 0;
}
