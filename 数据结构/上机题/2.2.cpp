#include<iostream>
using namespace std;
#include<malloc.h>
typedef struct LNode
{
	int data;
	struct LNode *next;
}LNode,*Linklist ;
void Init_creat_lklist(Linklist &head)////创建单链表
{
	head=(LNode *)malloc(sizeof(LNode));
	if(!head)throw("error!");
	head->next=NULL;
	int n;
	cout<<"Please input the data number:";//初始化单链表 
	cin>>n;
	Linklist p,q;
	q=head;
	for(int i=1;i<=n;i++)
	{
		p=(LNode *)malloc(sizeof(LNode));
		cin>>p->data;
		q->next=p;
		q=p;
	}
	q->next=NULL;
	 
}
void Print_lklist(Linklist head)//打印单链表 
{
	if(head->next==NULL)throw("no data!");
	Linklist p;
	p=head->next;
	int i=0;
	while(p!=NULL)
	{
		if(i%5==0)
		cout<<endl;
		cout<<p->data<<" ";
		p=p->next;
		i++;
	}
}
void Insert_lk(Linklist &head,int e)//将e插入到链表中 
{
	cout<<endl;
	Print_lklist(head);	
	Linklist m,n,k;//m为当前指针,n当前指针的前一个指针,k带插指针,s保留原来的m 
		k=(Linklist)malloc(sizeof(LNode));//开辟 
		k->data=e;
		n=head;
		m=head->next;
		while(m)
		{
			if(k->data<=m->data)//如果小于 
				{
					n->next=k;
					k->next=m;
					break;
				}
			if(k->data>m->data&&m->next==NULL)//如果大于 
				{
					m->next=k;
					k->next=NULL;
					break;
				}
				n=m;
				m=m->next;	
		}	
}
void Insert_arrary_lk(Linklist &head)//插入排序 
{
	Linklist p,q;
	if(head->next!=NULL)
	{
		p=head->next;
	}
	else
	{
		exit(0);
	}
	head->next=NULL;
	while(p)
	{	q=(Linklist)malloc(sizeof(LNode));
		q->data=p->data;
		if(head->next==NULL)
			{
				head->next=q;
				q->next=NULL;
				Print_lklist(head);		
			}			
		else
			Insert_lk(head,q->data);	
		p=p->next;				
	}
}

int main()
{
	Linklist head;
	Init_creat_lklist(head);
	Print_lklist(head);
	Insert_arrary_lk(head);
	Print_lklist(head);
	return 0;
}
