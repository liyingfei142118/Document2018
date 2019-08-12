#include<iostream>
using namespace std;
#include<malloc.h>
typedef struct LNode
{
	int data;
	struct LNode *next;
}LNode,*Linklist ;
void Init_creat_lklist(Linklist &head)
{
	head=(LNode *)malloc(sizeof(LNode));
	if(!head)throw("error!");
	head->next=NULL;
	int n;
	//int shuzi;
	cout<<"Please input the data number:";
	cin>>n;
	Linklist p,q;
	q=head;
	for(int i=1;i<=n;i++)
	{
		p=(LNode *)malloc(sizeof(LNode));
		cin>>p->data;
	//	cin>>shuzi;
		//p->data=shuzi;
		q->next=p;
		q=p;
	}
	q->next=NULL;
	 
}
void Print_lklist(Linklist head)
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
void Daozhi_lklist(Linklist &head)
{
	Linklist p,q;
	if(head->next!=NULL)
		p=head->next;
		head->next=NULL;
	while(p!=NULL)
	{
		q=p->next;
		p->next=head->next;
		head->next=p;
		p=q;
	}
}

int main()
{
	Linklist head;//LNode head;
	Init_creat_lklist(head);
	Print_lklist(head);
	Daozhi_lklist(head);
	Print_lklist(head);
	return 0;
}
