#include<iostream>
using namespace std;
#include<malloc.h>
#include<time.h>
#include<stdlib.h>
/*3．设某传感器，每秒不间断采集数据（整数0-1000），
要求任何时刻只保留最后N个数据（初始值为0），并输出当前最大值，
设N=10，试利用循环队列编写算法。*/	

#define max 10
typedef struct
{	int *elem;
	int  front;//队头标志 
	int rear;//队尾标志 
}LinkQueue;

void InitQueue(LinkQueue &Q)
 {
 	Q.elem=(int *)malloc(max*sizeof(int));
	if(!Q.elem)throw("error!");
	Q.front=Q.rear=0;

 }
void EnQueue(LinkQueue &Q,int e)
 {
 	if(Q.rear==10)//控制循环 
 	{
 		Q.rear=0;	
	 }
	Q.elem[Q.rear]=e;
	Q.rear++;
 }
void DeQueue(LinkQueue &Q,int &e)
{
	e=Q.elem[Q.front];
	if(Q.front==Q.rear)
	{
		Q.front++;
		Q.rear--;
	}	  
}
void Print(LinkQueue Q)
{
	for(int i=0;i<10;i++)
	{
		cout<<i<<":"<<Q.elem[Q.front]<<" ";
		Q.front++;
	}
}
int main()
{
	LinkQueue Q;
	InitQueue(Q);
	srand((int)time_t(1));//定义一秒类 
	int n;
	for(int i=1;i<=1000;i++)
	{
		n=rand()%1000;
		if(i%20==0)
		cout<<endl;
		cout<<n<<" ";//输出所有随机数 
		EnQueue(Q,n);
	}
	cout<<endl;
	Print(Q);
	return 0;
} 

