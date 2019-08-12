#include<iostream>
using namespace std;
#include<malloc.h>
#include<string.h>
#include<fstream>
#include<windows.h>



typedef struct Node//存物品的结构体 
{
	int code;//商铺编号
	char name1[10];//商品名称
	int price;//价格
	int output;//销量
}Node;
typedef struct Thing//物品 
{
	char name1[10];//商品名称
	int price;//价格
	int output;//销量
	struct Thing *next;//下一个物品 
}Thing,*LThing;

typedef struct GNode//商铺 
{
	int code;//商铺编号 
	char name[10];//商铺名 
	int degree;//信誉度
	LThing first;
	struct GNode *down;//下一个商铺 
}GNode,*LGNode;
typedef struct OneNode//循环链表结构体 
{
	int code;//商铺编号 
	char name[10];//商铺名 
	int degree;//信誉度
	char name1[10];//商品名称
	int price;//价格
	int output;//销量
	struct OneNode *prior;
	struct OneNode *next;
} Link,*Linklist;

void Init_LinkThing(Linklist &head);//初始化循环链表 
void Print_Onething(Linklist &head);//打印循环链表
void Creat_Onething(Linklist &head,LGNode head1,char *c);//创建循环链表查询某一种商品
void Paixu_Onething(Linklist &head);//排序 按销量   
void Init_Thing(LGNode &head);//创建商铺和物品的空间
void Creat_Thing(LGNode &head);//创建商铺 
void En_Thing();//增加商铺
void De_Thing();//删除商铺 
void En_GNode();//增加物品 
void De_GNode();//删除物品
void Creat_GNode(LGNode &head);////创建物品 
void Print_Thing();//打印商铺和物品 
void Eidt_Price();//修改价格
void Buy_GNode();//买物品 销量++ 
void Init_LinkThing(Linklist &head)//初始化循环链表 
{
	head=(Linklist)malloc(sizeof(Link));
	if(!head)exit(0);
	head->next=NULL;
	head->prior=NULL;
}
void Print_Onething(Linklist &head)//打印循环链表 
{
	Linklist s;
	s=head;
	int k=1;
	while(s&&k)
	{
			cout<<"商铺编号："<<s->code<<"商铺名称："<<s->name<<"商铺信誉度："<<s->degree<<endl;
			cout<<"物品名称："<<s->name1<<"物品价格："<<s->price<<"物品销量："<<s->output<<endl;
			s=s->next;
			if(s==head)
				k=0;
	}
	
}
void Creat_Onething(Linklist &head,LGNode head1,char *c)//创建循环链表查询某一种商品 
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
void Paixu_Onething(Linklist &head)//排序 按销量 
{//简单排序 
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

void Init_Thing(LGNode &head)//创建商铺和物品的空间 
{
	head=(LGNode)malloc(sizeof(GNode));
	if(!head)exit(0);
	head->down=NULL;
}
void Creat_Thing(LGNode &head)//创建商铺 
{
	fstream file("shangpu.dat",ios::out|ios::binary);
	if(file.fail())
	{
		cout<<"file open is error!"<<endl;
		exit(0);
	}
	cout<<"请输入商铺（商铺编号，商铺名，信誉度）："<<endl;
	LGNode p,q;
	GNode f;
	p=head;
	int key=1;
	while(key)
	{
		q=(LGNode)malloc(sizeof(GNode));
		cin>>q->code;//输入商铺编号 
		cin>>q->name;//输入商铺名 
		cin>>q->degree;//输入信誉度	
		q->first=NULL;//物品指针置空 
		q->down=NULL;
		f.code=q->code;
		f.degree=q->degree;
		strcpy(f.name,q->name);
		f.first=q->first;
		f.down=q->down;
		file.write((char *)&f,sizeof(f));
		p->down=q;//head为空 
		p=q;	
		int data;//判断是否继续输入 
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
			cout<<"商铺编号："<<f.code<<"商铺名称："<<f.name<<"商铺信誉度："<<f.degree<<endl;	
			file.read((char *)&f,sizeof(f));
	}
	file.close();
}
void En_Thing( )//增加商铺
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
			cout<<"商铺编号："<<f.code<<"商铺名称："<<f.name<<"商铺信誉度："<<f.degree<<endl;	
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
		cout<<"please input 商铺名 信誉度:";
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
			cout<<"商铺编号："<<f.code<<"商铺名称："<<f.name<<"商铺信誉度："<<f.degree<<endl;	
			file.read((char *)&f,sizeof(f));
	}
	file.close();
}
void De_Thing_GN(int code)//删除商铺 对应的删除物品 
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
	
	file.read((char *)&f,sizeof(f));//删除商铺 
	while(!file.eof())
	{
		if(f.code!=code)
			file1.write((char *)&f,sizeof(f));
		file.read((char *)&f,sizeof(f));
	}
	file.close();
	file1.close();
	
	file.open("wuping.dat",ios::out|ios::binary);//文件传递 
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
			cout<<"商铺编号："<<f.code<<"物品名称："<<f.name1<<"物品价格："<<f.price<<"物品销量："<<f.output<<endl;	
			file.read((char *)&f,sizeof(f));
	}
	file.close();
}
void De_Thing()//删除商铺 
{//两个文件 
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
	
	file.read((char *)&f,sizeof(f));//删除商铺 
	while(!file.eof())
	{
		if(f.code!=code)
		{
			if(f.code>code)//商铺编号-- 
				f.code--;
			file1.write((char *)&f,sizeof(f));
		} 
			
		file.read((char *)&f,sizeof(f));
	}
	file.close();
	file1.close();
	
	file.open("shangpu.dat",ios::out|ios::binary);//文件传递 
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
	
	cout<<endl;//打开文件检测 
	file.open("shangpu.dat",ios::in|ios::binary);
	if(file.fail())
	{
		cout<<"file open is error!"<<endl;
		exit(0);
	}
	file.read((char *)&f,sizeof(f));
	while(!file.eof())
	{
			cout<<"商铺编号："<<f.code<<"商铺名称："<<f.name<<"商铺信誉度："<<f.degree<<endl;	
			file.read((char *)&f,sizeof(f));
	}
	file.close();
	De_Thing_GN(code);
}
void En_GNode()//增加物品 
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
	cout<<"请输入商品名称，价格，销量："<<endl;
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
			cout<<"商铺编号："<<f.code<<"物品名称："<<f.name1<<"物品价格："<<f.price<<"物品销量："<<f.output<<endl;	
			file.read((char *)&f,sizeof(f));
	}
	file.close();
}
void De_GNode()
///void De_GNode(LGNode &head,char *c)//删除物品 
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
	
	file.read((char *)&f,sizeof(f));//删除物品  
	while(!file.eof())
	{
		if(f.code!=code&&strcmp(f.name1,name))
			file1.write((char *)&f,sizeof(f));
		file.read((char *)&f,sizeof(f));
	}
	file.close();
	file1.close();
	
	file.open("wuping.dat",ios::out|ios::binary);//文件传递 
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
			cout<<"商铺编号："<<f.code<<"物品名称："<<f.name1<<"物品价格："<<f.price<<"物品销量："<<f.output<<endl;	
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
void Creat_GNode(LGNode &head)////创建物品 
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
	cout<<"请输入商品名称，价格，销量："<<endl;
	
	int key1=1;
	LThing T,p1;//开辟空间存物品信息
	char n[12];
	int pr,out;
	while(key1)
	{

		cin>>n;
		cin>>pr>>out;
		
		f.code=q->code; 
		T=(Thing *)malloc(sizeof(Thing));
		strcpy(T->name1,n);//商品名称
		strcpy(f.name1,n);
		T->price=pr;//价格
		f.price=pr;
		T->output=out;//销量
		f.output=out;
		T->next=NULL;
		//尾插法
		file.write((char *)&f,sizeof(f));
		if(q->first==NULL) 
		 	q->first=T;//first不空 
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
			case 1://继续添加物品 
				{
					break;
				}
			case 2://添加下一个商铺物品信息 
				{
						q=q->down;
						if(!q)
							key1=0;
						break;
				}
			case 3://结束 
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
			cout<<"商铺编号："<<f.code<<"物品名称："<<f.name1<<"物品价格："<<f.price<<"物品销量："<<f.output<<endl;	
			file.read((char *)&f,sizeof(f));
	}
	file.close();
}
void Print_Thing()
//void Print_Thing(LGNode head)//打印商铺和物品 
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
			cout<<"商铺编号："<<s.code<<"商铺名称："<<s.name<<"商铺信誉度："<<s.degree<<endl;	
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
			cout<<"商铺编号："<<f.code<<"物品名称："<<f.name1<<"物品价格："<<f.price<<"物品销量："<<f.output<<endl;	
			file.read((char *)&f,sizeof(f));
	}
	file.close();
/*	LGNode p;
	p=head->down;
	if(p==NULL)exit(0);
	while(p)
	{
		
		cout<<"商铺编号："<<p->code<<"商铺名称："<<p->name<<"商铺信誉度："<<p->degree<<endl;
		LThing T;
		T=p->first;
		while(T)
		{
			cout<<"物品名称："<<T->name1<<"物品价格："<<T->price<<"物品销量："<<T->output<<endl;
			T=T->next;
		}
		p=p->down;
	}*/
}
void Eidt_Price()
//void Eidt_Price(LGNode &head,char *a,int pr)//修改价格 
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
	
	file.open("wuping.dat",ios::out|ios::binary);//文件传递 
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
			cout<<"商铺编号："<<f.code<<"物品名称："<<f.name1<<"物品价格："<<f.price<<"物品销量："<<f.output<<endl;	
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
//void Buy_GNode(LGNode &head,int c,char *a)//买物品 销量++ 
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
	
	file.read((char *)&f,sizeof(f));//删除物品  
	while(!file.eof())
	{
		if(f.code==code&&!strcmp(f.name1,name))
			f.output++;
		file1.write((char *)&f,sizeof(f));
		file.read((char *)&f,sizeof(f));
	}
	file.close();
	file1.close();
	
	file.open("wuping.dat",ios::out|ios::binary);//文件传递 
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
			cout<<"商铺编号："<<f.code<<"物品名称："<<f.name1<<"物品价格："<<f.price<<"物品销量："<<f.output<<endl;	
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
	Init_Thing(head);//创建商铺和物品的空间 
	cout<<"		购物网站信息管理"<<endl;
	cout<<"		1.创建物品和商铺及相关文件 "<<endl;
	cout<<"		  查询某一种商品名称"<<endl;
	cout<<"		2.增加商铺 "<<endl;
	cout<<"		3.删除商铺 "<<endl;
	cout<<"		4.增加物品"<<endl;
	cout<<"		5.删除物品"<<endl;
	cout<<"		6.修改价格"<<endl;
	cout<<"		7.购买物品"<<endl;	
	cout<<"		8.打印商铺和物品 "<<endl;
	int choice;
	cout<<"please input your choice:"<<endl;
	cin>>choice;
	switch(choice)
	{
		case 1:
			system("cls");
			cout<<"		购物网站信息管理"<<endl;
			cout<<"		 创建物品和商铺 "<<endl;
			cout<<"		  查询某一种商品名称"<<endl;
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
			cout<<"		购物网站信息管理"<<endl;
			cout<<"			增加商铺 "<<endl;
			En_Thing();
			break;
		case 3:
			system("cls");
			cout<<"		购物网站信息管理"<<endl;
			cout<<"		    删除商铺 "<<endl;
			De_Thing();
			break;
		case 4:
			system("cls");
			cout<<"		购物网站信息管理"<<endl;
			cout<<"		    增加物品"<<endl;
			En_GNode();
			break;
		case 5:
			system("cls");
			cout<<"		购物网站信息管理"<<endl;
			cout<<"			删除物品"<<endl;

			De_GNode();
			break;
		case 6:
			system("cls");
			cout<<"		购物网站信息管理"<<endl;
			cout<<"		 修改价格"<<endl;
			Eidt_Price();
			break;
		case 7:
			system("cls");
			cout<<"		购物网站信息管理"<<endl;
			cout<<"		    购买物品"<<endl;
			Buy_GNode();
			break;
		case 8:
			Print_Thing();			
			break;
		default:
				cout<<"input data is error!";
	}



}
