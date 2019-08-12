#include<iostream>
using namespace std;
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

#define max 100
#define add 10
typedef struct LNode
{
	int data;
	struct LNode *next;
	
}LNode,*LinkList;
void InitList_lk(LinkList &head)// 构造链表 
{
	head=(LNode *)malloc(sizeof(LNode));
	head->next=NULL;
}
void DestroyList_lk(LinkList &head)//销毁表
{
	LNode *p;
	if(head->next!=NULL)
	p=head->next;
	while(p)
	{
		head->next=p->next;
		free(p);
		p=head->next;
	}
	head->next=NULL;
}
void ClearList_lk(LinkList &head)//清空表 
{
	LNode *p;
	if(head->next!=NULL)
	p=head->next;
	while(p)
	{
		head->next=p->next;
		free(p);
		p=head->next;
	}
	head->next=NULL;
}
bool ListEmpty_lk(LinkList head)//判断表是否为空 
{
	if(head->next==NULL)
	return true;
	else
	return false;
	
}
int ListLength_lk(LinkList head)//返回表的长度 
{
	LinkList p;
	int i=0;
	if(head->next!=NULL)
		p=head->next;
	while(p)
	{
		i++;
		p=p->next;
	}
	return i;
}

void GetElem_lk(LinkList head,int i,int &e)//从表中得到位置i的元素
{
	LinkList p;
	int j=0;
	if(head->next!=NULL)
		p=head->next;
	while(p)
	{
		j++;
		if(j==i)
		e=p->data;
		p=p->next;
	}
	
}
void LocateElem_lk(LinkList head,int e)//确定元素的位置 
{
	LinkList p;
	int i=0;
	if(head->next!=NULL)
		p=head->next;
	while(p)
	{
		i++;
		if(p->data==e)
		cout<<"the location:"<<i<<endl;	
		p=p->next;
	}
}
void PriorElem_lk(LinkList head,int cur_e,int &pre_e)//找到当前元素的前一个数 
{
	LinkList p,q;
	int i=0;
	q=head;
	if(head->next!=NULL)
		{
		if(head->next->data==cur_e)throw("error!");
		p=head->next;
		}
	while(p)
	{
		if(p->data==cur_e)
			{
			//cout<<"the pre_e:"<<q->data<<endl;
			pre_e=q->data;			
			break;
			}
		q=p;
		if(q->next!=NULL)
		p=q->next;	
	}
}
void NextElem_lk(LinkList head,int cur_e,int &next_e)//找到当前元素的后一个数
{
	LinkList p;
	int i=0;
	if(head->next!=NULL)
		p=head->next;
	while(p)
	{
		if(p->data==cur_e)
		 {
		 	if(p->next!=NULL)
		 	{
		 		//cout<<"the pre_e:"<<p->next->data<<endl;
		 	next_e=p->next->data;
		 	break;
			 }
		 	else
		 		{
		 			cout<<"no have next_e."<<endl;
		 			break;
		 		}
		 }
		if(p->next!=NULL)
		p=p->next;	
	}
}
void ListInsert_lk(LinkList &head,int i,int e)//在位置i插入元素 
{
{
	LinkList p,q,k;
	k=(LinkList)malloc(sizeof(LNode));
	k->data=e;
	int j=0;
	q=head;
	if(head->next!=NULL)
		p=head->next;
	while(p&&j<i)
	{
		j++;
		if(j==(i-1))
			{
				q=p;
				p=p->next;
				break;
			}
		else	
		p=p->next;
	}
	q->next=k;
	k->next=p;
}
void ListDelete_lk(LinkList &head,int i,int &e)//删除位置i的元素 
{
	LinkList p,q;
	int j=0;
	q=head;
	if(head->next!=NULL)
		p=head->next;
	while(p&&j<=i)
	{
		j++;
			if(j==(i-1))
			{
				q=p;
				p=p->next;
				break;
			}
		else	
		p=p->next;
	}
	e=p->data;
	cout<<"the delete element:"<<e;
	if(p->next==NULL)
		q->next=NULL;
	else
		q->next=p;
}
void ListTraverse_lk(LinkList head)//遍历所有元素 
{
	LinkList p;
	int i=1;
	if(head->next!=NULL)
		p=head->next;
	while(p)
	{
	cout<<i<<": "<<p->data<<" ";
	i++;
	p=p->next;
	}
}
void fuzhi(LinkList head,int i)//对顺序表初始化 
{
	LinkList p,q;
	p=head;
	cout<<"Please input every element:";
	for(int j=1;j<=i;j++)
	{
		q=(LNode *)malloc(sizeof(LNode));
		cin>>q->data;
		p->next=q;
		p=p->next;
	}
	p->next=NULL;
}
int main()
{
	LinkList head;
	InitList_lk(head);
	int i;
	cout<<"the total element:";
	cin>>i;
	fuzhi(head,i);
	ListTraverse_lk(head);
	cout<<endl;
	
//	cout<<"the length:"<<ListLength_lk(head)<<endl;
//	DestroyList_lk(head);
/*int t,e;
	cout<<"the location of the element what you want:";
	cin>>t;
	GetElem_lk(head,t,e);
	cout<<"the element:"<<e<<endl;*/
	
/*	int k;
	cout<<"the number which you want defining:";
	cin>>k;
	LocateElem_lk(head,k);*/

/*	int cur_e,pre_e,next_e;
	cout<<"the cur_e:";
	cin>>cur_e;
	PriorElem_lk(head,cur_e,pre_e);
	NextElem_lk(head,cur_e,next_e);
	cout<<"the pre_e:"<<pre_e<<endl;
	cout<<"the next_e:"<<next_e<<endl;*/
	
/*	int m,n;
	cout<<"the location and the element:";
	cin>>m>>n;
	ListInsert_lk(head,m,n);	*/
	
	int s,e;
	cout<<"the delete element:";
	cin>>s; 
	ListDelete_lk(head,i,e);
	cout<<"the delete element:"<<e;

	ListTraverse_lk(head);
	return 0;
}



