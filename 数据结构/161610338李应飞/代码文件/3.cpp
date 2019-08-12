#include<iostream>
using namespace std;
#include<malloc.h>
#include<fstream>
#define max 100
#define add 10

typedef struct BiTNode//二叉链表结构体 
{
	int data;
	struct BiTNode *lchild,*rchild;//左右孩子指针 
}BiTNode,*BiTree;

typedef struct QNode//队列 
{
	BiTNode *data;//（int data存数据BITNode* data存树的指针） 
	struct QNode *next;//下一个数据的指针 
}QNode,*QueuePtr;
typedef struct
{
	QueuePtr front;//队列头 
	QueuePtr rear;//队列尾 
}LinkQueue;
typedef struct//栈的结构体 
{
	BiTNode * *base;//栈底指针 
	BiTNode * *top;//栈顶指针 
	int stacksize;//栈的大小 
}Sqstack;

void Init_Queue(LinkQueue &s);//创建队列 
void EnQueue(LinkQueue &s,BiTNode *e);//入队 
void DeQueue(LinkQueue &s,BiTNode * &e);//出队 
int Empty_Queue(LinkQueue s);//判断队是否为空
void Init_Sqstack(Sqstack &s);//构建栈 
void Push(Sqstack &s,BiTNode *e);//入栈
void Pop(Sqstack &s,BiTNode* &e);//出栈 
int Empty_stack(Sqstack s);//判断栈是否为空 
void Gottop_stack(Sqstack s,BiTNode* &e);//得到栈顶元素 
void Init_BiTree(BiTree &T);//创建二叉树 
void Creat_BiTree(BiTree &T);//创二叉树建数据 
void Clear_BiTree(BiTree &T);//清空树 
bool Empty_BiTree(BiTree T);//判断树是否为空 
int Max(int x,int y);//简易的两个数比较大小
int Depth_BiTree(BiTree T);//树的深度或者高度 
void Preorder_BiTree(BiTree T);//先序遍历 
void Preorder__BiTree(BiTree T);//先序遍历非递归 
void Inorder_BiTree(BiTree T);//中序遍历
void Inorder__BiTree(BiTree T);//中序遍历非递归
void Postorder_BiTree(BiTree T);//后序遍历
void Postorder__BiTree(BiTree T);//后序遍历非递归
void div_BiTree(BiTree T);//层次遍历 
int Leaf_BiTree(BiTree T);//求叶子数即宽度 
int Paixu_BiTree(BiTree T);//判断是否为二叉排序树 
void CreatWen_BiTree();//创建存树文件 
void CreatHWen_BiTree();//从文件传值给树

void Init_Queue(LinkQueue &s)//创建队列 
{
	s.front=s.rear=(QueuePtr)malloc(sizeof(QNode));
	if(!s.front)exit(0);
	s.front->next=NULL;	
}
void EnQueue(LinkQueue &s,BiTNode *e)//入队 
{
	QueuePtr p;
	p=(QueuePtr)malloc(sizeof(QNode));//开辟一个对应空间存数据 
	if(!p)exit(0);
	p->data=e;
	p->next=NULL;
	
	s.rear->next=p;//可以看出队头为空，队尾不空 
	s.rear=p;
}
void DeQueue(LinkQueue &s,BiTNode * &e)//出队 
{
	if(s.rear==s.front)exit(0);
	
	QueuePtr p;
	p=s.front->next;
	e=p->data;
	s.front->next=p->next;
	
	if(s.rear==p)s.rear=s.front;
	free(p);//删除空间 
}
int Empty_Queue(LinkQueue s)//判断队是否为空 
{
	if(s.rear==s.front)
		return 1;
	else
		return 0;
}

void Init_Sqstack(Sqstack &s)//构建栈 
{
	s.base=(BiTNode **)malloc(max*sizeof(BiTNode*));
	if(!s.base)exit(0);//如果失败，关闭 
	s.top=s.base;
	s.stacksize=max;
}

void Push(Sqstack &s,BiTNode *e)//入栈 
{//s.top-s.base为栈的长度 
	if(s.top-s.base>=s.stacksize)//如果栈满 
	{
		s.base=(BiTNode **) realloc (s.base,(s.stacksize+add)*sizeof( BiTNode*));
		if( !s.base)exit(0);
		s.top=s.base+s.stacksize;
		s.stacksize+=add;
	}
	*s.top=e;//栈顶赋值 
	s.top++;//栈顶指针下移 
}
void Pop(Sqstack &s,BiTNode* &e)//出栈 
{
	if(s.base==s.top)exit(0);//如果栈空，关闭 
	s.top--;//因为栈顶为空，所以栈顶指针下移即出栈 
	e=*s.top;
	//e 赋值 栈当前值 即出栈的数据或者指针 
}
int Empty_stack(Sqstack s)//判断栈是否为空 
{
	if(s.base==s.top)
		return 1;
	else
		return 0;
}
void Gottop_stack(Sqstack s,BiTNode* &e)//得到栈顶元素 
{
	if(s.base==s.top)exit(0);
	s.top--;
	//只需栈顶元素下移 
	e=*s.top;
}

void Init_BiTree(BiTree &T)//创建二叉树 
{
	T=(BiTNode *)malloc(sizeof(BiTNode));
	if(!T)exit(0);
	T->lchild=T->rchild=NULL;//左右孩子置空	
} 
void Creat_BiTree(BiTree &T)//创二叉树建数据 
{//根据先序遍历规则来建树 
	int e;
	fstream file,file1;
	BiTNode f;
	file.open("tree1.dat",ios::in|ios::binary);	
	if(file.fail())
	{
		cout<<"file open error!"<<endl;
		exit(0);
	}
	file1.open("tree2.dat",ios::out|ios::binary);	
	if(file1.fail())
	{
		cout<<"file1 open error!"<<endl;
		exit(0);
	}
	file.read((char *)&f,sizeof(f));
	e=f.data;
	file.read((char *)&f,sizeof(f));
	while(!file.eof())
	{
		file1.write((char *)&f,sizeof(f));
		file.read((char *)&f,sizeof(f));
	}
	file.close();
	file1.close();
	
	file.open("tree1.dat",ios::out|ios::binary);	
	if(file.fail())
	{
		cout<<"file open error!"<<endl;
		exit(0);
	}
	file1.open("tree2.dat",ios::in|ios::binary);	
	if(file1.fail())
	{
		cout<<"file1 open error!"<<endl;
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
	file.open("tree1.dat",ios::in|ios::binary);
				if(file.fail())
				{
					cout<<"file open error!"<<endl;
					exit(0);
				}
				file.read((char *)&f,sizeof(f));
				while(!file.eof())
				{
					cout<<f.data<<" ";
					file.read((char *)&f,sizeof(f));
				}
	file.close();
	cout<<"e:"<<e<<" ";
	if(e==0)
	{
		T=NULL;
	}		
	else
	{
		T=(BiTNode *)malloc(sizeof(BiTNode));
		if(!T)exit(0);
		T->data=e;
		Creat_BiTree(T->lchild);
		Creat_BiTree(T->rchild);
	}	
}

void Clear_BiTree(BiTree &T)//清空树 
{
	if(T)
	{
		Clear_BiTree(T->lchild);
		Clear_BiTree(T->rchild);
		free(T);
		T=NULL;	
	}
	
}
bool Empty_BiTree(BiTree T)//判断树是否为空 
{
	if(!T)
		return false;
}
int Max(int x,int y)//简易的两个数比较大小 
{
	if(x>y)
		return x;
	else
		return y;
}
int Depth_BiTree(BiTree T)//树的深度或者高度 
{
	if(T==NULL)
		return 0;
	else
		 return(Max(Depth_BiTree(T->lchild),Depth_BiTree(T->rchild))+1);
			
}

void Preorder_BiTree(BiTree T)//先序遍历 
{
	
	if(T)
	{
		cout<<T->data<<" ";//遍历根 
		Preorder_BiTree(T->lchild);//遍历左子树 
		Preorder_BiTree(T->rchild);//遍历右子树 
	}
}

void Preorder__BiTree(BiTree T)//先序遍历非递归 
{//用栈实现
//思想：根入栈，出栈 右子树 左子树入栈 
//即保证出栈的顺序是按照根 左子树 右子树。
	Sqstack s;
	BiTNode *p;//树的指针 
	Init_Sqstack(s);//创建一个栈 
	if(T)
	 
	Push(s,T);//如果树不空，根入栈 
	while(!Empty_stack(s))//栈不空为循环条件 
				{
					Pop(s,p);
					cout<<p->data<<" ";
					if(p->rchild)//如果右孩子不空入栈 
					{
						Push(s,p->rchild);			
					}
					
					if(p->lchild)//如果左孩子不空入栈 
					{
						Push(s,p->lchild);			
					}				
				}                                                        
}
void Inorder_BiTree(BiTree T)//中序遍历 
{

	if(T)
	{
		Inorder_BiTree(T->lchild);//遍历左子树 
		cout<<T->data<<" ";//遍历根 
		Inorder_BiTree(T->rchild);//遍历 右子树 
	}	
}
void Inorder__BiTree(BiTree T)//中序遍历非递归 
{
//思想：不断的将根 左子树入栈，出栈时，右子树入栈
//即保证出栈的顺序是按照左子树 根 右子树。 	
	BiTNode *p=T;
	Sqstack s;//建栈 
	Init_Sqstack(s);
	while(p||!Empty_stack(s))
		{
			if(p)
			{
				Push(s,p);//根入栈 		
				p=p->lchild;//指针移到左孩子 
			}
			else
			{
				Pop(s,p);//出栈 
				cout<<p->data<<" ";
				p=p->rchild;//右孩子入栈 
			}
		}
}
void Postorder_BiTree(BiTree T)//后序遍历 
{
	if(T)
	{
		
		Postorder_BiTree(T->lchild);//遍历左子树 
		Postorder_BiTree(T->rchild);//遍历右子树 
		cout<<T->data<<" ";//遍历根 
	}
}
void Postorder__BiTree(BiTree T)//后序遍历非递归 
{
//思想：控制出栈的条件是左子树的左右孩子为空，或者是已经访问过 
	BiTNode *p=T;
	Sqstack s;
	Init_Sqstack(s);//建栈 
	int word=1;
				if(p->rchild)
					{
						Push(s,p->rchild);//右孩子入栈		
					}
				Push(s,p);//根入栈 
				if(p->lchild)//左孩子入栈 
					{
						Push(s,p->lchild);			
					}//先存入第一个右孩子和左孩子，根   
		Gottop_stack(s,p);//得到栈顶元素，即左孩子 
			while(p)//得到左孩子 
			{
				if(p->rchild&&p->rchild->data!='0')
					{
						Push(s,p->rchild);//右孩子入栈			
					}			
				if(p->lchild&&p->lchild->data!='0') 
					{
						Push(s,p->lchild);//左孩子入栈			
					}	
					//注：根是原来的左孩子已经不需要入栈 
			if((p->lchild==NULL||p->lchild->data=='0')&&(p->rchild==NULL||p->rchild->data=='0'))
				{
					Pop(s,p);//出栈 
					cout<<p->data<<" ";
					T=p;
					T->data='0';//将树的数据暂时置‘0’ 
				}
			Gottop_stack(s,p);//得到栈顶元素	
			}	
}
void div_BiTree(BiTree T)//层次遍历 
{
	LinkQueue s;
	BiTNode *p=T;
	Init_Queue(s);//建队 
	if(T)
	{
		EnQueue(s,p);//入队 
	}
	while(!Empty_Queue(s))
	{
		DeQueue(s,p);//出队 
		cout<<p->data<<" ";
		if(p->lchild)
					EnQueue(s,p->lchild);//左孩子入队		
		if(p->rchild)
					EnQueue(s,p->rchild);//右孩子入队			
	}
}
int Leaf_BiTree(BiTree T)//求叶子数即宽度 
{
	if(T==NULL)
		return 0;
	else
	{
		if(T->lchild==NULL&&T->rchild==NULL)
			return 1;
		else
			return(Leaf_BiTree(T->lchild)+(Leaf_BiTree(T->rchild)));
	}
}
int Paixu_BiTree(BiTree T)//判断是否为二叉排序树 
{
//思想：通过比较根与左孩子 根与右孩子的情况 
	if(T==NULL)exit(0);
	else
	{
		if(T->lchild)//如果存在左孩子 
		{
			if(T->data < T->lchild->data)
				return 0;
			else
			{
				if(T->rchild)	
				{
					if(T->data<T->rchild->data)
					{
						Paixu_BiTree(T->lchild);
						Paixu_BiTree(T->rchild);
					}
					else
						return 0;	
				}
				else
				Paixu_BiTree(T->lchild);	
			}
		}
		else//如果不存在左孩子 
		{
			if(T->rchild)	
				if(T->data>T->rchild->data)
				{
						Paixu_BiTree(T->rchild);
				}
			else
				return 0;
		}	
		return 1;	
	}
	
}
void CreatWen_BiTree()//创建存树文件 
{
	fstream file;
	file.open("tree.dat",ios::out|ios::binary);
	if(file.fail())
	{
		cout<<"file open error!"<<endl;
		exit(0);
	}
	BiTNode f;
	int key=1;
	cout<<"please input the all data(0->NULL -1->end):"<<endl;
	while(key)
	{
		int elem;
		cin>>elem;
		f.data=elem;
		f.lchild=NULL;
		f.rchild=NULL;
		if(elem==-1)
		{
			key=0;	
		}
		else
		file.write((char *)&f,sizeof(f));	
	}
	file.close();
	
	file.open("tree.dat",ios::in|ios::binary);
	if(file.fail())
	{
		cout<<"file open error!"<<endl;
		exit(0);
	}
	file.read((char *)&f,sizeof(f));
	while(!file.eof())
	{
		cout<<f.data<<" ";
		file.read((char *)&f,sizeof(f));
	}
	file.close();
	cout<<endl;
}
void CreatHWen_BiTree()
{
	fstream file,file1;
				BiTNode f;
				file.open("tree.dat",ios::in|ios::binary);	
				if(file.fail())
				{
					cout<<"file open error!"<<endl;
					exit(0);
				}
				file1.open("tree1.dat",ios::out|ios::binary);	
				if(file1.fail())
				{
					cout<<"file1 open error!"<<endl;
					exit(0);
				}
				
				file.read((char *)&f,sizeof(f));
				while(!file.eof())
				{
					file1.write((char *)&f,sizeof(f));
					file.read((char *)&f,sizeof(f));
				}
				file.close();
				file1.close();
				
				cout<<endl;
				file.open("tree1.dat",ios::in|ios::binary);
				if(file.fail())
				{
					cout<<"file open error!"<<endl;
					exit(0);
				}
				file.read((char *)&f,sizeof(f));
				while(!file.eof())
				{
					cout<<f.data<<" ";
					file.read((char *)&f,sizeof(f));
				}
				file.close();
}
int main()
{
	int word;
	cout<<"   		二叉树的应用"<<endl;
	cout<<"			0.创建文件"<<endl;
	cout<<"			1.构建二叉树 "<<endl;
	cout<<"			2.求树的高度"<<endl; 
	cout<<"			3.求树的深度"<<endl;
	cout<<"			4.先序遍历"<<endl; 
	cout<<"			5.中序遍历"<<endl; 
	cout<<"			6.后序遍历"<<endl; 
	cout<<"			7.先序遍历非递归"<<endl; 
	cout<<"			8.中序遍历非递归"<<endl; 
	cout<<"			9.后序遍历非递归"<<endl; 
	cout<<"			10.判断是否为二叉排序树"<<endl; 
	cout<<"please input your choose:";
	cin>>word;
	switch(word)
	{
		case 0:
			{
				system("cls");
				cout<<"   		二叉树的应用"<<endl;
				cout<<"			 创建文件"<<endl;
				CreatWen_BiTree();
				CreatHWen_BiTree();								
				break;
			}
		case 1:
			{
				system("cls");
				cout<<"   		二叉树的应用"<<endl;
				cout<<"			 构建二叉树 "<<endl;
				CreatHWen_BiTree();	
				BiTree T;
				Init_BiTree(T);//构建二叉树
				Creat_BiTree(T);//初始化二叉树
				cout<<endl;
				Preorder_BiTree(T);//先序遍历 */ 	
				break;
			}
		case 2:
			{
				system("cls");
				cout<<"   		二叉树的应用"<<endl;
				cout<<"			 求树的高度"<<endl;	
				CreatHWen_BiTree();	
				BiTree T;
				Init_BiTree(T);//构建二叉树
				Creat_BiTree(T);//初始化二叉树 
				cout<<endl;
				cout<<"Depth:"<<Depth_BiTree(T)<<endl;
				break;
			}
		case 3:
			{
				system("cls");
				cout<<"   		二叉树的应用"<<endl;
				cout<<"			 求树的深度"<<endl;	
				CreatHWen_BiTree();	
				BiTree T;
				Init_BiTree(T);//构建二叉树
				Creat_BiTree(T);//初始化二叉树
				cout<<endl;  
				cout<<"deepth:"<<Leaf_BiTree(T)<<endl;
				break;
			}
		case 4:
			{
				system("cls");
				cout<<"   		二叉树的应用"<<endl;
				cout<<"			 先序遍历"<<endl; 
				CreatHWen_BiTree();			
				BiTree T;
				Init_BiTree(T);//构建二叉树
				Creat_BiTree(T);//初始化二叉树  
				cout<<endl;
				Preorder_BiTree(T);//先序遍历 
				break;
			}
		case 5:
			{
				system("cls");
				cout<<"   		二叉树的应用"<<endl;
				cout<<"			  中序遍历"<<endl;
				CreatHWen_BiTree();	 	
				BiTree T;
				Init_BiTree(T);//构建二叉树
				Creat_BiTree(T);//初始化二叉树 
				cout<<endl;
				Inorder_BiTree(T);//中序遍历 
				break;
			}
		case 6:
			{
				system("cls");
				cout<<"   		二叉树的应用"<<endl;
				cout<<"			  后序遍历"<<endl;	
				CreatHWen_BiTree();		
				BiTree T;
				Init_BiTree(T);//构建二叉树
				Creat_BiTree(T);//初始化二叉树
					cout<<endl;	  
				Postorder_BiTree(T);//后序遍历
				break;
			}
		case 7:
			{
				system("cls");
				cout<<"   		二叉树的应用"<<endl;
				cout<<"		先序遍历非递归"<<endl;
				CreatHWen_BiTree();			
				BiTree T;
				Init_BiTree(T);//构建二叉树
				Creat_BiTree(T);//初始化二叉树 
					cout<<endl;	 
				Preorder__BiTree(T);//先序遍历 
				break;
			}
		case 8:
			{
				system("cls");
				cout<<"   		二叉树的应用"<<endl;
				cout<<"		  中序遍历非递归"<<endl;
				CreatHWen_BiTree();	 		
				BiTree T;
				Init_BiTree(T);//构建二叉树
				Creat_BiTree(T);//初始化二叉树 
					cout<<endl;	
				Inorder__BiTree(T);//中序遍历
				break; 
			}
		case 9:
			{
				system("cls");
				cout<<"   		二叉树的应用"<<endl;
				cout<<"		   后序遍历非递归"<<endl;
				CreatHWen_BiTree();	 		
				BiTree T;
				Init_BiTree(T);//构建二叉树
				Creat_BiTree(T);//初始化二叉树 
					cout<<endl;	
				Postorder__BiTree(T);//后序遍历
				break;
			}
		case 10:
			{
				system("cls");
				cout<<"   		二叉树的应用"<<endl;
				cout<<"		判断是否为二叉排序树"<<endl;
				CreatHWen_BiTree();	
				BiTree T;
				Init_BiTree(T);//构建二叉树
				Creat_BiTree(T);//初始化二叉树 
				cout<<endl;	
				cout<<"1(true)or 0(false):"<<Paixu_BiTree(T)<<endl;
				break;
			}
		default:
				cout<<"input data is error!";
							
	}
	return 0;
}
