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
void Init_Graph(Graph &g)
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
void Creat_Graph(Graph &g)
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
void Most_low_H(Graph g,int data)//���ڽ���
{
	
	int weightnum=0;
	cout<<data<<" ";
	int visit[max];
	for(int i=1;i<=g.Ver;i++)//����û�ñ�־ 
	{
		visit[i]=1;
	}
	visit[data]=0;
	int k=g.Ver-1;//ѭ����־ 
	int m=data;//��¼��㣬�Ա����һ�����ܹ������� 
	
	while(k!=0)
	{
		int min,word;
		int key;//word key��¼λ�� 
			for(int i=1;i<=g.Ver;i++)	
			{
				if(visit[i])
				{
					if(g.arc[data][i]!=Infine)//�趨һ���˵�����ľ��� 
					{
						min=g.arc[data][i];
						word=i;//��¼λ�� 
						break;
					}
				
				}
			}
		key=word;
		word++;
		
		for(int s=word;s<=g.Ver;s++)//�ҵ��˵���������ĵ� 
		{
			if(visit[s]&&g.arc[data][s]!=Infine)
			{
				if(g.arc[data][s]<min)
				{
					min=g.arc[data][s];
					key=s;//��¼λ�� 
				}
			
			}
		}
		weightnum+=g.arc[data][key];
		cout<<key<<" ";
		data=key;//��һ�������� 
		visit[data]=0;//��־�˵����� 
		k--;
	}
	cout<<m<<endl;
	weightnum+=g.arc[data][k];
	cout<<endl;
	cout<<"ŷ����·����Ȩֵ:";
	cout<<weightnum<<endl;
}

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
	cout<<"HȦ:"<<endl;
	Most_low_H(g,data);
	return 0;
}
