#include<iostream>
using namespace std;
#include<malloc.h>
struct Node
{
	int key;
	int next;
};
struct QueueNode
{
	int front;
	int rear;
};
void Distribute(Node r[],int n,QueueNode q[],int m,int first)
{
	int i=first;
	while(r[i].next!=-1)
	{
		int k=r[i].key;
		if(q[k].front==-1)q[k].front=i;
		else
			r[q[k].rear].next=i;
		i=r[i].next;
	}
}
void Collect(Node r[],int n,QueueNode q[],int m,int first)
{
	int k=0;
	while(q[k].front!=-1)
	{
		k++;
	}
	first=q[k].front;
	int last=q[k].rear;
	while(k<m)
	{
		k++;
		if(q[k].front!=-1)
		{
			r[last].next=q[k].front;
			last=q[k].rear;
		}
	}
	r[last].next=-1;
}
void BucketSort(Node r[],QueueNode q[],int n,int m)
{
	for(int i=0;i<n;i++)
	{
		r[i].next=i+1;
	}
	r[n-1].next=-1;
	int first=0;
	for(int i=0;i<m;i++)
	{
		q[i].front=q[i].rear=-1;
	}
	Distribute(r,n,q,m,first);
	Collect(r,n,q,m,first);
}
