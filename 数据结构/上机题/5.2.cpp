//2. 二叉树的先序、中序、后序遍历非递归方法，层次遍历。
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

typedef struct
{
	BiTNode **base;
	BiTNode **top;
	int stacksize;
}Sqstack;
void Init_Sqstack(Sqstack &s)
{
	s.base=(BiTNode **)malloc(max*sizeof(BiTNode*));
	if(!s.base)exit(0);
	s.top=s.base;
	s.stacksize=max;
}

void Push(Sqstack &s,BiTNode *e)
{
	if(s.top-s.base>=s.stacksize)
	{
		s.base=(BiTNode **)realloc(s.base,(s.stacksize+add)*sizeof(BiTNode*));
		if(!s.base)exit(0);
		s.top=s.base+s.stacksize;
		s.stacksize+=add;
	}
	*s.top=e;
	s.top++;	
}
void Pop(Sqstack &s,BiTNode* &e)
{
	if(s.base==s.top)exit(0);
	s.top--;
	e=*s.top;
}
int Empty_stack(Sqstack s)
{
	if(s.base==s.top)
		return 1;
	else
		return 0;
}
void Gottop_stack(Sqstack s,BiTNode* &e)
{
	if(s.base==s.top)exit(0);
	s.top--;
	e=*s.top;
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
void Preorder_BiTree(BiTree T)//先序遍历非递归 
{
	Sqstack s;
	BiTNode *p;
	Init_Sqstack(s);
	if(T)
	Push(s,T);
	while(!Empty_stack(s))
				{
					Pop(s,p);
					cout<<p->data<<" ";
					if(p->rchild)
					{
						Push(s,p->rchild);			
					}
					
					if(p->lchild)
					{
						Push(s,p->lchild);			
					}				
				}                                                        
}
void Inorder_BiTree(BiTree T)
{
	Sqstack s;
	BiTNode *p=T;
	Init_Sqstack(s);
	while(p||!Empty_stack(s))
		{
			if(p)
			{
				Push(s,p);		
				p=p->lchild;
			}
			else
			{
				Pop(s,p);
				cout<<p->data<<" ";
				p=p->rchild;
			}
		}
}
void Postorder_BiTree(BiTree T)
{
	Sqstack s;
	BiTNode *p=T;
	Init_Sqstack(s);
	int word=1;
				if(p->rchild)
					{
						Push(s,p->rchild);		
					}
				Push(s,p);
				if(p->lchild)
					{
						Push(s,p->lchild);			
					}//先存入第一个右孩子和左孩子，根  //#AB 
		Gottop_stack(s,p);
			while(p)//得到孩子 
			{
				if(p->rchild&&p->rchild->data!='0')
					{
						Push(s,p->rchild);			
					}			
				if(p->lchild&&p->lchild->data!='0')
					{
						Push(s,p->lchild);			
					}	//#ABDC #ABD #ABDFE #ABDFEG #ABDFE 
			if((p->lchild==NULL||p->lchild->data=='0')&&(p->rchild==NULL||p->rchild->data=='0'))
				{
					Pop(s,p);
					cout<<p->data<<" ";
					T=p;
					T->data='0';
				}
			Gottop_stack(s,p);	
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
int main()
{
	BiTree T;
	Init_BiTree(T);//构建二叉树 
	cout<<"please input the all data:";
	Creat_BiTree(T);//初始化二叉树 
	cout<<endl;
	cout<<"div:";
	div_BiTree(T);
	cout<<endl;
	cout<<"Preorde:";
	Preorder_BiTree(T);
	cout<<endl;
	cout<<"Inorder:";
	Inorder_BiTree(T);
	cout<<endl;
	cout<<"Postorder:";
	Postorder_BiTree(T);
	
	return 0;
}
