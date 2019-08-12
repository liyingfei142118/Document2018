#include<iostream>
using namespace std;
#include<malloc.h>
typedef struct CSNode
{
	char data;
	struct CSNode *first,*next;
}CSNode,*CSNtree;
void Init_CSNtree(CSNtree &t)
{
	t=(CSNode *)malloc(sizeof(CSNode));
	if(!t)exit(0);
	t->first=t->next=NULL;
}
void Creat_CSNtree(CSNtree &t)
{
	char ch;
	cin>>ch;
	if(ch=='$')
		{
			t=NULL;
		}
	else
	{
		t=(CSNode *)malloc(sizeof(CSNode));
		if(!t)exit(0);
		t->data=ch;
		Creat_CSNtree(t->first);
		Creat_CSNtree(t->next);
	}
}

typedef struct QNode
{
	CSNode *data;
	struct QNode *next;
}QNode,*QueuePtr;
typedef struct
{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;
void Init_Queue(LinkQueue &s)
{
	s.front=s.rear=(QueuePtr)malloc(sizeof(QNode));
	if(!s.front)exit(0);
	s.front->next=NULL;	
}
void EnQueue(LinkQueue &s,CSNode *e)
{
	QueuePtr p;
	p=(QueuePtr)malloc(sizeof(QNode));
	if(!p)exit(0);
	p->data=e;
	p->next=NULL;
	s.rear->next=p;
	s.rear=p;
}
void DeQueue(LinkQueue &s,CSNode * &e)
{
	if(s.rear==s.front)exit(0);
	
	QueuePtr p;
	p=s.front->next;
	e=p->data;
	s.front->next=p->next;
	
	if(s.rear==p)s.rear=s.front;
	free(p);
}
int Empty_Queue(LinkQueue s)
{
	if(s.rear==s.front)
		return 1;
	else
		return 0;
}

void div_CSNtree(CSNtree t)
{
	LinkQueue s;
	CSNode *p=t;
	Init_Queue(s);
	if(t)
	{
		EnQueue(s,p);
	}
	while(!Empty_Queue(s))
	{
		DeQueue(s,p);
		cout<<p->data<<" ";
		if(p->first)
					EnQueue(s,p->first);		
		if(p->next)
					EnQueue(s,p->next);			
	}
}
int main()
{
	CSNtree t;
	Creat_CSNtree(t);
	div_CSNtree(t);
	return 0;
}

