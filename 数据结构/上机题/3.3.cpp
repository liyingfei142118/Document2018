#include<iostream>
using namespace std;
#include<malloc.h>
#include<time.h>
#include<stdlib.h>
/*3����ĳ��������ÿ�벻��ϲɼ����ݣ�����0-1000����
Ҫ���κ�ʱ��ֻ�������N�����ݣ���ʼֵΪ0�����������ǰ���ֵ��
��N=10��������ѭ�����б�д�㷨��*/	

#define max 10
typedef struct
{	int *elem;
	int  front;//��ͷ��־ 
	int rear;//��β��־ 
}LinkQueue;

void InitQueue(LinkQueue &Q)
 {
 	Q.elem=(int *)malloc(max*sizeof(int));
	if(!Q.elem)throw("error!");
	Q.front=Q.rear=0;

 }
void EnQueue(LinkQueue &Q,int e)
 {
 	if(Q.rear==10)//����ѭ�� 
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
	srand((int)time_t(1));//����һ���� 
	int n;
	for(int i=1;i<=1000;i++)
	{
		n=rand()%1000;
		if(i%20==0)
		cout<<endl;
		cout<<n<<" ";//������������ 
		EnQueue(Q,n);
	}
	cout<<endl;
	Print(Q);
	return 0;
} 

