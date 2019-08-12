#include<iostream>
using namespace std;
#include<malloc.h>
#define MAXVEX 100


//�߱���
typedef struct EdgeNode 
{
	int adjvex;//�ڽӵ��򣬴洢�ö����Ӧ���±�
	int weight;//���ڴ洢Ȩֵ�����ڷ���ͼ���Բ���Ҫ
	struct EdgeNode *next;//����ָ����һ���ڽӵ�
}EdgeNode;

//�������
typedef struct VertexNode
{
	int data; //�����򣬴洢������Ϣ
	EdgeNode *firstedge; //�߱�ͷָ��
}VertexNode,AdjList[MAXVEX];

typedef struct
{
	AdjList adjList;
	int numVertexes,numEdges;//ͼ�е�ǰ�������ͱ���
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
			cout<<p->adjvex<<":";
			cout<<p->weight<<" ";
			p=p->next;
		}
		cout<<endl;
	}
}

//����ͼ���ڽӱ�ṹ
//β�巨
void Creat_Graph(Graph *G)
{
	
	

	//���붥��ͱ���
	cout<<"���붥�����ͱ���:"<<endl;
	cin>>G->numVertexes>>G->numEdges;


	//���붥����Ϣ�����������
	cout<<"���붥���ַ�:"<<endl;
	for(int i=1;i<=G->numVertexes;i++)
	{
		cin>>G->adjList[i].data;
		G->adjList[i].firstedge=NULL;
	}
	cout<<endl;
	//�����߱�
	int i,j,weight1;
	EdgeNode *p,*q;
	EdgeNode *p1,*q1;
	for(int k=0;k<G->numEdges;k++)
	{
		
		cout<<"����ߣ�vi,vj���ϵĶ�����ź�Ȩֵ��"<<endl;
		cin>>i>>j>>weight1;
		//���������е�ͷ�巨��
		p = (EdgeNode*)malloc(sizeof(EdgeNode));//���ڴ�����ռ�
		//���ɱ߱���
		p->adjvex=j;
		p->weight=weight1;
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


	/*	q= (EdgeNode*)malloc(sizeof(EdgeNode));//���ڴ�����ռ�
		//���ɱ߱���
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
	QueuePtr front;//��ͷָ�� 
	QueuePtr rear;//��βָ�� 
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
void DeQueue_last(LinkQueue &Q,int &e)
{
	if(Q.front==Q.rear)exit(0);
	QueuePtr s;
	s=Q.front;
	e=Q.rear->data;
	while(s)
	{
		if(s->next==Q.rear)
			{
				Q.rear=s;
				Q.rear->next=NULL;
				break;
				}	
		s=s->next;
	}
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
	int ve[G.numVertexes+1];
	int indegree[G.numVertexes+1];
	for(int i=1;i<=G.numVertexes;i++)
		{
		indegree[i]=0;ve[i]=0;
		}
	FindIndegree(G,indegree);
	
	for(int i=1;i<=G.numVertexes;i++)
		cout<<" "<<i<<":"<<indegree[i]<<" ";
	cout<<endl;
	LinkQueue s,t;
	InitQueue(s);
	InitQueue(t);
	for(int i=1;i<=G.numVertexes;i++)
	{
		if(indegree[i]==0)
			{
				EnQueue(s,i);
				
			}
	}
	int count=0;

	while(!QueueEmpty(s))
	{
		int e;
		DeQueue(s,e);EnQueue(t,e);
			cout<<G.adjList[e].data<<" ";
			count++;
		EdgeNode *p;
	for(p=G.adjList[e].firstedge;p;p=p->next)
	{
		int k;
		k=p->adjvex;
		indegree[k]--;
		if(indegree[k]==0)
			{
				EnQueue(s,k);
			}
		if(ve[e]+p->weight>ve[k])
			ve[k]=ve[e]+p->weight;
	}				
	}
	cout<<endl;
	int vl[G.numVertexes+1];
	for(int i=1;i<=G.numVertexes;i++)
	{
		cout<<ve[i]<<" ";
		vl[i]=ve[G.numVertexes];
		
	}
	cout<<endl;
	for(int i=1;i<=G.numVertexes;i++)
	{
		cout<<vl[i]<<" ";
	}
while(!QueueEmpty(t))
	{
			int e;
		
		EdgeNode *p;
	for(DeQueue_last(t,e),p=G.adjList[e].firstedge;p;p=p->next)
	{
		int k;
	//	cout<<e<<"* ";
		k=p->adjvex;
		if((vl[k]-p->weight)<vl[e])
			vl[e]=vl[k]-p->weight;
	}
}
	cout<<endl;
	for(int i=1;i<=G.numVertexes;i++)
	{
		cout<<vl[i]<<" ";
	}
	cout<<endl;
	for(int j=1;j<=G.numVertexes;j++)
	{
		EdgeNode *q;
		for(q=G.adjList[j].firstedge;q;q=q->next)
		{
			int kk=q->adjvex;
			int ee=ve[j];
			int el=vl[kk]-q->weight;
			if((ee-el)==0)
				cout<<"<"<<j<<","<<kk<<">";
			
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
