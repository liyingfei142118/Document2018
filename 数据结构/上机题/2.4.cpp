#include<iostream>
using namespace std;
#include<malloc.h>
typedef struct LNode
{
	int data;
	struct LNode *next;
}LNode,*Linklist ;
void Init_creat_lklist(Linklist &head)//����������ֵ 
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
void Print_lklist(Linklist head)//��ӡ���� 
{
	if(head->next==NULL)throw("no data!");
	Linklist p;
	p=head->next;
	int i=0;
	while(p!=NULL)
	{
		if(i%5==0)//ÿ�����5������ 
		cout<<endl;
		cout<<p->data<<" ";
		p=p->next;
		i++;
	}
}
void Combine_array(Linklist &head,Linklist head1)//�ϲ����� 
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
				k->data=q->data;//k�������Ǵ�q�е����ݲ�ʵ���书��	
			if(k->data==p->data) 
			{				
				break;//�����ȣ�������ѭ�� 
			}	
			if(k->data<=p->data)//�������в��� 
			{				
					m->next=k;
					k->next=p;
				break;//������룬������ѭ�� 
			}
			if(p->next==NULL&&p->data<=k->data)//������β 
			{
				p->next=k;
				k->next=NULL;
				break;//������룬������ѭ�� 
			}
			m=p;//mΪp��ǰλ�õ�ǰһ��λ�á� 
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
