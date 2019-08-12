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
void Init_Graph(Graph &g)
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
void Creat_Graph(Graph &g)
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
void Most_low_H(Graph g,int data)//最邻近法
{
	
	int weightnum=0;
	cout<<data<<" ";
	int visit[max];
	for(int i=1;i<=g.Ver;i++)//点用没用标志 
	{
		visit[i]=1;
	}
	visit[data]=0;
	int k=g.Ver-1;//循环标志 
	int m=data;//记录起点，以便最后一个点能够连接上 
	
	while(k!=0)
	{
		int min,word;
		int key;//word key记录位置 
			for(int i=1;i<=g.Ver;i++)	
			{
				if(visit[i])
				{
					if(g.arc[data][i]!=Infine)//设定一个此点最近的距离 
					{
						min=g.arc[data][i];
						word=i;//记录位置 
						break;
					}
				
				}
			}
		key=word;
		word++;
		
		for(int s=word;s<=g.Ver;s++)//找到此点真正最近的点 
		{
			if(visit[s]&&g.arc[data][s]!=Infine)
			{
				if(g.arc[data][s]<min)
				{
					min=g.arc[data][s];
					key=s;//记录位置 
				}
			
			}
		}
		weightnum+=g.arc[data][key];
		cout<<key<<" ";
		data=key;//下一个点的起点 
		visit[data]=0;//标志此点已用 
		k--;
	}
	cout<<m<<endl;
	weightnum+=g.arc[data][k];
	cout<<endl;
	cout<<"欧拉回路的总权值:";
	cout<<weightnum<<endl;
}

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
	cout<<"H圈:"<<endl;
	Most_low_H(g,data);
	return 0;
}
