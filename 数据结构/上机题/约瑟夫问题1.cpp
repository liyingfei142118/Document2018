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
		p->data=i;
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
void operation(Linklist head,int s,int m)
{
	Linklist p,q;
//	if(head->next)throw("error!");
	p=head->next;
	int i=0,k=1;	
	while(p)
	{
		i++;
		if(p->data==s)
		{
			q=p;
		}
		if(p->next==NULL)
		{
			p->next=head->next;
			break;
		}
		p=p->next;
	}
	p=q;
	while(i!=0)
	{
		if(p->data!=0)
		if(k==m)
		{
			cout<<p->data<<" ";
			p->data=0;
			k=1;
			i--;
		}
		else
			k++;		
	//	if(p->next==NULL)
	//		p=head->next;
		//else
		p=p->next;				
	}
}
int main()
{
	Linklist head;//LNode head;
	Init_creat_lklist(head);
	Print_lklist(head);
	int s,m;
	cout<<"The first people who begin and the number who outqueue:";
	cin>>s>>m;
	operation(head,s,m);
	return 0;
}
