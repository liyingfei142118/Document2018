#include<iostream>
using namespace std;
#include<malloc.h>
#include<string.h>
#include<fstream>
#include<windows.h>



typedef struct Node//����Ʒ�Ľṹ�� 
{
	int code;//���̱��
	char name1[10];//��Ʒ����
	int price;//�۸�
	int output;//����
}Node;
typedef struct Thing//��Ʒ 
{
	char name1[10];//��Ʒ����
	int price;//�۸�
	int output;//����
	struct Thing *next;//��һ����Ʒ 
}Thing,*LThing;

typedef struct GNode//���� 
{
	int code;//���̱�� 
	char name[10];//������ 
	int degree;//������
	LThing first;
	struct GNode *down;//��һ������ 
}GNode,*LGNode;
typedef struct OneNode//ѭ������ṹ�� 
{
	int code;//���̱�� 
	char name[10];//������ 
	int degree;//������
	char name1[10];//��Ʒ����
	int price;//�۸�
	int output;//����
	struct OneNode *prior;
	struct OneNode *next;
} Link,*Linklist;

void Init_LinkThing(Linklist &head);//��ʼ��ѭ������ 
void Print_Onething(Linklist &head);//��ӡѭ������
void Creat_Onething(Linklist &head,LGNode head1,char *c);//����ѭ�������ѯĳһ����Ʒ
void Paixu_Onething(Linklist &head);//���� ������   
void Init_Thing(LGNode &head);//�������̺���Ʒ�Ŀռ�
void Creat_Thing(LGNode &head);//�������� 
void En_Thing();//��������
void De_Thing();//ɾ������ 
void En_GNode();//������Ʒ 
void De_GNode();//ɾ����Ʒ
void Creat_GNode(LGNode &head);////������Ʒ 
void Print_Thing();//��ӡ���̺���Ʒ 
void Eidt_Price();//�޸ļ۸�
void Buy_GNode();//����Ʒ ����++ 
void Init_LinkThing(Linklist &head)//��ʼ��ѭ������ 
{
	head=(Linklist)malloc(sizeof(Link));
	if(!head)exit(0);
	head->next=NULL;
	head->prior=NULL;
}
void Print_Onething(Linklist &head)//��ӡѭ������ 
{
	Linklist s;
	s=head;
	int k=1;
	while(s&&k)
	{
			cout<<"���̱�ţ�"<<s->code<<"�������ƣ�"<<s->name<<"���������ȣ�"<<s->degree<<endl;
			cout<<"��Ʒ���ƣ�"<<s->name1<<"��Ʒ�۸�"<<s->price<<"��Ʒ������"<<s->output<<endl;
			s=s->next;
			if(s==head)
				k=0;
	}
	
}
void Creat_Onething(Linklist &head,LGNode head1,char *c)//����ѭ�������ѯĳһ����Ʒ 
{
	LGNode q,q1;
	LThing p,p1;
	Linklist s,s1;
	if(!head)exit(0);
	if(!head1)exit(0);	
	q=head1->down;
	int key=0;
	while(q)
	{
		p=q->first;
	
		while(p)
		{
			if(!strcmp(p->name1,c))
			{
				if(key==0)
				{
						head->code=q->code;
						head->degree=q->degree;
						strcpy(head->name,q->name);
						strcpy(head->name1,p->name1);
						head->price=p->price;
						head->output=p->price;
						head->next=head->prior=head;
						key++;
						s=head;
					}
					else
					{
						s1=s;
						s=(Linklist)malloc(sizeof(Link));
						
						s->code=q->code;
							s->degree=q->degree;
							strcpy(s->name,q->name);
							strcpy(s->name1,p->name1);
							s->price=p->price;
							s->output=p->output;
							s1->next=s;
							s->next=head;
							s->prior=s1;
							head->prior=s;
						
					}
					break;
				}
				else
						{
							p=p->next;
						}
		}
	q=q->down;
	}
}
void Paixu_Onething(Linklist &head)//���� ������ 
{//������ 
	Linklist s,s1,s2;
	if(!head)exit(0);
	
	if(head->next)
		s=head->next;
		s2=head;
	while(s)
		{
			if(s2->output<=s->output)
			{
			s1=head;
			while(s1&&(s1!=s))
			{
				if(s->output<s1->output)
				{
					s1->next=s;
					s->prior=s1;
					s->next=s1->next;
					s1->next->prior=s;
				}
				else
				{
					s1=s1->next;
				}
			}
			}
			s2=s2->next;
			s=s->next;	
		}
}

void Init_Thing(LGNode &head)//�������̺���Ʒ�Ŀռ� 
{
	head=(LGNode)malloc(sizeof(GNode));
	if(!head)exit(0);
	head->down=NULL;
}
void Creat_Thing(LGNode &head)//�������� 
{
	fstream file("shangpu.dat",ios::out|ios::binary);
	if(file.fail())
	{
		cout<<"file open is error!"<<endl;
		exit(0);
	}
	cout<<"���������̣����̱�ţ��������������ȣ���"<<endl;
	LGNode p,q;
	GNode f;
	p=head;
	int key=1;
	while(key)
	{
		q=(LGNode)malloc(sizeof(GNode));
		cin>>q->code;//�������̱�� 
		cin>>q->name;//���������� 
		cin>>q->degree;//����������	
		q->first=NULL;//��Ʒָ���ÿ� 
		q->down=NULL;
		f.code=q->code;
		f.degree=q->degree;
		strcpy(f.name,q->name);
		f.first=q->first;
		f.down=q->down;
		file.write((char *)&f,sizeof(f));
		p->down=q;//headΪ�� 
		p=q;	
		int data;//�ж��Ƿ�������� 
		cout<<endl;
		cout<<"if continue , please input 1 or 0.: ";
		cin>>data;
		cout<<endl;
		if(data==0)
		{
			break;
		}
		
	}
	file.close();

	cout<<endl;
	file.open("shangpu.dat",ios::in|ios::binary);
	if(file.fail())
	{
		cout<<"file open is error!"<<endl;
		exit(0);
	}
	file.read((char *)&f,sizeof(f));
	while(!file.eof())
	{
			cout<<"���̱�ţ�"<<f.code<<"�������ƣ�"<<f.name<<"���������ȣ�"<<f.degree<<endl;	
			file.read((char *)&f,sizeof(f));
	}
	file.close();
}
void En_Thing( )//��������
{
	fstream file;
	GNode f;
	cout<<endl;
	file.open("shangpu.dat",ios::in|ios::binary);
	if(file.fail())
	{
		cout<<"file open is error!"<<endl;
		exit(0);
	}
	file.read((char *)&f,sizeof(f));
	while(!file.eof())
	{
			cout<<"���̱�ţ�"<<f.code<<"�������ƣ�"<<f.name<<"���������ȣ�"<<f.degree<<endl;	
			file.read((char *)&f,sizeof(f));
	}
	file.close();
	
	file.open("shangpu.dat",ios::in|ios::binary);
	if(file.fail())
	{
		cout<<"file open is error!"<<endl;
		exit(0);
	}
	file.read((char *)&f,sizeof(f));
	int k;
	while(!file.eof())
	{
		k=f.code;
		file.read((char *)&f,sizeof(f));
	}
	file.close();
	
	file.open("shangpu.dat",ios::app|ios::binary);
	if(file.fail())
	{
		cout<<"file open is error!"<<endl;
		exit(0);
	}
	GNode ff;
		cout<<"please input ������ ������:";
		k++;
		ff.code=k;
		cin>>ff.name;
		cin>>ff.degree;	
		ff.first=NULL;
		ff.down=NULL;
		file.write((char *)&ff,sizeof(ff));
	file.close();
	
	cout<<endl;
	file.open("shangpu.dat",ios::in|ios::binary);
	if(file.fail())
	{
		cout<<"file open is error!"<<endl;
		exit(0);
	}
	file.read((char *)&f,sizeof(f));
	while(!file.eof())
	{
			cout<<"���̱�ţ�"<<f.code<<"�������ƣ�"<<f.name<<"���������ȣ�"<<f.degree<<endl;	
			file.read((char *)&f,sizeof(f));
	}
	file.close();
}
void De_Thing_GN(int code)//ɾ������ ��Ӧ��ɾ����Ʒ 
{
	fstream file,file1;
	Node f;
	file.open("wuping.dat",ios::in|ios::binary);
	file1.open("wuping1.dat",ios::out|ios::binary);
	if(file.fail())
	{
		cout<<"file open is error!"<<endl;
		exit(0);
	}
	if(file1.fail())
	{
		cout<<"file1 open is error!"<<endl;
		exit(0);
	}
	
	file.read((char *)&f,sizeof(f));//ɾ������ 
	while(!file.eof())
	{
		if(f.code!=code)
			file1.write((char *)&f,sizeof(f));
		file.read((char *)&f,sizeof(f));
	}
	file.close();
	file1.close();
	
	file.open("wuping.dat",ios::out|ios::binary);//�ļ����� 
	file1.open("wuping1.dat",ios::in|ios::binary);
	if(file.fail())
	{
		cout<<"file open is error!"<<endl;
		exit(0);
	}
	if(file1.fail())
	{
		cout<<"file1 open is error!"<<endl;
		exit(0);
	}
	file1.read((char *)&f,sizeof(f));
	while(!file1.eof())
	{
		
		file.write((char *)&f,sizeof(f));
		file1.read((char *)&f,sizeof(f));
	}
	file.close();
	file1.close();
	
	cout<<endl;
	file.open("wuping.dat",ios::in|ios::binary);
	if(file.fail())
	{
		cout<<"file open is error!"<<endl;
		exit(0);
	}
	file.read((char *)&f,sizeof(f));
	while(!file.eof())
	{
			cout<<"���̱�ţ�"<<f.code<<"��Ʒ���ƣ�"<<f.name1<<"��Ʒ�۸�"<<f.price<<"��Ʒ������"<<f.output<<endl;	
			file.read((char *)&f,sizeof(f));
	}
	file.close();
}
void De_Thing()//ɾ������ 
{//�����ļ� 
	int code;
	cout<<"please input the code:";
	cin>>code;
	fstream file,file1;
	GNode f;
	cout<<endl;
	file.open("shangpu.dat",ios::in|ios::binary);
	file1.open("shangpu1.dat",ios::out|ios::binary);
	if(file.fail())
	{
		cout<<"file open is error!"<<endl;
		exit(0);
	}
	if(file1.fail())
	{
		cout<<"file1 open is error!"<<endl;
		exit(0);
	}
	
	file.read((char *)&f,sizeof(f));//ɾ������ 
	while(!file.eof())
	{
		if(f.code!=code)
		{
			if(f.code>code)//���̱��-- 
				f.code--;
			file1.write((char *)&f,sizeof(f));
		} 
			
		file.read((char *)&f,sizeof(f));
	}
	file.close();
	file1.close();
	
	file.open("shangpu.dat",ios::out|ios::binary);//�ļ����� 
	file1.open("shangpu1.dat",ios::in|ios::binary);
	if(file.fail())
	{
		cout<<"file open is error!"<<endl;
		exit(0);
	}
	if(file1.fail())
	{
		cout<<"file1 open is error!"<<endl;
		exit(0);
	}
	file1.read((char *)&f,sizeof(f));
	while(!file1.eof())
	{
		
		file.write((char *)&f,sizeof(f));
		file1.read((char *)&f,sizeof(f));
	}
	file.close();
	file1.close();
	
	cout<<endl;//���ļ���� 
	file.open("shangpu.dat",ios::in|ios::binary);
	if(file.fail())
	{
		cout<<"file open is error!"<<endl;
		exit(0);
	}
	file.read((char *)&f,sizeof(f));
	while(!file.eof())
	{
			cout<<"���̱�ţ�"<<f.code<<"�������ƣ�"<<f.name<<"���������ȣ�"<<f.degree<<endl;	
			file.read((char *)&f,sizeof(f));
	}
	file.close();
	De_Thing_GN(code);
}
void En_GNode()//������Ʒ 
{
	fstream file("wuping.dat",ios::app|ios::binary);
	if(file.fail())
	{
		cout<<"file open is error!"<<endl;
		exit(0);
	}
	Node f;
	cout<<"please input shangpu's code:";
	cin>>f.code;
	cout<<"��������Ʒ���ƣ��۸�������"<<endl;
	cin>>f.name1;
	cin>>f.output;
	cin>>f.price;
	file.write((char *)&f,sizeof(f));
	file.close();
	
	cout<<endl;
	file.open("wuping.dat",ios::in|ios::binary);
	if(file.fail())
	{
		cout<<"file open is error!"<<endl;
		exit(0);
	}
	file.read((char *)&f,sizeof(f));
	while(!file.eof())
	{
			cout<<"���̱�ţ�"<<f.code<<"��Ʒ���ƣ�"<<f.name1<<"��Ʒ�۸�"<<f.price<<"��Ʒ������"<<f.output<<endl;	
			file.read((char *)&f,sizeof(f));
	}
	file.close();
}
void De_GNode()
///void De_GNode(LGNode &head,char *c)//ɾ����Ʒ 
{
	fstream file,file1;
	Node f;
	int code;
	char name[10]; 
	cout<<"please input shangpu'code  wp'name:";
	cin>>code;
	cin>>name;
	file.open("wuping.dat",ios::in|ios::binary);
	file1.open("wuping1.dat",ios::out|ios::binary);
	if(file.fail())
	{
		cout<<"file open is error!"<<endl;
		exit(0);
	}
	if(file1.fail())
	{
		cout<<"file1 open is error!"<<endl;
		exit(0);
	}
	
	file.read((char *)&f,sizeof(f));//ɾ����Ʒ  
	while(!file.eof())
	{
		if(f.code!=code&&strcmp(f.name1,name))
			file1.write((char *)&f,sizeof(f));
		file.read((char *)&f,sizeof(f));
	}
	file.close();
	file1.close();
	
	file.open("wuping.dat",ios::out|ios::binary);//�ļ����� 
	file1.open("wuping1.dat",ios::in|ios::binary);
	if(file.fail())
	{
		cout<<"file open is error!"<<endl;
		exit(0);
	}
	if(file1.fail())
	{
		cout<<"file1 open is error!"<<endl;
		exit(0);
	}
	file1.read((char *)&f,sizeof(f));
	while(!file1.eof())
	{
		
		file.write((char *)&f,sizeof(f));
		file1.read((char *)&f,sizeof(f));
	}
	file.close();
	file1.close();
	
	cout<<endl;
	file.open("wuping.dat",ios::in|ios::binary);
	if(file.fail())
	{
		cout<<"file open is error!"<<endl;
		exit(0);
	}
	file.read((char *)&f,sizeof(f));
	while(!file.eof())
	{
			cout<<"���̱�ţ�"<<f.code<<"��Ʒ���ƣ�"<<f.name1<<"��Ʒ�۸�"<<f.price<<"��Ʒ������"<<f.output<<endl;	
			file.read((char *)&f,sizeof(f));
	}
	file.close();
/*	LGNode q;
	if(!head->down)exit(0);	
	q=head->down;
	LThing p,p1;
	while(q)
	{
		p1=p=q->first;
		if(!strcmp(p->name1,c))
			{
				q->first=p->next;
				free(p);
			}
		else
		{
			p=p->next;
			while(p)
			{
					if(!strcmp(p->name1,c))
					{
						p1->next=p->next;
						free(p);
						break;
					}	
					else
					{
						p=p->next;
						p1=p1->next;
					}
				
				
			}
			
		}
		q=q->down;
	}*/
}
void Creat_GNode(LGNode &head)////������Ʒ 
{

	fstream file("wuping.dat",ios::out|ios::binary);
	if(file.fail())
	{
		cout<<"file open is error!"<<endl;
		exit(0);
	}
	Node f;
	LGNode q;
	if(!head->down)exit(0);
	q=head->down;
	
	//cout<<q->code<<endl;
	cout<<"��������Ʒ���ƣ��۸�������"<<endl;
	
	int key1=1;
	LThing T,p1;//���ٿռ����Ʒ��Ϣ
	char n[12];
	int pr,out;
	while(key1)
	{

		cin>>n;
		cin>>pr>>out;
		
		f.code=q->code; 
		T=(Thing *)malloc(sizeof(Thing));
		strcpy(T->name1,n);//��Ʒ����
		strcpy(f.name1,n);
		T->price=pr;//�۸�
		f.price=pr;
		T->output=out;//����
		f.output=out;
		T->next=NULL;
		//β�巨
		file.write((char *)&f,sizeof(f));
		if(q->first==NULL) 
		 	q->first=T;//first���� 
		 else
		 {
		 	p1=q->first;
		 	while(p1->next)
		 		p1=p1->next;
		 	p1->next=T;	 
		 }
		//cout<<"2"<<endl;
		int data;
		cout<<endl;
		cout<<"if continue?please input 1 or 2 or 3:";
		cin>>data;
		cout<<endl;
		switch(data)
		{
			case 1://���������Ʒ 
				{
					break;
				}
			case 2://�����һ��������Ʒ��Ϣ 
				{
						q=q->down;
						if(!q)
							key1=0;
						break;
				}
			case 3://���� 
			{
				key1=0;
				break;
			}		
		}

	}
	file.close();
	
	cout<<endl;
	file.open("wuping.dat",ios::in|ios::binary);
	if(file.fail())
	{
		cout<<"file open is error!"<<endl;
		exit(0);
	}
	file.read((char *)&f,sizeof(f));
	while(!file.eof())
	{
			cout<<"���̱�ţ�"<<f.code<<"��Ʒ���ƣ�"<<f.name1<<"��Ʒ�۸�"<<f.price<<"��Ʒ������"<<f.output<<endl;	
			file.read((char *)&f,sizeof(f));
	}
	file.close();
}
void Print_Thing()
//void Print_Thing(LGNode head)//��ӡ���̺���Ʒ 
{
	fstream file;
	GNode s;
	file.open("shangpu.dat",ios::in|ios::binary);
	if(file.fail())
	{
		cout<<"file open is error!"<<endl;
		exit(0);
	}
	file.read((char *)&s,sizeof(s));
	while(!file.eof())
	{
			cout<<"���̱�ţ�"<<s.code<<"�������ƣ�"<<s.name<<"���������ȣ�"<<s.degree<<endl;	
			file.read((char *)&s,sizeof(s));
	}
	file.close();
	
	Node f;
	file.open("wuping.dat",ios::in|ios::binary);
	if(file.fail())
	{
		cout<<"file open is error!"<<endl;
		exit(0);
	}
	file.read((char *)&f,sizeof(f));
	while(!file.eof())
	{
			cout<<"���̱�ţ�"<<f.code<<"��Ʒ���ƣ�"<<f.name1<<"��Ʒ�۸�"<<f.price<<"��Ʒ������"<<f.output<<endl;	
			file.read((char *)&f,sizeof(f));
	}
	file.close();
/*	LGNode p;
	p=head->down;
	if(p==NULL)exit(0);
	while(p)
	{
		
		cout<<"���̱�ţ�"<<p->code<<"�������ƣ�"<<p->name<<"���������ȣ�"<<p->degree<<endl;
		LThing T;
		T=p->first;
		while(T)
		{
			cout<<"��Ʒ���ƣ�"<<T->name1<<"��Ʒ�۸�"<<T->price<<"��Ʒ������"<<T->output<<endl;
			T=T->next;
		}
		p=p->down;
	}*/
}
void Eidt_Price()
//void Eidt_Price(LGNode &head,char *a,int pr)//�޸ļ۸� 
{
	fstream file,file1;
	Node f;
	int code;
	char name[10]; 
	cout<<"please input shangpu'code  wp'name:";
	cin>>code;
	cin>>name;
	file.open("wuping.dat",ios::in|ios::binary);
	file1.open("wuping1.dat",ios::out|ios::binary);
	if(file.fail())
	{
		cout<<"file open is error!"<<endl;
		exit(0);
	}
	if(file1.fail())
	{
		cout<<"file1 open is error!"<<endl;
		exit(0);
	}
	
	file.read((char *)&f,sizeof(f));  
	while(!file.eof())
	{
		if(f.code==code&&!strcmp(f.name1,name))
			{
				int pr;
				cout<<"please input the new price:";
				cin>>pr;
				f.price=pr;
			}
		file1.write((char *)&f,sizeof(f));
		file.read((char *)&f,sizeof(f));
	}
	file.close();
	file1.close();
	
	file.open("wuping.dat",ios::out|ios::binary);//�ļ����� 
	file1.open("wuping1.dat",ios::in|ios::binary);
	if(file.fail())
	{
		cout<<"file open is error!"<<endl;
		exit(0);
	}
	if(file1.fail())
	{
		cout<<"file1 open is error!"<<endl;
		exit(0);
	}
	file1.read((char *)&f,sizeof(f));
	while(!file1.eof())
	{
		
		file.write((char *)&f,sizeof(f));
		file1.read((char *)&f,sizeof(f));
	}
	file.close();
	file1.close();
	
	cout<<endl;
	file.open("wuping.dat",ios::in|ios::binary);
	if(file.fail())
	{
		cout<<"file open is error!"<<endl;
		exit(0);
	}
	file.read((char *)&f,sizeof(f));
	while(!file.eof())
	{
			cout<<"���̱�ţ�"<<f.code<<"��Ʒ���ƣ�"<<f.name1<<"��Ʒ�۸�"<<f.price<<"��Ʒ������"<<f.output<<endl;	
			file.read((char *)&f,sizeof(f));
	}
	file.close();
/*	LGNode q;
	if(!head->down)exit(0);	
	q=head->down;
	LThing p;
	while(q)
	{
		p=q->first;
		if(!strcmp(p->name1,a))
			{
				
				p->price=pr;
			}
		else
		{
			p=p->next;
			while(p)
			{
					if(!strcmp(p->name1,a))
					{
						
						p->price=pr;
						break;
					}	
					else
					{
						p=p->next;
					}
				
				
			}
			
		}
		q=q->down;
	}*/
}
void Buy_GNode()
//void Buy_GNode(LGNode &head,int c,char *a)//����Ʒ ����++ 
{
	fstream file,file1;
	Node f;
	int code;
	char name[10]; 
	cout<<"please input shangpu'code  wp'name:";
	cin>>code;
	cin>>name;
	file.open("wuping.dat",ios::in|ios::binary);
	file1.open("wuping1.dat",ios::out|ios::binary);
	if(file.fail())
	{
		cout<<"file open is error!"<<endl;
		exit(0);
	}
	if(file1.fail())
	{
		cout<<"file1 open is error!"<<endl;
		exit(0);
	}
	
	file.read((char *)&f,sizeof(f));//ɾ����Ʒ  
	while(!file.eof())
	{
		if(f.code==code&&!strcmp(f.name1,name))
			f.output++;
		file1.write((char *)&f,sizeof(f));
		file.read((char *)&f,sizeof(f));
	}
	file.close();
	file1.close();
	
	file.open("wuping.dat",ios::out|ios::binary);//�ļ����� 
	file1.open("wuping1.dat",ios::in|ios::binary);
	if(file.fail())
	{
		cout<<"file open is error!"<<endl;
		exit(0);
	}
	if(file1.fail())
	{
		cout<<"file1 open is error!"<<endl;
		exit(0);
	}
	file1.read((char *)&f,sizeof(f));
	while(!file1.eof())
	{
		
		file.write((char *)&f,sizeof(f));
		file1.read((char *)&f,sizeof(f));
	}
	file.close();
	file1.close();
	
	cout<<endl;
	file.open("wuping.dat",ios::in|ios::binary);
	if(file.fail())
	{
		cout<<"file open is error!"<<endl;
		exit(0);
	}
	file.read((char *)&f,sizeof(f));
	while(!file.eof())
	{
			cout<<"���̱�ţ�"<<f.code<<"��Ʒ���ƣ�"<<f.name1<<"��Ʒ�۸�"<<f.price<<"��Ʒ������"<<f.output<<endl;	
			file.read((char *)&f,sizeof(f));
	}
	file.close();
/*	LGNode q;
	if(!head->down)exit(0);
	q=head->down;
	LThing p;
	while(q)
	{
		if(q->code==c)
		{
				p=q->first;
				while(p)
				{
					if(!strcmp(p->name1,a))
					{
						p->output++;
						break;
					}
					else
					p=p->next;
				}
				break;
		}
		else
			q=q->down;
		
	}*/
}

int main()
{
	LGNode head;
	Init_Thing(head);//�������̺���Ʒ�Ŀռ� 
	cout<<"		������վ��Ϣ����"<<endl;
	cout<<"		1.������Ʒ�����̼�����ļ� "<<endl;
	cout<<"		  ��ѯĳһ����Ʒ����"<<endl;
	cout<<"		2.�������� "<<endl;
	cout<<"		3.ɾ������ "<<endl;
	cout<<"		4.������Ʒ"<<endl;
	cout<<"		5.ɾ����Ʒ"<<endl;
	cout<<"		6.�޸ļ۸�"<<endl;
	cout<<"		7.������Ʒ"<<endl;	
	cout<<"		8.��ӡ���̺���Ʒ "<<endl;
	int choice;
	cout<<"please input your choice:"<<endl;
	cin>>choice;
	switch(choice)
	{
		case 1:
			system("cls");
			cout<<"		������վ��Ϣ����"<<endl;
			cout<<"		 ������Ʒ������ "<<endl;
			cout<<"		  ��ѯĳһ����Ʒ����"<<endl;
			Creat_Thing(head);
			Creat_GNode(head);
			Linklist T;
			cout<<"please input the shangping's name:";
			char name2[10];
			cin>>name2;
			Init_LinkThing(T);
			Creat_Onething(T,head,name2);
			Print_Onething(T);
			break;
		case 2:
			system("cls");
			cout<<"		������վ��Ϣ����"<<endl;
			cout<<"			�������� "<<endl;
			En_Thing();
			break;
		case 3:
			system("cls");
			cout<<"		������վ��Ϣ����"<<endl;
			cout<<"		    ɾ������ "<<endl;
			De_Thing();
			break;
		case 4:
			system("cls");
			cout<<"		������վ��Ϣ����"<<endl;
			cout<<"		    ������Ʒ"<<endl;
			En_GNode();
			break;
		case 5:
			system("cls");
			cout<<"		������վ��Ϣ����"<<endl;
			cout<<"			ɾ����Ʒ"<<endl;

			De_GNode();
			break;
		case 6:
			system("cls");
			cout<<"		������վ��Ϣ����"<<endl;
			cout<<"		 �޸ļ۸�"<<endl;
			Eidt_Price();
			break;
		case 7:
			system("cls");
			cout<<"		������վ��Ϣ����"<<endl;
			cout<<"		    ������Ʒ"<<endl;
			Buy_GNode();
			break;
		case 8:
			Print_Thing();			
			break;
		default:
				cout<<"input data is error!";
	}



}
