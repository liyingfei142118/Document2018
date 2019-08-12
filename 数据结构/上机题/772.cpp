/*Hash表应用 （选做） （查找）
[问题描述]
设计散列表实现VIP客户发掘。对身份证号进行Hash,
 通过对乘客某时间段内的乘机频率、里程数统计，发掘VIP客户。 
[基本要求]
（1） 设每个记录有下列数据项：身份证号码（虚构，位数和编码规则与真实一致即可）、
姓名、航班号、航班日期、里程。 
（2） 从文件输入各记录，以身份证号码为关键字建立散列表。 
（3） 分别采用开放定址（自行选择和设计定址方案）和链地址两种方案解决冲突；
显示发生冲突的次数、每次中解决冲突进行重定位的次数。
（4）记录条数至少在100条以上。
（5） 从记录中实现乘客乘机频率、里程数统计，从而发掘VIP客户。*/
#include<iostream>
using namespace std;
#include<malloc.h> 
#define maxsize 20
#define minsize 1
#define max 1000
typedef struct Hash//hash表结构体 
{
	int elem;
	struct Hash *next;
}Hash,*LHash;
typedef struct H
{
	int data;
	Hash *first;	
}H;
typedef struct people//记录结构体 
{
	int ID;//身份证号码 
	char name[10];//姓名 
	int code;//航班号
	int data;//航班日期
	int distance;//里程
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
	cout<<"please input n:";//创建记录 
	cin>>n;
	cout<<"please input every information:"<<endl;//输入记录 
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
	H L[max];//建立hash表和初始化 
	for(int i=1;i<=maxsize;i++ )
	{
		
		L[i].data=i;
		L[i].first=NULL;
	}
	int count=0;//count记录发生冲突的记录个数 
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
	cout<<"发生冲突的记录个数"<<count<<endl;
	Print_LHash(L);
//	Print_people(p,n);
}
int main()
{
	people p[max];
	Creat_LHash(p);
	return 0;
}
