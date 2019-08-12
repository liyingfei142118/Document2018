#include<iostream>
using namespace std;
#include<malloc.h>

#define STACK_INIT_SIZE 100
#define STACKINCREAT 10

typedef struct
{
	int i;
	int j;
	int dir;
}Pos;
typedef struct 
{
	Pos *base;
	Pos *top;
	int stacksize;
}SqStack;

void InitStack(SqStack &s)//构造空栈和赋值 
{
	s.base=(Pos *)malloc(STACK_INIT_SIZE*sizeof(Pos));
	if(!s.base)exit(0);
	s.top=s.base;
	s.stacksize=STACK_INIT_SIZE;

}
void Print_Stack(SqStack s)//打印栈 
{
	cout<<"the SqStack element:";
	cout<<s.top-s.base<<endl;
	SqStack s1;
	s1.base=s.base;
	for(int i=0; i<s.top-s.base; i++)//元素的长度length=s.top-s.base 
	{
		cout<<"i:"<<s1.base->i<<" j:"<<s1.base->j<<" "<<" dir:"<<s1.base->dir<<endl;
		s1.base++;
	} 
	cout<<endl;	
}

void Push(SqStack &s,int x,int y,int dir)//添加一个元素 
{
	if(s.top-s.base>=s.stacksize) 
	{
	s.base=(Pos *)realloc(s.base,(s.stacksize+STACKINCREAT)*sizeof(Pos));	
		if(!s.base)exit(0);
	s.top=s.base+s.stacksize;
	s.stacksize+=STACKINCREAT;
	}
	s.top->i=x;
	s.top->j=y;
	s.top->dir=dir;
	s.top++;
}
void Pop(SqStack &s)//删除一个元素 
{
	if(s.base==s.top)exit(0);
	--s.top;
}

int GetTop(SqStack s)//得到栈顶的元素 
{
	if(s.base==s.top)exit(0);
	s.top--;
	return s.top->dir;
}


void print(int a[10][10])
{
	for(int i=0;i<10;i++)
	for(int j=0;j<10;j++)
	{
		cout<<a[i][j]<<"    ";
		if(j==9)
			cout<<endl;
		
	}
	cout<<endl;
}
void Solution(SqStack &L)
{

	int a[10][10];
	int k=2;
	for(int i=0;i<10;i++)
	for(int j=0;j<10;j++)
	{
		if(i==0||i==9||j==0||j==9)
			a[i][j]=0;
		else if(j==1&&i==8)
			a[i][j]=0;
		else if(j==2&&(i==4||i==6||i==7))
			a[i][j]=0;
		else if(j==3&&(i==1||i==2||i==4||i==7))
			a[i][j]=0;
		else if(j==4&&(i==4||i==5||i==7))
			a[i][j]=0;
		else if(j==5&&i==3)
			a[i][j]=0;
		else if(j==6&&(i==3||i==6||i==7))
			a[i][j]=0;
		else if(j==7&&(i==1||i==2||i==7))
			a[i][j]=0;
		else
			a[i][j]=1;
	}
	print(a);

	int i=1,j=1;
	a[1][1]=k;
	Push(L,1,1,99);
	Print_Stack(L);
	while((i!=8||j!=8))	
	{

		if(a[i-1][j]==1)
			{
				
				Push(L,i-1,j,11);
				i=i-1;
				a[i][j]=k+1;
				k++;
				
			}
		else if(a[i][j+1]==1)
			{
				
				Push(L,i,j+1,22);
				j=j+1;
				a[i][j]=k+1;
				k++;	
			}
		else if(a[i+1][j]==1)
			{
				
				Push(L,i+1,j,33);
				i=i+1;
				a[i][j]=k+1;
				k++;	
			}
		else if(a[i][j-1]==1)
			{
				
				Push(L,i,j-1,44);
				j=j-1;
				a[i][j]=k+1;
				k++;
					
			}
		else
			{
				
				a[i][j]=0;			
				if(GetTop(L)==11)
					i=i+1;
				if(GetTop(L)==22)
					j=j-1;
				if(GetTop(L)==33)
					i=i-1;
				if(GetTop(L)==44)
					j=j+1;
				Pop(L);
				k--;
			//	print(a);
			}
	}
	print(a);	
}

int main()
{

	SqStack L;

	InitStack(L);
	
	Solution(L);

	Print_Stack(L);

	cout<<endl;

	return 0;
}
