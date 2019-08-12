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
	int *ver;//顶点
	int arc[max+1][max+1];//边
	int Ver,Edg;//顶点数和边数
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
void Creat_map();//创建文件
void Creat_Graph(Graph &g);//创建问题一的图 
void Creat1_Graph(Graph &g);//创建问题二的图
void Print_Graph(Graph g);//打印图 
void InitStack(SqStack &s);//构造空栈和赋值 
void Print_Stack(SqStack s);//打印栈 
void Push(SqStack &s,int e);//添加一个元素 
int Empty_Stack(SqStack s);
void Pop(SqStack &s,int &e);//删除一个元素 
void Got_top(SqStack s,int &e);//得到栈顶的元素 
void Search(Graph g,int lowcost[],int vex[],int k);//找路径 
void Short_Path(Graph g,int k);//最短路径 思路仿prim算法 
void Prim(Graph g,int k);//最小生成树prim算法

void Init_Graph(Graph &g)
{
	g.ver=(int *)malloc(max*sizeof(int));
	if(!g.ver)exit(0);
/*	int m,n,i,j;
/*	cout<<"输入顶点数和边数:";
	cin>>m>>n;
	g.Ver=m;//初始化顶点数
	g.Edg=n;//初始化边数
	for(i=1;i<=g.Ver;i++)//输入顶点信息标识:"
	{
		g.ver[i]=i;
	}*/
	g.Edg=0;
	g.Ver=0;
	//把矩阵初始化为00
	int i,j; 
	for(i=0;i<=max;i++)
	for(j=0;j<=max;j++)
	{
		g.arc[i][j]=Infine;
	}
}
void Creat_map()//创建文件
{
	fstream file;
	file.open("net.txt",ios::out);
	if(file.fail())
	{
		cout<<"file open is error!"<<endl;
		exit(0);
	}
	int n;
	cout<<"please input n无线传感器结点:";
	cin>>n;
	node nn[n];
	//int ni,xi,yi;
	cout<<"please input ni, xi, yi:"<<endl;
	for(int i=1;i<=n;i++)
	{
		cin>>nn[i].node;//输入节点 
		cin>>nn[i].i;//输入节点位置 
		cin>>nn[i].j;//输入节点位置
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
void Creat_Graph(Graph &g)//创建问题一的图 
{
	
	int n;
	cout<<"please input n无线传感器结点:";
	cin>>n;
	g.Ver=n;//节点数 
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
		nn[i].node=k;//输入节点 
		g.ver[i]=nn[i].node;
		file>>k;
		nn[i].i=k;//输入节点位置 
		file>>k;
		nn[i].j=k;//输入节点位置
		file>>k;
		if(i>=2)//从第二个节点判断是否有边 
		{
			for(int j=1;j<i;j++)//从第一个节点开始 
			{//distance求距离的平方 
				int distance=(nn[i].i-nn[j].i)*(nn[i].i-nn[j].i)+(nn[i].j-nn[j].j)*(nn[i].j-nn[j].j);
				if(j==1&&sqrt(distance)>10)
				{
					break;
				}
				else if(sqrt(distance)<10)//如果距离小于10 
				{
					count++;//记录边数 
					g.arc[nn[i].node][nn[j].node]=distance;//加边 
		 			g.arc[nn[j].node][nn[i].node]=distance;
				}
			}
		}
	}
	file.close();
	g.Edg=2*count;//传递边数 
/*	int i,j;
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
		  
	}		*/
}
void Creat1_Graph(Graph &g)//创建问题二的图 
{
	
	int n;
	cout<<"please input n无线传感器结点:";
	cin>>n;
	g.Ver=n;//节点数 
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
		nn[i].node=k;//输入节点 
		g.ver[i]=nn[i].node;
		file>>k;
		nn[i].i=k;//输入节点位置 
		file>>k;
		nn[i].j=k;//输入节点位置
		file>>k;
		if(i>=2)//从第二个节点判断是否有边 
		{
			for(int j=1;j<i;j++)//从第一个节点开始 
			{//distance求距离的平方 
				int distance=(nn[i].i-nn[j].i)*(nn[i].i-nn[j].i)+(nn[i].j-nn[j].j)*(nn[i].j-nn[j].j);
				if(j==1&&sqrt(distance)>10)
				{
					break;
				}
				else if(sqrt(distance)<10)//如果距离小于10 
				{
					count++;//记录边数 
					g.arc[nn[i].node][nn[j].node]=sqrt(distance);//加边 
		 			g.arc[nn[j].node][nn[i].node]=sqrt(distance);
				}
			}
		}
	}
	file.close();
	g.Edg=2*count;//传递边数 
/*	int i,j;
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
		  
	}		*/
}
void Print_Graph(Graph g)//打印图 
{
	cout<<"顶点数和边数:"<<g.Ver<<" "<<g.Edg<<endl;
	for(int i=0;i<=max;i++)
	{
		for(int s=0;s<=max;s++)
		{
			if(g.arc[i][s]!=Infine)
			cout<<i<<"  "<<s<<":"<<g.arc[i][s]<<endl;
		}
	}
}


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

void Search(Graph g,int lowcost[],int vex[],int k)//找路径 
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
			cout<<k<<"到"<<i<<"最短时间:"<<lowcost[i]<<endl;	
			tongdao[s]=i;//记录终点位置 
			t=i;//t记录终点位置 
			while(vex[t]!=k)
			{
				s++;
				tongdao[s]=vex[t];
				t=vex[t];
			}
			cout<<"通道: "<<k<<" "; 
			for(int j=s;j>=1;j--)
			cout<<tongdao[j]<<" ";
			cout<<endl;
		}	
	}
}
void Short_Path(Graph g,int k)//最短路径 思路仿prim算法 
{ 
	int m,n;
	int visit[g.Ver+1];//访问标志 
	int lowcost[g.Ver+1];//权值 
	int vex[g.Ver+1];//存顶点 
	for(int i=1;i<=g.Ver;i++)
	{
		visit[i]=0;//访问标志
		lowcost[i]=g.arc[k][i];//k距离i最小权值
		vex[i]=k;
	}
	visit[k]=1;//k点被访问 
	int key=g.Ver-1;//循环次数 
//	cout<<"最小生成树生成边加入过程："<<endl; 
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
//	cout<<"<"<<vex[word]<<","<<word<<">"<<" ";//输出下一个节点

	for(int j=1;j<=g.Ver;j++)//刷新权值数组 
	{
		if(!visit[j])
		{
			if(g.arc[word][j]+lowcost[word]<lowcost[j])
			{
				lowcost[j]=g.arc[word][j]+lowcost[word];//权值改变 
				vex[j]=word;//顶点数组改变 
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
void Prim(Graph g,int k)//最小生成树prim算法 
{ 
	int m,n;
	int visit[g.Ver+1];//访问标志 
	int lowcost[g.Ver+1];//权值 
	int vex[g.Ver+1];//存顶点 
	for(int i=1;i<=g.Ver;i++)
	{
		visit[i]=0;
		lowcost[i]=g.arc[k][i];
		vex[i]=k;
	}
	visit[k]=1;
	int key=g.Ver-1;//循环次数 
	cout<<"平均能耗最小网络结构加入过程："<<endl; 
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
	if(g.arc[vex[word]][word]!=Infine)
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
int main()
{
	cout<<"			无线传感器网络"<<endl;
	cout<<"			1.创建文件"<<endl;
	cout<<"			2.最短时间通道"<<endl;
	cout<<"			3.平均能耗最小网络结构"<<endl;
	int choice;
	cout<<"please input your choice:";
	cin>>choice;
	switch(choice)
	{
		case 1:
			system("cls");
			cout<<"			无线传感器网络"<<endl;
			cout<<"			1.创建文件"<<endl;
			Creat_map();
			break;
		case 2:
			{
			system("cls");
			cout<<"			无线传感器网络"<<endl;
			cout<<"			2.最短时间通道"<<endl;
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
			Short_Path(g,data);
			break;
			}
		case 3:
			{
			system("cls");
			cout<<"			无线传感器网络"<<endl;
			cout<<"		3.平均能耗最小网络结构"<<endl;
			Graph g;
			Init_Graph(g);
			Creat1_Graph(g);
			cout<<endl;
			cout<<"初始图："<<endl; 
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
