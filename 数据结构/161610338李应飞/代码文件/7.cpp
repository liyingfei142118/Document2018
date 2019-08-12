#include<iostream>
using namespace std;
#include<malloc.h> 
#include<fstream>
#include<string.h>
#define maxsize 20
#define minsize 1
#define max 1000
typedef struct hash//hash��ṹ�� 
{
	int *elem;
	int length;
	int listsize;
}hash;
typedef struct people//��¼�ṹ�� 
{
	int ID;//���֤���� 
	char name[10];//���� 
	int code;//�����
	int data;//��������
	int distance;//���
	int vip;//VIP 
}people;
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
void Init_Hash(hash &L);
void Search_VIP(people p[],hash L,int n);//��vip�ͻ� 
void creat_wen();//������¼�ļ� 
void Print_people(people p[],int n);
void Creat_kHash(people p[]);//���Ŷ�ַ
void Print_LHash(H L[]);//��ӡ��ϣ��
void Print_Hash(hash L);//��ӡ��ϣ��
void Creat_LHash(people p[]);//����ַ

void Init_Hash(hash &L)
{
	L.elem=(int *)malloc(maxsize*sizeof(int));
	if(!L.elem)exit(0);
	L.length=0;
	L.listsize=maxsize;
}
void Search_VIP(people p[],hash L,int n)//��vip�ͻ� 
{
	for(int i=1;i<=L.listsize;i++ )
	{
		int count,mdistance;
		if(L.elem[i]!=0)//hash���в��� 
		{	
			count=1;//Ƶ��
			int k;
			for(int s=1;s<=n;s++ )//�ҵ���Ӧ�Ŀͻ�����¼λ�� 
			{
				if(p[s].ID==L.elem[i])
				{
					k=s;
					break;
				}
			}
			mdistance=p[k].distance;//�����ͳ��
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
					if(count>=4&&count<8)//����Ƶ�ʷ���VIP 
						p[s].vip=1;
					else if(count>=8)
					{
						p[s].vip=2;
					}
				}
				if(mdistance>100)//�������������VIP 
					p[s].vip=1;
				else	if(mdistance>200)
					p[s].vip=2;
			}
			
			
	}
}
void Print_Hash(hash L)//��ӡ��ϣ�� 
{
	for(int i=1;i<=L.listsize;i++ )
	{
		cout<<L.elem[i]<<" ";
	}
	cout<<endl;
}
void creat_wen()//������¼�ļ� 
{
	fstream file;
	file.open("hash.dat",ios::out|ios::binary);
	if(file.fail())
	{
		cout<<"file open is error!"<<endl;
		exit(0);
	}
	int n;
	cout<<"please input n:";//������¼ 
	cin>>n;
	people p[max];
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
void Creat_kHash(people p[])//���Ŷ�ַ
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
	}*/
	hash L;//����hash��ͳ�ʼ�� 
	Init_Hash(L);
	for(int i=1;i<=L.listsize;i++ )
	{
		L.elem[i]=0;
	}
	int count=0;//count��¼������ͻ�ļ�¼���� 
	for(int i=1;i<=n;i++)
	{
		int t=p[i].ID%10;
		if(L.elem[t]!=0)
		{
			count++;
			t++;
			int key=1;//key��¼ĳ�����ݷ�����ͻ�Ĵ��� 
			while(L.elem[t]!=0)
			{
				key++;
				t++;//��������̽����ɢ�� 
			}
			L.elem[t]=p[i].ID;
			cout<<p[i].ID<<"��ͻ����"<<key<<endl;
		}
		else
		{
			L.elem[t]=p[i].ID;
		}
	}
	cout<<"������ͻ�ļ�¼����"<<count<<endl;
	Print_Hash(L);
	Print_people(p,n);
	Search_VIP(p,L,n);
	Print_Hash(L);
	Print_people(p,n);
}
void Print_LHash(H L[])//��ӡ��ϣ�� 
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
void Creat_LHash(people p[])//����ַ
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
	}*/
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
	Print_people(p,n);
}

int main()
{
	cout<<"			Hash��Ӧ��"<<endl;
	cout<<"			1.�����ļ�"<<endl;
	cout<<"			2.����ַ"<<endl;
	cout<<"			3.���Ŷ�ַ+����VIP�ͻ�"<<endl;
	int choice;
	cout<<"please input your choice:";
	cin>>choice;
	switch(choice)
	{
		case 1:
			system("cls");
			cout<<"			Hash��Ӧ��"<<endl;
			cout<<"			 �����ļ�"<<endl;
			creat_wen();
			break;
		case 2:
			system("cls");
			cout<<"			Hash��Ӧ��"<<endl;
			cout<<"			 ����ַ"<<endl;
			 people p1[max];
			Creat_LHash(p1);
			break;
		case 3:
			system("cls");
			cout<<"			Hash��Ӧ��"<<endl;
			cout<<"		���Ŷ�ַ+����VIP�ͻ�"<<endl;
			people p[max];
			Creat_kHash(p);
			break;
		default:
			cout<<"chioce input is error!"<<endl;
			break;
	}
	return 0;
}
