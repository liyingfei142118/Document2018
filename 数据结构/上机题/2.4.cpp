#include<iostream>
using namespace std;
#include<malloc.h>
typedef struct LNode
{
	int data;
	struct LNode *next;
}LNode,*Linklist ;
void Init_creat_lklist(Linklist &head)//创建链表并赋值 
{
	head=(LNode *)malloc(sizeof(LNode));
	if(!head)throw("error!");
	head->next=NULL;
	int n;
	cout<<"Please input the data number:";
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
void Print_lklist(Linklist head)//打印链表 
{
	if(head->next==NULL)throw("no data!");
	Linklist p;
	p=head->next;
	int i=0;
	while(p!=NULL)
	{
		if(i%5==0)//每行输出5个数据 
		cout<<endl;
		cout<<p->data<<" ";
		p=p->next;
		i++;
	}
}
void Combine_array(Linklist &head,Linklist head1)//合并链表 
{
	Linklist p,q,m;
	m=head;
	if(head->next!=NULL)
		p=head->next;
	if(head1->next!=NULL)
		q=head1->next;
	while(q)
	{
		while(p)
		{
			Linklist k;
			k=(LNode *)malloc(sizeof(LNode));
			if(!k)throw("error!");
					k->next=NULL;
				k->data=q->data;//k的作用是存q中的数据并实现其功能	
			if(k->data==p->data) 
			{				
				break;//如果相等，结束此循环 
			}	
			if(k->data<=p->data)//在链表中插入 
			{				
					m->next=k;
					k->next=p;
				break;//如果插入，结束此循环 
			}
			if(p->next==NULL&&p->data<=k->data)//在链表尾 
			{
				p->next=k;
				k->next=NULL;
				break;//如果插入，结束此循环 
			}
			m=p;//m为p当前位置的前一个位置。 
			p=p->next;
		}
		q=q->next;
	}
}
int main()
{
	Linklist head,head1;
	
	Init_creat_lklist(head);
	Print_lklist(head);
	cout<<endl; 
	
	Init_creat_lklist(head1);
	Print_lklist(head1);
	cout<<endl; 
	
	Combine_array(head,head1);
	Print_lklist(head);
	return 0;
}
