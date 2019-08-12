#include<iostream>
using namespace std;
#include<malloc.h>
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
void QSolution(LinkQueue &Q)
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
		int i,j;
	EnQueue(Q,1,1);
	while(!QueueEmpty(Q))	
	{
		DeQueue(Q,i,j);
		a[i][j]=k++;
		print(a);
		if(i==8&&j==8)
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

int main()
{
	LinkQueue Q;
	InitQueue(Q);
	QSolution(Q);
	QueueTraverse(Q);
	return 0;
} 
