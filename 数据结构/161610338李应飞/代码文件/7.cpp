#include<iostream>
using namespace std;
#include<malloc.h> 
#include<fstream>
#include<string.h>
#define maxsize 20
#define minsize 1
#define max 1000
typedef struct hash//hash表结构体 
{
	int *elem;
	int length;
	int listsize;
}hash;
typedef struct people//记录结构体 
{
	int ID;//身份证号码 
	char name[10];//姓名 
	int code;//航班号
	int data;//航班日期
	int distance;//里程
	int vip;//VIP 
}people;
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
void Init_Hash(hash &L);
void Search_VIP(people p[],hash L,int n);//找vip客户 
void creat_wen();//创建记录文件 
void Print_people(people p[],int n);
void Creat_kHash(people p[]);//开放定址
void Print_LHash(H L[]);//打印哈希表
void Print_Hash(hash L);//打印哈希表
void Creat_LHash(people p[]);//链地址

void Init_Hash(hash &L)
{
	L.elem=(int *)malloc(maxsize*sizeof(int));
	if(!L.elem)exit(0);
	L.length=0;
	L.listsize=maxsize;
}
void Search_VIP(people p[],hash L,int n)//找vip客户 
{
	for(int i=1;i<=L.listsize;i++ )
	{
		int count,mdistance;
		if(L.elem[i]!=0)//hash表中不空 
		{	
			count=1;//频率
			int k;
			for(int s=1;s<=n;s++ )//找到对应的客户，记录位置 
			{
				if(p[s].ID==L.elem[i])
				{
					k=s;
					break;
				}
			}
			mdistance=p[k].distance;//里程数统计
			for(int j=i+1;j<=n;j++)
			{
				if(L.elem[j]==L.elem[i])
				{
					count++;
					L.elem[j]=0;
						for(int s=1;s<=n;s++ )
							{
								if(p[s].ID==L.elem[j])
								{
									k=s;
									break;
								}
							}
					mdistance+=p[k].distance;
				}
			}
			
		}
		
		for(int s=1;s<=n;s++ )
			{
				if(p[s].ID==L.elem[i])
				{
					if(count>=4&&count<8)//根据频率发掘VIP 
						p[s].vip=1;
					else if(count>=8)
					{
						p[s].vip=2;
					}
				}
				if(mdistance>100)//根据里程量发掘VIP 
					p[s].vip=1;
				else	if(mdistance>200)
					p[s].vip=2;
			}
			
			
	}
}
void Print_Hash(hash L)//打印哈希表 
{
	for(int i=1;i<=L.listsize;i++ )
	{
		cout<<L.elem[i]<<" ";
	}
	cout<<endl;
}
void creat_wen()//创建记录文件 
{
	fstream file;
	file.open("hash.dat",ios::out|ios::binary);
	if(file.fail())
	{
		cout<<"file open is error!"<<endl;
		exit(0);
	}
	int n;
	cout<<"please input n:";//创建记录 
	cin>>n;
	people p[max];
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
		file.write((char *)&p[i],sizeof(p[i]));
	}
	file.close();
	
	people f;
	file.open("hash.dat",ios::in|ios::binary);
	if(file.fail())
	{
		cout<<"file open is error!"<<endl;
		exit(0);
	}
	file.read((char *)&f,sizeof(f));
	while(!file.eof())
	{
		cout<<f.ID<<" ";
		cout<<f.name<<" ";
		cout<<f.code<<" ";
		cout<<f.data<<" ";
		cout<<f.distance<<" ";
		cout<<f.vip<<endl;
		file.read((char *)&f,sizeof(f));
	}
	file.close();
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
void Creat_kHash(people p[])//开放定址
{
	fstream file;
	people f;
	file.open("hash.dat",ios::in|ios::binary);
	if(file.fail())
	{
		cout<<"file open is error!"<<endl;
		exit(0);
	}
	file.read((char *)&f,sizeof(f));
	int n=0,i=1;
	while(!file.eof())
	{
		p[i].ID=f.ID;
		strcpy(p[i].name,f.name);
		p[i].code=f.code;
		p[i].data=f.data;
		p[i].distance=f.distance;
		p[i].vip=f.vip;
		i++;
		n++;
		file.read((char *)&f,sizeof(f));
	}
	file.close();
/*	int n;
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
	}*/
	hash L;//建立hash表和初始化 
	Init_Hash(L);
	for(int i=1;i<=L.listsize;i++ )
	{
		L.elem[i]=0;
	}
	int count=0;//count记录发生冲突的记录个数 
	for(int i=1;i<=n;i++)
	{
		int t=p[i].ID%10;
		if(L.elem[t]!=0)
		{
			count++;
			t++;
			int key=1;//key记录某个数据发生冲突的次数 
			while(L.elem[t]!=0)
			{
				key++;
				t++;//采用线性探测再散列 
			}
			L.elem[t]=p[i].ID;
			cout<<p[i].ID<<"冲突次数"<<key<<endl;
		}
		else
		{
			L.elem[t]=p[i].ID;
		}
	}
	cout<<"发生冲突的记录个数"<<count<<endl;
	Print_Hash(L);
	Print_people(p,n);
	Search_VIP(p,L,n);
	Print_Hash(L);
	Print_people(p,n);
}
void Print_LHash(H L[])//打印哈希表 
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
void Creat_LHash(people p[])//链地址
{
	fstream file;
	people f;
	file.open("hash.dat",ios::in|ios::binary);
	if(file.fail())
	{
		cout<<"file open is error!"<<endl;
		exit(0);
	}
	file.read((char *)&f,sizeof(f));
	int n=0,i=1;
	while(!file.eof())
	{
		p[i].ID=f.ID;
		strcpy(p[i].name,f.name);
		p[i].code=f.code;
		p[i].data=f.data;
		p[i].distance=f.distance;
		p[i].vip=f.vip;
		i++;
		n++;
		file.read((char *)&f,sizeof(f));
	}
	file.close();
/*	int n;
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
	}*/
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
	Print_people(p,n);
}

int main()
{
	cout<<"			Hash表应用"<<endl;
	cout<<"			1.创建文件"<<endl;
	cout<<"			2.链地址"<<endl;
	cout<<"			3.开放定址+发掘VIP客户"<<endl;
	int choice;
	cout<<"please input your choice:";
	cin>>choice;
	switch(choice)
	{
		case 1:
			system("cls");
			cout<<"			Hash表应用"<<endl;
			cout<<"			 创建文件"<<endl;
			creat_wen();
			break;
		case 2:
			system("cls");
			cout<<"			Hash表应用"<<endl;
			cout<<"			 链地址"<<endl;
			 people p1[max];
			Creat_LHash(p1);
			break;
		case 3:
			system("cls");
			cout<<"			Hash表应用"<<endl;
			cout<<"		开放定址+发掘VIP客户"<<endl;
			people p[max];
			Creat_kHash(p);
			break;
		default:
			cout<<"chioce input is error!"<<endl;
			break;
	}
	return 0;
}
