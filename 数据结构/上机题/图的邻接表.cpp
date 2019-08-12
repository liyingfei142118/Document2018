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


		q= (EdgeNode*)malloc(sizeof(EdgeNode));//向内存申请空间
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
		 }
//	Print_Graph(G);
	}
}
//头插法 
/*void Creat_Graph(Graph *G)
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
	for(int k=0;k<G->numEdges;k++)
	{
		cout<<"输入边（vi,vj）上的顶点序号："<<endl;
		cin>>i>>j;
		//（单链表中的头插法）
		p = (EdgeNode*)malloc(sizeof(EdgeNode));//向内存申请空间
		//生成边表结点
		p->adjvex=j;
		p->next=G->adjList[i].firstedge;
		G->adjList[i].firstedge=p;

		q= (EdgeNode*)malloc(sizeof(EdgeNode));//向内存申请空间
		//生成边表结点
		q->adjvex=i;
		q->next=G->adjList[j].firstedge;
		G->adjList[j].firstedge=q;
	//	Print_Graph(G);
	}
}*/
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
void BFS(Graph *G,int k,int *visit)
{
	LinkQueue S;
	InitQueue(S);
	EnQueue(S,k);
	visit[k]=0;
	int e;
	EdgeNode *p;
	while(!QueueEmpty(S))
	{		
		DeQueue(S,e);
		cout<<e<<"";		
		p=G->adjList[e].firstedge;
		while(p!=NULL)
			{
				if(visit[p->adjvex]==1)
				{
					visit[p->adjvex]=0;
					EnQueue(S,p->adjvex);
				}
				p=p->next;	
			}	
	}
	
}
void DFS(Graph *G,int *visit,int k)
{
	EdgeNode *p;
     cout<<G->adjList[k].data<<"";  // 访问顶点vi
    visit[k] = 0;              //标记vi已访问
    p = G->adjList[k].firstedge;        //取vi边表的头指针
    while (p)
     {                               //依次搜索vi的邻接点vj，这里j=p->adjvex
        if (visit[p->adjvex])    //若vi尚未被访问
            DFS(G, visit,p->adjvex);      //则以Vj为出发点向纵深搜索
        p = p->next;                     //找vi的下一邻接点
    }
    for(int i=1;i<=G->numVertexes;i++)
	{
		if(visit[i]!=0)
			DFS(G, visit,i);
	}
}

int main()
{    
	Graph G;    
	Creat_Graph(&G);
	Print_Graph(&G);
	
	int visit[MAXVEX],k;
	for(int i=1;i<=G.numVertexes;i++)
	{
		visit[i]=1;
	}
	cout<<"the first vertexes:";
	cin>>k;
//	DFS(&G,visit,k);
//	cout<<endl;
	
	BFS(&G,k,visit);
	return 0;
}




