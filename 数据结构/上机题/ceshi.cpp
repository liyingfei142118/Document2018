//************************************************************************/
/* ͼ���ڽӱ�洢�ṹ                                                    */
/************************************************************************/
#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifdef _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__) 
#endif
#endif

#include <stdio.h>
#define MaxVertexNum 100
#define QueueSize 30 
typedef enum{ FALSE, TRUE }Boolean;
 Boolean visited[MaxVertexNum];
typedef char VertexType;
typedef int EdgeType;
typedef struct node     //�߱���
{
     int adjvex;         //�ڽӵ���
    struct node *next;  //����
    //����Ҫ��ʾ���ϵ�Ȩ,��Ӧ����һ��������
}EdgeNode;
typedef struct vnode    //����߽��
{
     VertexType vertex;  //������
    EdgeNode *firstedge;//�߱�ͷָ��
}VertexNode;
typedef VertexNode AdjList[MaxVertexNum];   //AdjList���ڽӱ�����
typedef struct
 {
     AdjList adjlist;    //�ڽӱ�
    int n, e;           //ͼ�е�ǰ�������ͱ���
}ALGraph;               //���ڼ򵥵�Ӧ�ã����붨������ͣ���ֱ��ʹ��AdjList����
/************************************************************************/
/* ��������ͼ���ڽӱ��㷨                                               */
/************************************************************************/
void CreateGraphAL(ALGraph *G)
 {
     int i, j, k;
     EdgeNode * s;
     printf("�����붥�����ͱ���(�����ʽΪ:������,����)��\n");
     scanf("%d,%d", &(G->n), &(G->e));       // ���붥�����ͱ���   
    printf("�����붥����Ϣ(�����ʽΪ:�����<CR>)ÿ�������Իس���Ϊ����:\n");
     for (i = 0; i < G->n; i++)              // ����n������Ķ����   
    {
         scanf("\n%c", &(G->adjlist[i].vertex)); // ���붥����Ϣ   
        G->adjlist[i].firstedge = NULL;            // ��ı߱�ͷָ����Ϊ��   
    }
     printf("������ߵ���Ϣ(�����ʽΪ:i,j)��\n");
     for (k = 0; k < G->e; k++)      // �����߱�   
    {
         scanf("\n%d,%d", &i, &j); // �����<Vi,Vj>�Ķ����Ӧ���   
        s = new EdgeNode;         // �����±߱���s   
        s->adjvex = j;         // �ڽӵ����Ϊj   
        s->next = G->adjlist[i].firstedge; // ���±߱���s���뵽����Vi�ı߱�ͷ��   
        G->adjlist[i].firstedge = s;
         s = new EdgeNode;
         s->adjvex = i;
         s->next = G->adjlist[j].firstedge;
         G->adjlist[j].firstedge = s;
     }
 }
/************************************************************************/
/* ������ȱ���                                                         */
/************************************************************************/
void DFS(ALGraph *G, int i)
 {
     //��viΪ��������ڽӱ��ʾ��ͼG���������������
    EdgeNode *p;
     printf("visit vertex:%c\n", G->adjlist[i].vertex);  // ���ʶ���vi
    visited[i] = TRUE;              //���vi�ѷ���
    p = G->adjlist[i].firstedge;        //ȡvi�߱��ͷָ��
    while (p)
     {                               //��������vi���ڽӵ�vj������j=p->adjvex
        if (!visited[p->adjvex])    //��vi��δ������
            DFS(G, p->adjvex);      //����VjΪ����������������
        p = p->next;                     //��vi����һ�ڽӵ�
    }
 }
void DFSTraverseM(ALGraph *G)
 {
     int i;
     for (i = 0; i < G->n; i++)
         visited[i] = FALSE;
     for (i = 0; i < G->n; i++)
         if (!visited[i])
             DFS(G, i);
 }
/************************************************************************/
/* ������ȱ���                                                         */
/************************************************************************/
typedef struct
 {
     int front;
     int rear;
     int count;
     int data[QueueSize];
 }CirQueue;
void InitQueue(CirQueue *Q)
 {
     Q->front = Q->rear = 0;
     Q->count = 0;
 }
int QueueEmpty(CirQueue *Q)
 {
     return Q->count == 0;
 }
int QueueFull(CirQueue *Q)
 {
     return Q->count == QueueSize;
 }
void EnQueue(CirQueue *Q, int x)
 {
     if (QueueFull(Q))
         printf("Queue overflow");
     else
     {
         Q->count++;
         Q->data[Q->rear] = x;
         Q->rear = (Q->rear + 1) % QueueSize;
     }
 }
int DeQueue(CirQueue *Q)
 {
     int temp;
     if (QueueEmpty(Q))
     {
         printf("Queue underflow");
         return NULL;
     }
     else
     {
         temp = Q->data[Q->front];
         Q->count--;
         Q->front = (Q->front + 1) % QueueSize;
         return temp;
     }
 }
void BFS(ALGraph*G, int k)
 {   // ��vkΪԴ������ڽӱ��ʾ��ͼG���й����������
    int i;
     CirQueue Q;             //�뽫���ж�����DataType��Ϊint
    EdgeNode *p;
     InitQueue(&Q);          //���г�ʼ��
    printf("visit vertex:%c\n", G->adjlist[k].vertex);      //����Դ��vk
    visited[k] = TRUE;
     EnQueue(&Q, k);         //vk�ѷ��ʣ������˶ӡ���ʵ�����ǽ�������˶ӣ�
    while (!QueueEmpty(&Q))
     {                                   //�ӷǿ���ִ��
        i = DeQueue(&Q);                    //�൱��vi����
        p = G->adjlist[i].firstedge;        //ȡvi�ı߱�ͷָ��
        while (p)
         {                               //��������vi���ڽӵ�vj(��p->adjvex=j)
            if (!visited[p->adjvex])
             {                           //��vjδ���ʹ�
                printf("visit vertex:%c\n", G->adjlist[p->adjvex].vertex);      //����vj
                visited[p->adjvex] = TRUE;
                 EnQueue(&Q, p->adjvex); //���ʹ���vj�˶�
            }
             p = p->next;                    //��vi����һ�ڽӵ�
        }
     }
 }
void BFSTraverseM(ALGraph *G)
 {
     int i;
     for (i = 0; i < G->n; i++)
         visited[i] = FALSE;
     for (i = 0; i < G->n; i++)
         if (!visited[i])
             BFS(G, i);
 }
/************************************************************************/
/* ��ӡ�ڽӱ�                                                     */
/************************************************************************/
void PrintfGraphAL(ALGraph *G)
 {
     for (int i = 0; i < G->n; i++)
     {
         printf("vertex:%c", G->adjlist[i].vertex);
         EdgeNode *p = G->adjlist[i].firstedge;
         while (p)
         {
             printf("��:%d", p->adjvex);
             p = p->next;
         }
         printf("\n");
     }
 }
/************************************************************************/
/* ɾ���ڽӱ�                                                     */
/************************************************************************/
void DeleteGraphAL(ALGraph *G)
 {
     for (int i = 0; i < G->n; i++)
     {
         EdgeNode *q;
         EdgeNode *p = G->adjlist[i].firstedge;
         while (p)
         {
             q = p;
             p = p->next;
             delete q;
         }
         G->adjlist[i].firstedge = NULL;
     }
 }
/************************************************************************/
/* ����������                                                           */
/************************************************************************/
int main()
 {
#ifdef _MSC_VER
     _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG));
     _CrtDumpMemoryLeaks();
#endif

     ALGraph G;
     CreateGraphAL(&G);
     printf("������ȱ�����\n");
     DFSTraverseM(&G);
     printf("������ȱ�����\n");
     BFSTraverseM(&G);
     printf("�ڽӱ�\n");
     PrintfGraphAL(&G);
     DeleteGraphAL(&G);

     return 0;
 }
 #include<iostream>
#include<fstream>
using  namespace std;

#define MAX 100
#define MAXCOST 0x7fffffff

int graph[MAX][MAX];

int prim(int graph[][MAX], int n)
{
	int lowcost[MAX];
	int mst[MAX];
	int i, j, min, minid, sum = 0;
	for (i = 2; i <= n; i++)
	{
		lowcost[i] = graph[1][i];
		mst[i] = 1;
	}
	mst[1] = 0;
	for (i = 2; i <= n; i++)
	{
		min = MAXCOST;
		//minid = 0;
		for (j = 2; j <= n; j++)
		{
			if (lowcost[j] < min && lowcost[j] != 0)
			{
				min = lowcost[j];
			//	minid = j;
			}
		}
		cout << "V" << mst[minid] << "-V" << minid << "=" << min << endl;
		sum += min;
		lowcost[minid] = 0;
		for (j = 2; j <= n; j++)
		{
			if (graph[minid][j] < lowcost[j])
			{
				lowcost[j] = graph[minid][j];
				mst[j] = minid;
			}
		}
	}
	return sum;
}

int main()
{
	int i, j, k, m, n;
	int x, y, cost;
	ifstream in("input.txt");
	in >> m >> n;//m=����ĸ�����n=�ߵĸ���
	//��ʼ��ͼG
	for (i = 1; i <= m; i++)
	{
		for (j = 1; j <= m; j++)
		{
			graph[i][j] = MAXCOST;
		}
	}
	//����ͼG
	for (k = 1; k <= n; k++)
	{
		in >> i >> j >> cost;
		graph[i][j] = cost;
		graph[j][i] = cost;
	}
	//�����С������
	cost = prim(graph, m);
	//�����СȨֵ��
	cout << "��СȨֵ��=" << cost << endl;
	system("pause");
	return 0;
}

