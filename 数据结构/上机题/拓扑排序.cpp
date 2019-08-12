#include<iostream>
using namespace std;
#include<malloc.h>
#define MAXVEX 100


//边表结点
typedef struct EdgeNode 
{
	int adjvex;//邻接点域，存储该顶点对应的下标
	int weight;//用于存储权值，对于非网图可以不需要
	struct EdgeNode *next;//链域，指向下一个邻接点
}EdgeNode;

//顶点表结点
typedef struct VertexNode
{
	int data; //顶点域，存储顶点信息
	EdgeNode *firstedge; //边表头指针
}VertexNode,AdjList[MAXVEX];

typedef struct
{
	AdjList adjList;
	int numVertexes,numEdges;//图中当前顶点数和边数
}Graph;
void Print_Graph(Graph *G)
{
	EdgeNode *p;
	for(int i=1;i<=G->numVertexes;i++)
	{		
		p=G->adjList[i].firstedge;
		cout<<G->adjList[i].data<<" ";
		while(p)
		{
			cout<<p->adjvex<<" ";
			p=p->next;
		}
		cout<<endl;
	}
}

//建立图的邻接表结构
//尾插法
void Creat_Graph(Graph *G)
{
	
	

	//输入顶点和边数
	cout<<"输入顶点数和边数:"<<endl;
	cin>>G->numVertexes>>G->numEdges;


	//输入顶点信息，建立顶点表
	cout<<"输入顶点字符:"<<endl;
	for(int i=1;i<=G->numVertexes;i++)
	{
		cin>>G->adjList[i].data;
		G->adjList[i].firstedge=NULL;
	}
	cout<<endl;
	//建立边表
	int i,j;
	EdgeNode *p,*q;
	EdgeNode *p1,*q1;
	for(int k=0;k<G->numEdges;k++)
	{
		
		cout<<"输入边（vi,vj）上的顶点序号："<<endl;
		cin>>i>>j;
		//（单链表中的头插法）
		p = (EdgeNode*)malloc(sizeof(EdgeNode));//向内存申请空间
		//生成边表结点
		p->adjvex=j;
		p->next=NULL;
		if(G->adjList[i].firstedge==NULL)
		 	G->adjList[i].firstedge=p;
		 else
		 {
		 	p1=G->adjList[i].firstedge;
		 	while(p1->next)
		 		p1=p1->next;
		 	p1->next=p;
		 	
		 }


	/*	q= (EdgeNode*)malloc(sizeof(EdgeNode));//向内存申请空间
		//生成边表结点
		q->adjvex=i;
		q->next=NULL;
		if(G->adjList[j].firstedge==NULL)
		 	G->adjList[j].firstedge=q;
		 else
		 {
		 	q1=G->adjList[j].firstedge;
		 	while(q1->next)
		 		q1=q1->next;
		 	q1->next=q;	 	
		 }*/
	}
}

 
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
 }
 int QueueEmpty(LinkQueue Q)
 {

	if(Q.rear==Q.front)
		return 1;
	else
		return 0;

 }
void EnQueue(LinkQueue &s,int e)
{
	QueuePtr p;
	p=(QueuePtr)malloc(sizeof(QNode));
	if(!p)exit(0);
	p->data=e;
	p->next=NULL;
	s.rear->next=p;
	s.rear=p;
}
void DeQueue(LinkQueue &Q,int &e)
{
	if(Q.front==Q.rear)exit(0);
	QueuePtr s;
	s=Q.front->next;
	e=s->data;
	Q.front->next=s->next;
	if(Q.rear==s)
		Q.rear=Q.front;
	free(s);
}
void FindIndegree(Graph G,int *indegree)
{
	EdgeNode *p;
	for(int i=1;i<=G.numVertexes;i++)
	{		
		p=G.adjList[i].firstedge;
		
		while(p)
		{
			indegree[p->adjvex]++;
			p=p->next;
		}
	}
}
void Topologicalsort(Graph G)
{
	int indegree[G.numVertexes];
	for(int i=1;i<=G.numVertexes;i++)
		indegree[i]=0;
	FindIndegree(G,indegree);
	
	for(int i=1;i<=G.numVertexes;i++)
		cout<<" "<<i<<":"<<indegree[i]<<" ";
	cout<<endl;
	LinkQueue s;
	InitQueue(s);
	for(int i=1;i<=G.numVertexes;i++)
	{
		if(indegree[i]==0)
			EnQueue(s,i);
	}
	int count=0;
	while(!QueueEmpty(s))
	{
		int e;
		DeQueue(s,e);
			cout<<G.adjList[e].data<<" ";
			count++;
		EdgeNode *p;
	for(p=G.	st[e].firstedge;p;p=p->next)
	{
		int k;
		k=p->adjvex;indegree[k]--;
		if(indegree[k]==0)
			EnQueue(s,k);
		
	}	
			
	}
	if(count<G.numVertexes)exit(0);
}

int main()
{    
	Graph G;    
	Creat_Graph(&G);
	Print_Graph(&G);
	cout<<endl;
	Topologicalsort(G);

}
