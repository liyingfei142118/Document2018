/*Hash��Ӧ�� ��ѡ���� �����ң�
[��������]
���ɢ�б�ʵ��VIP�ͻ����򡣶����֤�Ž���Hash,
 ͨ���Գ˿�ĳʱ����ڵĳ˻�Ƶ�ʡ������ͳ�ƣ�����VIP�ͻ��� 
[����Ҫ��]
��1�� ��ÿ����¼��������������֤���루�鹹��λ���ͱ����������ʵһ�¼��ɣ���
����������š��������ڡ���̡� 
��2�� ���ļ��������¼�������֤����Ϊ�ؼ��ֽ���ɢ�б� 
��3�� �ֱ���ÿ��Ŷ�ַ������ѡ�����ƶ�ַ������������ַ���ַ��������ͻ��
��ʾ������ͻ�Ĵ�����ÿ���н����ͻ�����ض�λ�Ĵ�����
��4����¼����������100�����ϡ�
��5�� �Ӽ�¼��ʵ�ֳ˿ͳ˻�Ƶ�ʡ������ͳ�ƣ��Ӷ�����VIP�ͻ���*/
#include<iostream>
using namespace std;
#include<malloc.h> 
#define maxsize 20
#define minsize 1
#define max 1000
typedef struct Hash//hash��ṹ�� 
{
	int elem;
	struct Hash *next;
}Hash,*LHash;
typedef struct H
{
	int data;
	Hash *first;	
}H;
typedef struct people//��¼�ṹ�� 
{
	int ID;//���֤���� 
	char name[10];//���� 
	int code;//�����
	int data;//��������
	int distance;//���
	int vip;//VIP 
}people;


void Print_LHash(H L[])
{
	for(int i=1;i<=maxsize;i++ )
	{
		Hash *p;
		cout<<L[i].data<<":";
		p=L[i].first;
		while(p)
		{
			cout<<p->elem<<" ";
			p=p->next;
		}
		cout<<endl;
	
	}
}
void Print_people(people p[],int n)
{
	for(int i=1;i<=n;i++ )
	{
		cout<<p[i].ID<<" ";
		cout<<p[i].name<<" ";
		cout<<p[i].code<<" ";
		cout<<p[i].data<<" ";
		cout<<p[i].distance<<" ";
		cout<<p[i].vip<<endl;
	}
}
void Creat_LHash(people p[])
{
	int n;
	cout<<"please input n:";//������¼ 
	cin>>n;
	cout<<"please input every information:"<<endl;//�����¼ 
	cout<<"ID name code data distance:"<<endl;
	for(int i=1;i<=n;i++ )
	{
		cin>>p[i].ID;
		cin>>p[i].name;
		cin>>p[i].code;
		cin>>p[i].data;
		cin>>p[i].distance;
		p[i].vip=0;
	}
	H L[max];//����hash��ͳ�ʼ�� 
	for(int i=1;i<=maxsize;i++ )
	{
		
		L[i].data=i;
		L[i].first=NULL;
	}
	int count=0;//count��¼������ͻ�ļ�¼���� 
	for(int i=1;i<=n;i++)
	{
		int t=p[i].ID%10;
		if(L[t].first!=NULL)
		{
			count++;
			Hash *q,*s,*p1=L[t].first;
			s=(Hash *)malloc(sizeof(Hash));
			s->elem=p[i].ID;
			s->next=NULL;
			while(p1)
			{
				q=p1;
				p1=p1->next;
			}
			q->next=s;
;
		}
		else
		{
			Hash *q=(Hash *)malloc(sizeof(Hash));
			q->elem =p[i].ID;
			L[t].first=q;
			q->next=NULL;		
		}
	}
	cout<<"������ͻ�ļ�¼����"<<count<<endl;
	Print_LHash(L);
//	Print_people(p,n);
}
int main()
{
	people p[max];
	Creat_LHash(p);
	return 0;
}
