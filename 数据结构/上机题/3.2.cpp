#include<iostream>
using namespace std;
#include<malloc.h>
typedef struct  QNode
{
	int data;
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
 	int n;
	cout<<"The element number:";
	cin>>n;
	cout<<"Please input every number:";
	
	for(int i=0;i<n;i++)
	{	QNode *s;
		s=(QNode *)malloc(sizeof(QNode));
		cin>>s->data;
		Q.rear->next=s;
		Q.rear=Q.rear->next;
	} 
	Q.rear->next=NULL;
 }
 void visit (int e)
 {
 	cout<<e<<" ";
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
 			cout<<L->data<<" ";
 			L=L->next;
 		}
 	}
 }
 void DestroyQueue(LinkQueue &Q)
 {
 	Q.front=Q.front->next;
 	while(Q.front)
 	{
 		Q.rear=Q.front->next;
 		free(Q.front);
 		Q.front=Q.rear;
 	}
 }
 void ClearQueue(LinkQueue &Q)
 {
 	Q.front=Q.front->next;
 	while(Q.front)
 	{
 		Q.rear=Q.front->next;
 		free(Q.front);
 		Q.front=Q.rear;
 	}
 }
 bool QueueEmpty(LinkQueue Q)
 {
 	if(Q.front->next==NULL)
	 return ture;
 	else 
	 return false;
 }
 int QueueLength(LinkQueue Q)
 {
 	int i=0;
 	Q.front=Q.front->next;
 	while(Q.front)
 	{
 		i++;
 		Q.front=Q.rear;
 	}
 	return i;
 }
void EnQueue(likeQueue &Q,int e)
 {
 	Queueptr s;
 	s=(QNode *)malloc(sizeof(QNode));
 	if(!p)exit(0);
 	s->data=e;
 	Q.rear->next=s;
 	Q.rear=Q.rear->next;
 	Q.rear->next=NULL;
 }
void DeQueue(LinkQueue &Q,int &e)
{
	if(Q.front==Q.rear)exit(0);
	Queueptr s;
	s=Q.front->next;
	e=s->data;
	Q.front->next=s->next;
	if(Q.rear==s)
	Q.rear=Q.front;
	free(s);
}
int main()
{
	LinkQueue Q;
	InitQueue(Q);
	QueueTraverse(Q);
	return 0;
} 
