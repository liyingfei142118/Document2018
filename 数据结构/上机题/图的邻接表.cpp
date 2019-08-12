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
			cout<<p->adjvex<<" ";
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
	int i,j;
	EdgeNode *p,*q;
	EdgeNode *p1,*q1;
	for(int k=0;k<G->numEdges;k++)
	{
		
		cout<<"����ߣ�vi,vj���ϵĶ�����ţ�"<<endl;
		cin>>i>>j;
		//���������е�ͷ�巨��
		p = (EdgeNode*)malloc(sizeof(EdgeNode));//���ڴ�����ռ�
		//���ɱ߱���
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


		q= (EdgeNode*)malloc(sizeof(EdgeNode));//���ڴ�����ռ�
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
		 }
//	Print_Graph(G);
	}
}
//ͷ�巨 
/*void Creat_Graph(Graph *G)
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
	int i,j;
	EdgeNode *p,*q;
	for(int k=0;k<G->numEdges;k++)
	{
		cout<<"����ߣ�vi,vj���ϵĶ�����ţ�"<<endl;
		cin>>i>>j;
		//���������е�ͷ�巨��
		p = (EdgeNode*)malloc(sizeof(EdgeNode));//���ڴ�����ռ�
		//���ɱ߱���
		p->adjvex=j;
		p->next=G->adjList[i].firstedge;
		G->adjList[i].firstedge=p;

		q= (EdgeNode*)malloc(sizeof(EdgeNode));//���ڴ�����ռ�
		//���ɱ߱���
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
     cout<<G->adjList[k].data<<"";  // ���ʶ���vi
    visit[k] = 0;              //���vi�ѷ���
    p = G->adjList[k].firstedge;        //ȡvi�߱��ͷָ��
    while (p)
     {                               //��������vi���ڽӵ�vj������j=p->adjvex
        if (visit[p->adjvex])    //��vi��δ������
            DFS(G, visit,p->adjvex);      //����VjΪ����������������
        p = p->next;                     //��vi����һ�ڽӵ�
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




