#include<iostream>
using namespace std;
#include<malloc.h>
#define Infine 10000
#define max 100
typedef struct
{
	int *ver;//顶点
	int arc[max][max];//边
	int Ver,Edg;//顶点数和边数
}Graph;
void Init_Graph(Graph &g)//创建矩阵-
{
	g.ver=(int *)malloc(max*sizeof(int));
		if(!g.ver)exit(0);
	int m,n,i,j;
	cout<<"输入顶点数和边数:";
	cin>>m>>n;
	g.Ver=m;//初始化顶点数
	g.Edg=n;//初始化边数
	for(i=1;i<=g.Ver;i++)//输入顶点信息标识:"
	{
		g.ver[i]=i;
	}

	//把矩阵初始化为00
	for(i=1;i<=m;i++)
	for(j=1;j<=m;j++)
	{
		g.arc[i][j]=Infine;
	}
}
void Creat_Graph(Graph &g)//初始化矩阵 
{
	int i,j;
//输入有权值的边，其余直接赋值
 for(int i=1;i<=g.Edg;i++)//输入顶点信息标识:"
	{
		
		int a,a1,weight,word=0;
		cout<<"输入(vi,vj）顶点 权值:"<<endl;
		cin>>a>>a1>>weight;////输入顶点 权值
		for(int s=1;s<=g.Ver;s++)//判断是否顶点是否正确 
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
		else//如果不正确，重复输入 
		{
			cout<<"input is error!";
			i--;
		}
		  
	}		
}
void Print_Graph(Graph g)
{
	cout<<"顶点数和边数:"<<g.Ver<<" "<<g.Edg<<endl;
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
void InitStack(SqStack &s)//构造空栈和赋值 
{
	s.base=(int *)malloc(STACK_INIT_SIZE*sizeof(int));
	if(!s.base)exit(0);
	s.top=s.base;
	s.stacksize=STACK_INIT_SIZE;
}
void Print_Stack(SqStack s)//打印栈 
{
	cout<<"the SqStack element:";
	cout<<s.top-s.base<<endl;
	SqStack s1;
	s1.base=s.base;
	for(int i=0; i<s.top-s.base; i++)//元素的长度length=s.top-s.base 
	{
		cout<<*s1.base++<<" ";
	} 	
}
void Push(SqStack &s,int e)//添加一个元素 
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
void Pop(SqStack &s,int &e)//删除一个元素 
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
void Got_top(SqStack s,int &e)//得到栈顶的元素 
{
	if(s.base==s.top)exit(0);
	e=*(s.top-1);
}
void BFS(Graph g)//广度优先搜索 
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

void DFS(SqStack &s,Graph g,int data,int *visit)//深度优先搜索 
{
	
	cout<<g.ver[data]<<" ";//输出第一个结点 
	visit[data]=0;//标记为0 
	Push(s,data);//入栈dfv 
	int e;
	Got_top(s,e);//得到栈顶点元素
	while(!Empty_Stack(s)) 
	{
		int word=0;
		for(int i=1;i<=g.Ver;i++)
			{
				if(g.arc[e][i]!=Infine&&visit[i]!=0)//找到它的一个邻接点 
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
		for(int i=1;i<=g.Ver;i++)//判断是否还有结点没有找到,果还有，继续这个函数
		{
			if(visit[i]!=0)
			{
				DFS(s,g,i,visit);
			}
		}
	}
}
void Prim(Graph g,int k)//k 1 pfim算法求最小生成树 
{

	int visit[g.Ver+1];//访问标志 
	int lowcost[g.Ver+1];//权值 
	int vex[g.Ver+1];//存顶点 
	for(int i=1;i<=g.Ver;i++)
	{
		visit[i]=0;
		lowcost[i]=g.arc[k][i];
		vex[i]=1;
	}
	visit[k]=1;
	int key=g.Ver-1;//循环次数 
	cout<<"最小生成树生成边加入过程："<<endl; 
while(key!=0)
{
	int min;
	int word;
	
	for(int i=1;i<=g.Ver;i++)//设一个最小值 
	{
		if(!visit[i])//未被访问的 
			{
				min=lowcost[i];
				word=i;
				break;
			}
	}
	
	for(int i=1;i<=g.Ver;i++)//找到权值最小值 
	{
		if(!visit[i])
		{
			if(lowcost[i]<min)
			{
				min=lowcost[i];
				word=i;//记录位置 
			}
		}
	}
	
	visit[word]=1;//标记 
	key--;//次数减一 
	cout<<"<"<<vex[word]<<","<<word<<">"<<" ";//输出下一个节点
	for(int j=1;j<=g.Ver;j++)//刷新权值数组 
	{
		if(!visit[j])
		{
			if(g.arc[word][j]<lowcost[j])
			{
				lowcost[j]=g.arc[word][j];//权值改变 
				vex[j]=word;//顶点数组改变 
			}
		}
	}
}

}

void DestroyGraph(Graph &g)//摧毁矩阵 
{
	for(i=1;i<=g.Ver;i++)
	for(j=1;j<=g.Ver;j++)
	{
		g.arc[i][j]=Infine;
	}
}

//void LocateVex(Graph g)
//void GetVex(Graph g,int e)
void Putvex(Graph &g,int x,int value)//改变节点的值 
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
int Firstadjvex(Graph g,int x)//此点的第一个邻接点 
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
void Nexadjvex(Graph g,intx)//此点的第二个邻接点 
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
void Deletevex(Graph &g,int x)//删除顶点 
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
//void Insertvex(Graph g)插入点 
//void Deletearc(Graph &g,int x,int y)//删除边 
//void Insertarc(Graph &g,int x,int y)//加入边 
int main()
{
	Graph g;
	Init_Graph(g);
	Creat_Graph(g);
	cout<<endl;
	cout<<"初始图："<<endl; 
	Print_Graph(g);
	int data;
	cout<<"please input the first number:";
	cin>>data;
	cout<<endl;
	Prim(g,data);
	
/*	SqStack s;
	InitStack(s);//建栈 
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
