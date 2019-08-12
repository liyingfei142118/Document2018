#include<iostream>
using namespace std;
#include<malloc.h>
#include<fstream>
#define STACK_INIT_SIZE 100
#define STACKINCREAT 10


typedef struct
{
	int i;
	int j;
	int weight;	
}map;
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
typedef struct  QNode
{
	int x;
	int y;
	struct QNode *next;
}QNode,*QueuePtr;

typedef struct
{
	QueuePtr front;//队头指针 
	QueuePtr rear;//队尾指针 
}LinkQueue;
void InitStack(SqStack &s);//构造空栈和赋值 
void Print_Stack(SqStack s);//打印栈 
void Push(SqStack &s,int x,int y,int dir);//添加一个元素
void Pop(SqStack &s);//删除一个元素  
int GetTop(SqStack s);//得到栈顶的元素 
void print(int a[10][10]);
void Solution(SqStack &L);//栈 
void InitQueue(LinkQueue &Q);
void QueueTraverse(LinkQueue Q);
int QueueEmpty(LinkQueue Q);
void EnQueue(LinkQueue &Q,int x,int y);
void DeQueue(LinkQueue &Q,int &x,int &y);
void QSolution(LinkQueue &Q);//队列 
int  Find(int a[10][10],int i,int j,int x,int y,int &k,int &flag);//深度搜索
void Creat_map();//创建地图 
void Solution3();//深度搜索 
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
		cout<<a[i][j]<<"    	";
		if(j==9)
			cout<<endl;
		
	}
	cout<<endl;
}
void Solution(SqStack &L)//栈 
{

	fstream file;
	int a[10][10];
	map p;
	file.open("map.dat",ios::in|ios::binary);
	if(file.fail())
	{
		cout<<"file open error!"<<endl;
		exit(0);
	}
	file.read((char *)&p,sizeof(p));
	while(!file.eof())
	{
		a[p.i][p.j]=p.weight;
		file.read((char *)&p,sizeof(p));
	}
	file.close();
	print(a);

	int k=2;
	int i,j;
	cout<<"please input qidian:";
	cin>>i>>j;
	a[i][j]=k;
	int x,y;
	cout<<"please input zhongdian:";
	cin>>x>>y;
	Push(L,i,j,99);
//	Print_Stack(L);
	while((i!=x||j!=y))	
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



void InitQueue(LinkQueue &Q)
 {
 	Q.front=Q.rear=(QNode *)malloc(sizeof(QNode));
 	if(!Q.front)exit(0);
 	Q.front->next=NULL;
 }
 void QueueTraverse(LinkQueue Q)
 {
 	QueuePtr L;
 	if(Q.front->next!=NULL)
 	{
 		L=Q.front->next;
 		cout<<"output all element:";
 		while(L)
 		{
 			cout<<L->x<<" "<<L->y<<" ";
 			L=L->next;
 		}
 	}
 }
 
 
int QueueEmpty(LinkQueue Q)
 {
 	if(Q.front->next==NULL)
	 return 1;
 	else 
	 return 0;
 }
void EnQueue(LinkQueue &Q,int x,int y)
 {
 	QueuePtr s;
 	s=(QNode *)malloc(sizeof(QNode));
 	if(!s)exit(0);
 	
 	s->x=x;
 	s->y=y;

 	
	 Q.rear->next=s;
 	Q.rear=Q.rear->next;
 	Q.rear->next=NULL;
 }
void DeQueue(LinkQueue &Q,int &x,int &y)
{
	if(Q.front==Q.rear)exit(0);
	QueuePtr s;
	
	s=Q.front->next;
	x=s->x;
	y=s->y;
	
	Q.front->next=s->next;
	if(Q.rear==s)
	Q.rear=Q.front;
	free(s);
}
void QSolution(LinkQueue &Q)//队列 
{
	fstream file;
	int a[10][10];
	map p;
	file.open("map.dat",ios::in|ios::binary);
	if(file.fail())
	{
		cout<<"file open error!"<<endl;
		exit(0);
	}
	file.read((char *)&p,sizeof(p));
	while(!file.eof())
	{
		a[p.i][p.j]=p.weight;
		file.read((char *)&p,sizeof(p));
	}
	file.close();
	print(a);

	int k=2;
	int x,y,x1,y1;
	cout<<"please input qidian:";
	cin>>x>>y;
	cout<<"please input zhongdian:";
	cin>>x1>>y1;
	a[x][y]=k;
		int i,j;
	EnQueue(Q,x,y);
	while(!QueueEmpty(Q))	
	{
		DeQueue(Q,i,j);
		a[i][j]=k++;
		cout<<"<"<<i<<","<<j<<">"<<" ";
		//print(a);
		if(i==x1&&j==y1)
			break;
		if(a[i-1][j]==1)//上 
			{
				
				EnQueue(Q,i-1,j);
				a[i-1][j]=0;
				
			}
		 if(a[i][j+1])//右 
			{
				
				EnQueue(Q,i,j+1);
				a[i][j+1]=0;
					
			}
		 if(a[i+1][j]==1)//下 
			{
				
				EnQueue(Q,i+1,j);
				a[i+1][j]=0;	
			}
	 if(a[i][j-1]==1)//左 
			{
				
				EnQueue(Q,i,j-1);
				a[i][j-1]=0;	
			}
	}
	print(a);
}
int  Find(int a[10][10],int i,int j,int x,int y,int &k,int &flag)
{
	if(flag)return 0;
	a[i][j]=k;
//	print(a);
cout<<"<"<<i<<","<<j<<">"<<" ";
	k++;
	if(i==x&&j==y)
	{
		flag=1;
		return 1;
	}
		
	else
	{
		if(a[i-1][j]==1)//上 
			{			
				Find(a,i-1,j,x,y,k,flag);			
			}
		 if(a[i][j+1])//右 
			{
				
				Find(a,i,j+1,x,y,k,flag);
					
			}
		 if(a[i+1][j]==1)//下 
			{
				
				Find(a,i+1,j,x,y,k,flag);	
			}
		 if(a[i][j-1]==1)//左 
		 {
		 		Find(a,i,j-1,x,y,k,flag);
		 }
	}
		
	
}
void Solution3()//深度搜索 
{
	fstream file;
	int a[10][10];
	map p;
	file.open("map.dat",ios::in|ios::binary);
	if(file.fail())
	{
		cout<<"file open error!"<<endl;
		exit(0);
	}
	file.read((char *)&p,sizeof(p));
	while(!file.eof())
	{
		a[p.i][p.j]=p.weight;
		file.read((char *)&p,sizeof(p));
	}
	file.close();
	print(a);
	int k=2,flag=0;
	int x,y,x1,y1;
	cout<<"please input qidian:";
	cin>>x>>y;
	cout<<"please input zhongdian:";
	cin>>x1>>y1;
	cout<<Find(a,x,y,x1,y1,k,flag)<<endl;
	print(a);
}
void Creat_map()//创建地图 
{//其实可以实现手动输入 
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
	fstream file;
	map p;
	file.open("map.dat",ios::out|ios::binary);
	if(file.fail())
	{
		cout<<"file open error!"<<endl;
		exit(0);
	}
	for(int i=0;i<10;i++)
	for(int j=0;j<10;j++)
	{
		p.i=i;
		p.j=j;
		p.weight=a[i][j];
		file.write((char *)&p,sizeof(p));
	}
	file.close();
	file.open("map.dat",ios::in|ios::binary);
	if(file.fail())
	{
		cout<<"file open error!"<<endl;
		exit(0);
	}
	file.read((char *)&p,sizeof(p));
	while(!file.eof())
	{
		cout<<"i:"<<p.i<<" j:"<<p.j<<" weight:"<<p.weight<<endl;
		file.read((char *)&p,sizeof(p));
	}
}
int main()
{

	
	cout<<"			迷宫问题"<<endl;
	cout<<"			1.创建地图"<<endl;
	cout<<"			2.栈"<<endl;
	cout<<"			3.队列 广度搜索"<<endl;
	cout<<"			4.深度搜索"<<endl;
	int choice;
	cout<<"please input your choice:";
	cin>>choice;
	switch(choice)
	{
		case 1:
			system("cls");
			cout<<"			迷宫问题"<<endl;
			cout<<"			创建地图"<<endl;
			Creat_map();
			break;
		case 2:
			system("cls");
			cout<<"			迷宫问题"<<endl;
			cout<<"			   栈"<<endl;
			SqStack L;
			InitStack(L);
			Solution(L);
			//Print_Stack(L);
			break;
		case 3:
			system("cls");
			cout<<"			迷宫问题"<<endl;
			cout<<"		  队列 广度搜索"<<endl;
			LinkQueue Q;
			InitQueue(Q);
			QSolution(Q);
			//QueueTraverse(Q);
			break;	
		case 4:
			system("cls");
			cout<<"			迷宫问题"<<endl;
			cout<<"			深度搜索"<<endl;
			Solution3();
			break;
		default:
				cout<<"input data is error!";		
	}
	return 0;
}
