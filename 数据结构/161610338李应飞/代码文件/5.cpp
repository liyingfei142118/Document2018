#include<iostream>
using namespace std;
#include<malloc.h>
#include<fstream>
#include<math.h>
#define Infine 10000
#define max 100
typedef struct
{
	int node;
	int i;
	int j;
}node;
typedef struct
{
	int *ver;//����
	int arc[max+1][max+1];//��
	int Ver,Edg;//�������ͱ���
}Graph;
#define STACK_INIT_SIZE 100
#define STACKINCREAT 10
typedef struct 
{
	int *base;
	int *top;
	int stacksize;
}SqStack;

void Init_Graph(Graph &g);
void Creat_map();//�����ļ�
void Creat_Graph(Graph &g);//��������һ��ͼ 
void Creat1_Graph(Graph &g);//�����������ͼ
void Print_Graph(Graph g);//��ӡͼ 
void InitStack(SqStack &s);//�����ջ�͸�ֵ 
void Print_Stack(SqStack s);//��ӡջ 
void Push(SqStack &s,int e);//���һ��Ԫ�� 
int Empty_Stack(SqStack s);
void Pop(SqStack &s,int &e);//ɾ��һ��Ԫ�� 
void Got_top(SqStack s,int &e);//�õ�ջ����Ԫ�� 
void Search(Graph g,int lowcost[],int vex[],int k);//��·�� 
void Short_Path(Graph g,int k);//���·�� ˼·��prim�㷨 
void Prim(Graph g,int k);//��С������prim�㷨

void Init_Graph(Graph &g)
{
	g.ver=(int *)malloc(max*sizeof(int));
	if(!g.ver)exit(0);
/*	int m,n,i,j;
/*	cout<<"���붥�����ͱ���:";
	cin>>m>>n;
	g.Ver=m;//��ʼ��������
	g.Edg=n;//��ʼ������
	for(i=1;i<=g.Ver;i++)//���붥����Ϣ��ʶ:"
	{
		g.ver[i]=i;
	}*/
	g.Edg=0;
	g.Ver=0;
	//�Ѿ����ʼ��Ϊ00
	int i,j; 
	for(i=0;i<=max;i++)
	for(j=0;j<=max;j++)
	{
		g.arc[i][j]=Infine;
	}
}
void Creat_map()//�����ļ�
{
	fstream file;
	file.open("net.txt",ios::out);
	if(file.fail())
	{
		cout<<"file open is error!"<<endl;
		exit(0);
	}
	int n;
	cout<<"please input n���ߴ��������:";
	cin>>n;
	node nn[n];
	//int ni,xi,yi;
	cout<<"please input ni, xi, yi:"<<endl;
	for(int i=1;i<=n;i++)
	{
		cin>>nn[i].node;//����ڵ� 
		cin>>nn[i].i;//����ڵ�λ�� 
		cin>>nn[i].j;//����ڵ�λ��
		file<<nn[i].node<<" ";
		file<<nn[i].i<<" ";
		file<<nn[i].j<<" ";
	}
	file.close();
	
	cout<<"put file'content:"<<endl;
	int k;
	file.open("net.txt",ios::in);
	if(file.fail())
	{
		cout<<"file open is error!"<<endl;
		exit(0);
	}
	file>>k;
	while(!file.eof())
	{
		
		cout<<k<<"  ";
		file>>k;
	}
	file.close();
}
void Creat_Graph(Graph &g)//��������һ��ͼ 
{
	
	int n;
	cout<<"please input n���ߴ��������:";
	cin>>n;
	g.Ver=n;//�ڵ��� 
	node nn[n];
	//int ni,xi,yi;
	int count=0;
	int k;
	fstream file;
	file.open("net.txt",ios::in);
	if(file.fail())
	{
		cout<<"file open is error!"<<endl;
		exit(0);
	}
	file>>k;
	for(int i=1;i<=n;i++)
	{
		nn[i].node=k;//����ڵ� 
		g.ver[i]=nn[i].node;
		file>>k;
		nn[i].i=k;//����ڵ�λ�� 
		file>>k;
		nn[i].j=k;//����ڵ�λ��
		file>>k;
		if(i>=2)//�ӵڶ����ڵ��ж��Ƿ��б� 
		{
			for(int j=1;j<i;j++)//�ӵ�һ���ڵ㿪ʼ 
			{//distance������ƽ�� 
				int distance=(nn[i].i-nn[j].i)*(nn[i].i-nn[j].i)+(nn[i].j-nn[j].j)*(nn[i].j-nn[j].j);
				if(j==1&&sqrt(distance)>10)
				{
					break;
				}
				else if(sqrt(distance)<10)//�������С��10 
				{
					count++;//��¼���� 
					g.arc[nn[i].node][nn[j].node]=distance;//�ӱ� 
		 			g.arc[nn[j].node][nn[i].node]=distance;
				}
			}
		}
	}
	file.close();
	g.Edg=2*count;//���ݱ��� 
/*	int i,j;
//������Ȩֵ�ıߣ�����ֱ�Ӹ�ֵ
 for(int i=1;i<=g.Edg;i++)//���붥����Ϣ��ʶ:"
	{
		
		int a,a1,weight,word=0;
		cout<<"����(vi,vj������ Ȩֵ:"<<endl;
		cin>>a>>a1>>weight;////���붥�� Ȩֵ
		for(int s=1;s<=g.Ver;s++)//�ж��Ƿ񶥵��Ƿ���ȷ 
		{
			if(g.ver[s]==a)
				word++;
			if(g.ver[s]==a1)
				word++;		
		 }
		 if(word==2)
		 {
		 	g.arc[a][a1]=weight;
		 	g.arc[a1][a]=weight;
		  } 
		else//�������ȷ���ظ����� 
		{
			cout<<"input is error!";
			i--;
		}
		  
	}		*/
}
void Creat1_Graph(Graph &g)//�����������ͼ 
{
	
	int n;
	cout<<"please input n���ߴ��������:";
	cin>>n;
	g.Ver=n;//�ڵ��� 
	node nn[n];
	//int ni,xi,yi;
	int count=0;
	int k;
	fstream file;
	file.open("net.txt",ios::in);
	if(file.fail())
	{
		cout<<"file open is error!"<<endl;
		exit(0);
	}
	file>>k;
	for(int i=1;i<=n;i++)
	{
		nn[i].node=k;//����ڵ� 
		g.ver[i]=nn[i].node;
		file>>k;
		nn[i].i=k;//����ڵ�λ�� 
		file>>k;
		nn[i].j=k;//����ڵ�λ��
		file>>k;
		if(i>=2)//�ӵڶ����ڵ��ж��Ƿ��б� 
		{
			for(int j=1;j<i;j++)//�ӵ�һ���ڵ㿪ʼ 
			{//distance������ƽ�� 
				int distance=(nn[i].i-nn[j].i)*(nn[i].i-nn[j].i)+(nn[i].j-nn[j].j)*(nn[i].j-nn[j].j);
				if(j==1&&sqrt(distance)>10)
				{
					break;
				}
				else if(sqrt(distance)<10)//�������С��10 
				{
					count++;//��¼���� 
					g.arc[nn[i].node][nn[j].node]=sqrt(distance);//�ӱ� 
		 			g.arc[nn[j].node][nn[i].node]=sqrt(distance);
				}
			}
		}
	}
	file.close();
	g.Edg=2*count;//���ݱ��� 
/*	int i,j;
//������Ȩֵ�ıߣ�����ֱ�Ӹ�ֵ
 for(int i=1;i<=g.Edg;i++)//���붥����Ϣ��ʶ:"
	{
		
		int a,a1,weight,word=0;
		cout<<"����(vi,vj������ Ȩֵ:"<<endl;
		cin>>a>>a1>>weight;////���붥�� Ȩֵ
		for(int s=1;s<=g.Ver;s++)//�ж��Ƿ񶥵��Ƿ���ȷ 
		{
			if(g.ver[s]==a)
				word++;
			if(g.ver[s]==a1)
				word++;		
		 }
		 if(word==2)
		 {
		 	g.arc[a][a1]=weight;
		 	g.arc[a1][a]=weight;
		  } 
		else//�������ȷ���ظ����� 
		{
			cout<<"input is error!";
			i--;
		}
		  
	}		*/
}
void Print_Graph(Graph g)//��ӡͼ 
{
	cout<<"�������ͱ���:"<<g.Ver<<" "<<g.Edg<<endl;
	for(int i=0;i<=max;i++)
	{
		for(int s=0;s<=max;s++)
		{
			if(g.arc[i][s]!=Infine)
			cout<<i<<"  "<<s<<":"<<g.arc[i][s]<<endl;
		}
	}
}


void InitStack(SqStack &s)//�����ջ�͸�ֵ 
{
	s.base=(int *)malloc(STACK_INIT_SIZE*sizeof(int));
	if(!s.base)exit(0);
	s.top=s.base;
	s.stacksize=STACK_INIT_SIZE;
}
void Print_Stack(SqStack s)//��ӡջ 
{
	cout<<"the SqStack element:";
	cout<<s.top-s.base<<endl;
	SqStack s1;
	s1.base=s.base;
	for(int i=0; i<s.top-s.base; i++)//Ԫ�صĳ���length=s.top-s.base 
	{
		cout<<*s1.base++<<" ";
	} 	
}
void Push(SqStack &s,int e)//���һ��Ԫ�� 
{
	if(s.top-s.base>=s.stacksize) 
	{
	s.base=(int *)realloc(s.base,(s.stacksize+STACKINCREAT)*sizeof(int));	
		if(!s.base)exit(0);
	s.top=s.base+s.stacksize;
	s.stacksize+=STACKINCREAT;
	}
	*s.top=e;
	s.top++;
}
void Pop(SqStack &s,int &e)//ɾ��һ��Ԫ�� 
{
	if(s.base==s.top)exit(0);
	--s.top;
	e=*s.top;
}
int Empty_Stack(SqStack s)
{
	if(s.base==s.top)
		return 1;
	else
		return 0;
}
void Got_top(SqStack s,int &e)//�õ�ջ����Ԫ�� 
{
	if(s.base==s.top)exit(0);
	e=*(s.top-1);
}

void Search(Graph g,int lowcost[],int vex[],int k)//��·�� 
{
	int tongdao[g.Edg+1];
	int s,t; 
	for(int ss=1;ss<=g.Edg;ss++)
			{
				tongdao[ss]=0;
			}	
	for(int i=1;i<=g.Ver;i++)
	{

		s=1;
		if(i!=k&&lowcost[i]!=Infine)
		{
			cout<<k<<"��"<<i<<"���ʱ��:"<<lowcost[i]<<endl;	
			tongdao[s]=i;//��¼�յ�λ�� 
			t=i;//t��¼�յ�λ�� 
			while(vex[t]!=k)
			{
				s++;
				tongdao[s]=vex[t];
				t=vex[t];
			}
			cout<<"ͨ��: "<<k<<" "; 
			for(int j=s;j>=1;j--)
			cout<<tongdao[j]<<" ";
			cout<<endl;
		}	
	}
}
void Short_Path(Graph g,int k)//���·�� ˼·��prim�㷨 
{ 
	int m,n;
	int visit[g.Ver+1];//���ʱ�־ 
	int lowcost[g.Ver+1];//Ȩֵ 
	int vex[g.Ver+1];//�涥�� 
	for(int i=1;i<=g.Ver;i++)
	{
		visit[i]=0;//���ʱ�־
		lowcost[i]=g.arc[k][i];//k����i��СȨֵ
		vex[i]=k;
	}
	visit[k]=1;//k�㱻���� 
	int key=g.Ver-1;//ѭ������ 
//	cout<<"��С���������ɱ߼�����̣�"<<endl; 
while(key!=0)
{
	int min;
	int word;
	
	for(int i=1;i<=g.Ver;i++)//��һ����Сֵ 
	{
		if(!visit[i])//δ�����ʵ� 
			{
				min=lowcost[i];
				word=i;
				break;
			}
	}
	
	for(int i=1;i<=g.Ver;i++)//�ҵ�Ȩֵ��Сֵ 
	{
		if(!visit[i])
		{
			if(lowcost[i]<min)
			{
				min=lowcost[i];
				word=i;//��¼λ�� 
			}
		}
	}
	
	visit[word]=1;//��� 
	key--;//������һ 
//	cout<<"<"<<vex[word]<<","<<word<<">"<<" ";//�����һ���ڵ�

	for(int j=1;j<=g.Ver;j++)//ˢ��Ȩֵ���� 
	{
		if(!visit[j])
		{
			if(g.arc[word][j]+lowcost[word]<lowcost[j])
			{
				lowcost[j]=g.arc[word][j]+lowcost[word];//Ȩֵ�ı� 
				vex[j]=word;//��������ı� 
			}
		}
	}
}
cout<<"lowcost[i]:"<<endl;
	for(int i=1;i<=g.Ver;i++)
	{	
		cout<<lowcost[i]<<" ";
		
	}
	cout<<endl;
cout<<"vex[i]:"<<endl;
	for(int i=1;i<=g.Ver;i++)
	{
		cout<<vex[i]<<" ";
	}
	cout<<endl;
	Search(g,lowcost,vex,k);
}
void Prim(Graph g,int k)//��С������prim�㷨 
{ 
	int m,n;
	int visit[g.Ver+1];//���ʱ�־ 
	int lowcost[g.Ver+1];//Ȩֵ 
	int vex[g.Ver+1];//�涥�� 
	for(int i=1;i<=g.Ver;i++)
	{
		visit[i]=0;
		lowcost[i]=g.arc[k][i];
		vex[i]=k;
	}
	visit[k]=1;
	int key=g.Ver-1;//ѭ������ 
	cout<<"ƽ���ܺ���С����ṹ������̣�"<<endl; 
while(key!=0)
{
	int min;
	int word;
	
	for(int i=1;i<=g.Ver;i++)//��һ����Сֵ 
	{
		if(!visit[i])//δ�����ʵ� 
			{
				min=lowcost[i];
				word=i;
				break;
			}
	}
	
	for(int i=1;i<=g.Ver;i++)//�ҵ�Ȩֵ��Сֵ 
	{
		if(!visit[i])
		{
			if(lowcost[i]<min)
			{
				min=lowcost[i];
				word=i;//��¼λ�� 
			}
		}
	}
	
	visit[word]=1;//��� 
	key--;//������һ 
	if(g.arc[vex[word]][word]!=Infine)
		cout<<"<"<<vex[word]<<","<<word<<">"<<" ";//�����һ���ڵ�

	for(int j=1;j<=g.Ver;j++)//ˢ��Ȩֵ���� 
	{
		if(!visit[j])
		{
			if(g.arc[word][j]<lowcost[j])
			{
				lowcost[j]=g.arc[word][j];//Ȩֵ�ı� 
				vex[j]=word;//��������ı� 
			}
		}
	}
}
}
int main()
{
	cout<<"			���ߴ���������"<<endl;
	cout<<"			1.�����ļ�"<<endl;
	cout<<"			2.���ʱ��ͨ��"<<endl;
	cout<<"			3.ƽ���ܺ���С����ṹ"<<endl;
	int choice;
	cout<<"please input your choice:";
	cin>>choice;
	switch(choice)
	{
		case 1:
			system("cls");
			cout<<"			���ߴ���������"<<endl;
			cout<<"			1.�����ļ�"<<endl;
			Creat_map();
			break;
		case 2:
			{
			system("cls");
			cout<<"			���ߴ���������"<<endl;
			cout<<"			2.���ʱ��ͨ��"<<endl;
			Graph g;
			Init_Graph(g);
			Creat_Graph(g);
			cout<<endl;
			cout<<"��ʼͼ��"<<endl; 
			Print_Graph(g);
			int data;
			cout<<"please input the first number:";
			cin>>data;
			cout<<endl;
			Short_Path(g,data);
			break;
			}
		case 3:
			{
			system("cls");
			cout<<"			���ߴ���������"<<endl;
			cout<<"		3.ƽ���ܺ���С����ṹ"<<endl;
			Graph g;
			Init_Graph(g);
			Creat1_Graph(g);
			cout<<endl;
			cout<<"��ʼͼ��"<<endl; 
			Print_Graph(g);
			int data;
			cout<<"please input the first number:";
			cin>>data;
			cout<<endl;
			Prim(g,data);
			break;
			}
		default:
			cout<<"chioce input is error!"<<endl;
			break;
	 } 
	return 0;
}
