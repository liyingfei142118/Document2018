#include<iostream>
using namespace std;
#include<malloc.h>
#define Infine 10000
#define max 100
typedef struct
{
	int *ver;//����
	int arc[max][max];//��
	int Ver,Edg;//�������ͱ���
}Graph;
void Init_Graph(Graph &g)//��������-
{
	g.ver=(int *)malloc(max*sizeof(int));
		if(!g.ver)exit(0);
	int m,n,i,j;
	cout<<"���붥�����ͱ���:";
	cin>>m>>n;
	g.Ver=m;//��ʼ��������
	g.Edg=n;//��ʼ������
	for(i=1;i<=g.Ver;i++)//���붥����Ϣ��ʶ:"
	{
		g.ver[i]=i;
	}

	//�Ѿ����ʼ��Ϊ00
	for(i=1;i<=m;i++)
	for(j=1;j<=m;j++)
	{
		g.arc[i][j]=Infine;
	}
}
void Creat_Graph(Graph &g)//��ʼ������ 
{
	int i,j;
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
		  
	}		
}
void Print_Graph(Graph g)
{
	cout<<"�������ͱ���:"<<g.Ver<<" "<<g.Edg<<endl;
	for(int i=1;i<=g.Ver;i++)
	{
		for(int s=1;s<=g.Ver;s++)
		{
			cout<<"  "<<g.arc[i][s];
		}
		cout<<endl;
	}
}

#define STACK_INIT_SIZE 100
#define STACKINCREAT 10
typedef struct 
{
	int *base;
	int *top;
	int stacksize;
}SqStack;
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
void BFS(Graph g)//����������� 
{
	for(int i=1;i<=g.Ver;i++)
	{
		for(int s=1;s<=g.Ver;s++)
		{
			if(g.arc[i][s]!=Infine)
			cout<<g.arc[i][s]<<" ";
		}
	}
}

void DFS(SqStack &s,Graph g,int data,int *visit)//����������� 
{
	
	cout<<g.ver[data]<<" ";//�����һ����� 
	visit[data]=0;//���Ϊ0 
	Push(s,data);//��ջdfv 
	int e;
	Got_top(s,e);//�õ�ջ����Ԫ��
	while(!Empty_Stack(s)) 
	{
		int word=0;
		for(int i=1;i<=g.Ver;i++)
			{
				if(g.arc[e][i]!=Infine&&visit[i]!=0)//�ҵ�����һ���ڽӵ� 
					{
						DFS(s,g,i,visit);
						word=1;
						break;
					}
			}
		if(word==0)
				{
					Pop(s,e);
					Got_top(s,e);	
				}
		for(int i=1;i<=g.Ver;i++)//�ж��Ƿ��н��û���ҵ�,�����У������������
		{
			if(visit[i]!=0)
			{
				DFS(s,g,i,visit);
			}
		}
	}
}
void Prim(Graph g,int k)//k 1 pfim�㷨����С������ 
{

	int visit[g.Ver+1];//���ʱ�־ 
	int lowcost[g.Ver+1];//Ȩֵ 
	int vex[g.Ver+1];//�涥�� 
	for(int i=1;i<=g.Ver;i++)
	{
		visit[i]=0;
		lowcost[i]=g.arc[k][i];
		vex[i]=1;
	}
	visit[k]=1;
	int key=g.Ver-1;//ѭ������ 
	cout<<"��С���������ɱ߼�����̣�"<<endl; 
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

void DestroyGraph(Graph &g)//�ݻپ��� 
{
	for(i=1;i<=g.Ver;i++)
	for(j=1;j<=g.Ver;j++)
	{
		g.arc[i][j]=Infine;
	}
}

//void LocateVex(Graph g)
//void GetVex(Graph g,int e)
void Putvex(Graph &g,int x,int value)//�ı�ڵ��ֵ 
{
	for(i=1;i<=g.Ver;i++)
	int word=0;
	for(j=1;j<=g.Ver;j++)
	{
		if(g.arc[i][j]==x)
		{
			g.arc[i][j]=value;
			word=1;
			break;
		}
	}
	if(word==0)
	cout<<"the node is error!"<<endl;
}
int Firstadjvex(Graph g,int x)//�˵�ĵ�һ���ڽӵ� 
{
	for(i=1;i<=g.Ver;i++)
	for(j=1;j<=g.Ver;j++)
	{
		if(g.arc[i][j]==x)
			{
				int key=0;
				for(int s=j+1;s<=g.Ver;s++)	
				{
					if(g.arc[i][s]!=Infine)
					{
						key=1;
						cout<<"the adjvex:"<<g.arc[i][s]<<endl;
						break;
					}
				}
				if(key==0)
				cout<<"the node don't have adjvex."<<endl;
				break;
			}
	}
}
void Nexadjvex(Graph g,intx)//�˵�ĵڶ����ڽӵ� 
{
	
	for(i=1;i<=g.Ver;i++)
	for(j=1;j<=g.Ver;j++)
	{
		
		if(g.arc[i][j]==x)
		{
			int num=0;
			int key=0;	
				for(int s=j+1;s<=g.Ver;s++)	
				{
					if(g.arc[i][s]!=Infine)
						num++;
					if(num==2)
						{
							cout<<"Nexadjvex:"<<g.arc[i][s]<<endl;
							key=1;
							break;
						}
					}
			if(key==0)
			{
				cout<<"the node have no Nextadjvex."<<endl;
			}
				break;
		}
	}
}
void Deletevex(Graph &g,int x)//ɾ������ 
{
	for(int i=1;i<g.Ver;i++)
	{
		g.arc[i][x]=Infine;
	}
	for(int k=1;k<g.Ver;k++)
	{
		g.arc[x][k]=Infine;
	}
}
//void Insertvex(Graph g)����� 
//void Deletearc(Graph &g,int x,int y)//ɾ���� 
//void Insertarc(Graph &g,int x,int y)//����� 
int main()
{
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
	Prim(g,data);
	
/*	SqStack s;
	InitStack(s);//��ջ 
	int visit[max];
	for(int i=1;i<=g.Ver;i++)
	{
		visit[i]=1;
	}
	int data;
	cout<<"please input the first number:";
	cin>>data;
	cout<<endl;
	int word=0;
	for(int i=1;i<=g.Ver;i++)
	{
		if(g.ver[i]==data)
		{
			word=1;
			break;
			}	
	}
	if(word==1)
	{
		DFS(s,g,data,visit);
	}
	else
	{
	cout<<"input is error!"<<endl;
	}*/
	return 0;
}
