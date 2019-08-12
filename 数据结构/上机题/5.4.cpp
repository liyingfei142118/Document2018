#include<iostream>
using namespace std;
#include<malloc.h>
#define max 100
#define add 10
typedef struct BiTNode
{
	char data;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;
typedef struct QNode
{
	BiTNode *data;
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
void EnQueue(LinkQueue &s,BiTNode *e)
{
	QueuePtr p;
	p=(QueuePtr)malloc(sizeof(QNode));
	if(!p)exit(0);
	p->data=e;
	p->next=NULL;
	s.rear->next=p;
	s.rear=p;
}
void DeQueue(LinkQueue &s,BiTNode * &e)
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
void Init_BiTree(BiTree &T)
{
	T=(BiTNode *)malloc(sizeof(BiTNode));
	if(!T)exit(0);
	T->lchild=T->rchild=NULL;
		
} 
void Creat_BiTree(BiTree &T)
{
	char e;
	cin>>e;
	if(e=='$')
		T=NULL;
	else
	{
		T=(BiTNode *)malloc(sizeof(BiTNode));
		if(!T)exit(0);
		T->data=e;
		Creat_BiTree(T->lchild);
		Creat_BiTree(T->rchild);
	}	
}
void div_BiTree(BiTree T)
{
	LinkQueue s;
	BiTNode *p=T;
	Init_Queue(s);
	if(T)
	{
		EnQueue(s,p);
	}
	while(!Empty_Queue(s))
	{
		DeQueue(s,p);
		cout<<p->data<<" ";
		if(p->lchild)
					EnQueue(s,p->lchild);		
		if(p->rchild)
					EnQueue(s,p->rchild);			
	}
}
void Adjust_BiTree(BiTree T)
{
	LinkQueue s;
	BiTNode *p=T;
	Init_Queue(s);
	if(T)
	{
		EnQueue(s,p);
	}
	while(!Empty_Queue(s))
	{
		DeQueue(s,p);
		if(p->rchild&&p->lchild==NULL)//如果有右孩子，没有左孩子，false 
		{
			cout<<"No!";
			break;
		}
		if((p->lchild&&p->rchild==NULL)||(p->lchild==NULL&&p->rchild==NULL))//如果只有左孩子
		//或者都没有
		{
			if(p->lchild)//将当前有左孩子的入队列 
					EnQueue(s,p->lchild);		
			int word=1;
			while(!Empty_Queue(s))//后面的结点都没有左孩子或者右孩子，如果有，false 
			{
				DeQueue(s,p);
				if(p->lchild||p->rchild)//
				{
					word=0;
					break;
				}

				
			}
			if(word==0)
			{
				cout<<"No!";
				break;
			}
			else
			{
				cout<<"Yes!";
				break;
			}
			
		}
		else
		{	
		if(p->lchild)
					EnQueue(s,p->lchild);	
		if(p->rchild)
					EnQueue(s,p->rchild);
		}
			
	}
		 


}
int main()
{
	
	BiTree T;
	Init_BiTree(T);//构建二叉树 
	cout<<"please input the all data:";
	Creat_BiTree(T);//初始化二叉树 
	div_BiTree(T);
	Adjust_BiTree(T);//判断完全二叉树 
	return 0;
}
