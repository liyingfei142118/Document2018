#include<iostream>
using namespace std;
#include<malloc.h>
#include<fstream>
#define max 100
#define add 10

typedef struct BiTNode//��������ṹ�� 
{
	int data;
	struct BiTNode *lchild,*rchild;//���Һ���ָ�� 
}BiTNode,*BiTree;

typedef struct QNode//���� 
{
	BiTNode *data;//��int data������BITNode* data������ָ�룩 
	struct QNode *next;//��һ�����ݵ�ָ�� 
}QNode,*QueuePtr;
typedef struct
{
	QueuePtr front;//����ͷ 
	QueuePtr rear;//����β 
}LinkQueue;
typedef struct//ջ�Ľṹ�� 
{
	BiTNode * *base;//ջ��ָ�� 
	BiTNode * *top;//ջ��ָ�� 
	int stacksize;//ջ�Ĵ�С 
}Sqstack;

void Init_Queue(LinkQueue &s);//�������� 
void EnQueue(LinkQueue &s,BiTNode *e);//��� 
void DeQueue(LinkQueue &s,BiTNode * &e);//���� 
int Empty_Queue(LinkQueue s);//�ж϶��Ƿ�Ϊ��
void Init_Sqstack(Sqstack &s);//����ջ 
void Push(Sqstack &s,BiTNode *e);//��ջ
void Pop(Sqstack &s,BiTNode* &e);//��ջ 
int Empty_stack(Sqstack s);//�ж�ջ�Ƿ�Ϊ�� 
void Gottop_stack(Sqstack s,BiTNode* &e);//�õ�ջ��Ԫ�� 
void Init_BiTree(BiTree &T);//���������� 
void Creat_BiTree(BiTree &T);//�������������� 
void Clear_BiTree(BiTree &T);//����� 
bool Empty_BiTree(BiTree T);//�ж����Ƿ�Ϊ�� 
int Max(int x,int y);//���׵��������Ƚϴ�С
int Depth_BiTree(BiTree T);//������Ȼ��߸߶� 
void Preorder_BiTree(BiTree T);//������� 
void Preorder__BiTree(BiTree T);//��������ǵݹ� 
void Inorder_BiTree(BiTree T);//�������
void Inorder__BiTree(BiTree T);//��������ǵݹ�
void Postorder_BiTree(BiTree T);//�������
void Postorder__BiTree(BiTree T);//��������ǵݹ�
void div_BiTree(BiTree T);//��α��� 
int Leaf_BiTree(BiTree T);//��Ҷ��������� 
int Paixu_BiTree(BiTree T);//�ж��Ƿ�Ϊ���������� 
void CreatWen_BiTree();//���������ļ� 
void CreatHWen_BiTree();//���ļ���ֵ����

void Init_Queue(LinkQueue &s)//�������� 
{
	s.front=s.rear=(QueuePtr)malloc(sizeof(QNode));
	if(!s.front)exit(0);
	s.front->next=NULL;	
}
void EnQueue(LinkQueue &s,BiTNode *e)//��� 
{
	QueuePtr p;
	p=(QueuePtr)malloc(sizeof(QNode));//����һ����Ӧ�ռ������ 
	if(!p)exit(0);
	p->data=e;
	p->next=NULL;
	
	s.rear->next=p;//���Կ�����ͷΪ�գ���β���� 
	s.rear=p;
}
void DeQueue(LinkQueue &s,BiTNode * &e)//���� 
{
	if(s.rear==s.front)exit(0);
	
	QueuePtr p;
	p=s.front->next;
	e=p->data;
	s.front->next=p->next;
	
	if(s.rear==p)s.rear=s.front;
	free(p);//ɾ���ռ� 
}
int Empty_Queue(LinkQueue s)//�ж϶��Ƿ�Ϊ�� 
{
	if(s.rear==s.front)
		return 1;
	else
		return 0;
}

void Init_Sqstack(Sqstack &s)//����ջ 
{
	s.base=(BiTNode **)malloc(max*sizeof(BiTNode*));
	if(!s.base)exit(0);//���ʧ�ܣ��ر� 
	s.top=s.base;
	s.stacksize=max;
}

void Push(Sqstack &s,BiTNode *e)//��ջ 
{//s.top-s.baseΪջ�ĳ��� 
	if(s.top-s.base>=s.stacksize)//���ջ�� 
	{
		s.base=(BiTNode **) realloc (s.base,(s.stacksize+add)*sizeof( BiTNode*));
		if( !s.base)exit(0);
		s.top=s.base+s.stacksize;
		s.stacksize+=add;
	}
	*s.top=e;//ջ����ֵ 
	s.top++;//ջ��ָ������ 
}
void Pop(Sqstack &s,BiTNode* &e)//��ջ 
{
	if(s.base==s.top)exit(0);//���ջ�գ��ر� 
	s.top--;//��Ϊջ��Ϊ�գ�����ջ��ָ�����Ƽ���ջ 
	e=*s.top;
	//e ��ֵ ջ��ǰֵ ����ջ�����ݻ���ָ�� 
}
int Empty_stack(Sqstack s)//�ж�ջ�Ƿ�Ϊ�� 
{
	if(s.base==s.top)
		return 1;
	else
		return 0;
}
void Gottop_stack(Sqstack s,BiTNode* &e)//�õ�ջ��Ԫ�� 
{
	if(s.base==s.top)exit(0);
	s.top--;
	//ֻ��ջ��Ԫ������ 
	e=*s.top;
}

void Init_BiTree(BiTree &T)//���������� 
{
	T=(BiTNode *)malloc(sizeof(BiTNode));
	if(!T)exit(0);
	T->lchild=T->rchild=NULL;//���Һ����ÿ�	
} 
void Creat_BiTree(BiTree &T)//�������������� 
{//��������������������� 
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

void Clear_BiTree(BiTree &T)//����� 
{
	if(T)
	{
		Clear_BiTree(T->lchild);
		Clear_BiTree(T->rchild);
		free(T);
		T=NULL;	
	}
	
}
bool Empty_BiTree(BiTree T)//�ж����Ƿ�Ϊ�� 
{
	if(!T)
		return false;
}
int Max(int x,int y)//���׵��������Ƚϴ�С 
{
	if(x>y)
		return x;
	else
		return y;
}
int Depth_BiTree(BiTree T)//������Ȼ��߸߶� 
{
	if(T==NULL)
		return 0;
	else
		 return(Max(Depth_BiTree(T->lchild),Depth_BiTree(T->rchild))+1);
			
}

void Preorder_BiTree(BiTree T)//������� 
{
	
	if(T)
	{
		cout<<T->data<<" ";//������ 
		Preorder_BiTree(T->lchild);//���������� 
		Preorder_BiTree(T->rchild);//���������� 
	}
}

void Preorder__BiTree(BiTree T)//��������ǵݹ� 
{//��ջʵ��
//˼�룺����ջ����ջ ������ ��������ջ 
//����֤��ջ��˳���ǰ��ո� ������ ��������
	Sqstack s;
	BiTNode *p;//����ָ�� 
	Init_Sqstack(s);//����һ��ջ 
	if(T)
	 
	Push(s,T);//��������գ�����ջ 
	while(!Empty_stack(s))//ջ����Ϊѭ������ 
				{
					Pop(s,p);
					cout<<p->data<<" ";
					if(p->rchild)//����Һ��Ӳ�����ջ 
					{
						Push(s,p->rchild);			
					}
					
					if(p->lchild)//������Ӳ�����ջ 
					{
						Push(s,p->lchild);			
					}				
				}                                                        
}
void Inorder_BiTree(BiTree T)//������� 
{

	if(T)
	{
		Inorder_BiTree(T->lchild);//���������� 
		cout<<T->data<<" ";//������ 
		Inorder_BiTree(T->rchild);//���� ������ 
	}	
}
void Inorder__BiTree(BiTree T)//��������ǵݹ� 
{
//˼�룺���ϵĽ��� ��������ջ����ջʱ����������ջ
//����֤��ջ��˳���ǰ��������� �� �������� 	
	BiTNode *p=T;
	Sqstack s;//��ջ 
	Init_Sqstack(s);
	while(p||!Empty_stack(s))
		{
			if(p)
			{
				Push(s,p);//����ջ 		
				p=p->lchild;//ָ���Ƶ����� 
			}
			else
			{
				Pop(s,p);//��ջ 
				cout<<p->data<<" ";
				p=p->rchild;//�Һ�����ջ 
			}
		}
}
void Postorder_BiTree(BiTree T)//������� 
{
	if(T)
	{
		
		Postorder_BiTree(T->lchild);//���������� 
		Postorder_BiTree(T->rchild);//���������� 
		cout<<T->data<<" ";//������ 
	}
}
void Postorder__BiTree(BiTree T)//��������ǵݹ� 
{
//˼�룺���Ƴ�ջ�������������������Һ���Ϊ�գ��������Ѿ����ʹ� 
	BiTNode *p=T;
	Sqstack s;
	Init_Sqstack(s);//��ջ 
	int word=1;
				if(p->rchild)
					{
						Push(s,p->rchild);//�Һ�����ջ		
					}
				Push(s,p);//����ջ 
				if(p->lchild)//������ջ 
					{
						Push(s,p->lchild);			
					}//�ȴ����һ���Һ��Ӻ����ӣ���   
		Gottop_stack(s,p);//�õ�ջ��Ԫ�أ������� 
			while(p)//�õ����� 
			{
				if(p->rchild&&p->rchild->data!='0')
					{
						Push(s,p->rchild);//�Һ�����ջ			
					}			
				if(p->lchild&&p->lchild->data!='0') 
					{
						Push(s,p->lchild);//������ջ			
					}	
					//ע������ԭ���������Ѿ�����Ҫ��ջ 
			if((p->lchild==NULL||p->lchild->data=='0')&&(p->rchild==NULL||p->rchild->data=='0'))
				{
					Pop(s,p);//��ջ 
					cout<<p->data<<" ";
					T=p;
					T->data='0';//������������ʱ�á�0�� 
				}
			Gottop_stack(s,p);//�õ�ջ��Ԫ��	
			}	
}
void div_BiTree(BiTree T)//��α��� 
{
	LinkQueue s;
	BiTNode *p=T;
	Init_Queue(s);//���� 
	if(T)
	{
		EnQueue(s,p);//��� 
	}
	while(!Empty_Queue(s))
	{
		DeQueue(s,p);//���� 
		cout<<p->data<<" ";
		if(p->lchild)
					EnQueue(s,p->lchild);//�������		
		if(p->rchild)
					EnQueue(s,p->rchild);//�Һ������			
	}
}
int Leaf_BiTree(BiTree T)//��Ҷ��������� 
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
int Paixu_BiTree(BiTree T)//�ж��Ƿ�Ϊ���������� 
{
//˼�룺ͨ���Ƚϸ������� �����Һ��ӵ���� 
	if(T==NULL)exit(0);
	else
	{
		if(T->lchild)//����������� 
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
		else//������������� 
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
void CreatWen_BiTree()//���������ļ� 
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
	cout<<"   		��������Ӧ��"<<endl;
	cout<<"			0.�����ļ�"<<endl;
	cout<<"			1.���������� "<<endl;
	cout<<"			2.�����ĸ߶�"<<endl; 
	cout<<"			3.���������"<<endl;
	cout<<"			4.�������"<<endl; 
	cout<<"			5.�������"<<endl; 
	cout<<"			6.�������"<<endl; 
	cout<<"			7.��������ǵݹ�"<<endl; 
	cout<<"			8.��������ǵݹ�"<<endl; 
	cout<<"			9.��������ǵݹ�"<<endl; 
	cout<<"			10.�ж��Ƿ�Ϊ����������"<<endl; 
	cout<<"please input your choose:";
	cin>>word;
	switch(word)
	{
		case 0:
			{
				system("cls");
				cout<<"   		��������Ӧ��"<<endl;
				cout<<"			 �����ļ�"<<endl;
				CreatWen_BiTree();
				CreatHWen_BiTree();								
				break;
			}
		case 1:
			{
				system("cls");
				cout<<"   		��������Ӧ��"<<endl;
				cout<<"			 ���������� "<<endl;
				CreatHWen_BiTree();	
				BiTree T;
				Init_BiTree(T);//����������
				Creat_BiTree(T);//��ʼ��������
				cout<<endl;
				Preorder_BiTree(T);//������� */ 	
				break;
			}
		case 2:
			{
				system("cls");
				cout<<"   		��������Ӧ��"<<endl;
				cout<<"			 �����ĸ߶�"<<endl;	
				CreatHWen_BiTree();	
				BiTree T;
				Init_BiTree(T);//����������
				Creat_BiTree(T);//��ʼ�������� 
				cout<<endl;
				cout<<"Depth:"<<Depth_BiTree(T)<<endl;
				break;
			}
		case 3:
			{
				system("cls");
				cout<<"   		��������Ӧ��"<<endl;
				cout<<"			 ���������"<<endl;	
				CreatHWen_BiTree();	
				BiTree T;
				Init_BiTree(T);//����������
				Creat_BiTree(T);//��ʼ��������
				cout<<endl;  
				cout<<"deepth:"<<Leaf_BiTree(T)<<endl;
				break;
			}
		case 4:
			{
				system("cls");
				cout<<"   		��������Ӧ��"<<endl;
				cout<<"			 �������"<<endl; 
				CreatHWen_BiTree();			
				BiTree T;
				Init_BiTree(T);//����������
				Creat_BiTree(T);//��ʼ��������  
				cout<<endl;
				Preorder_BiTree(T);//������� 
				break;
			}
		case 5:
			{
				system("cls");
				cout<<"   		��������Ӧ��"<<endl;
				cout<<"			  �������"<<endl;
				CreatHWen_BiTree();	 	
				BiTree T;
				Init_BiTree(T);//����������
				Creat_BiTree(T);//��ʼ�������� 
				cout<<endl;
				Inorder_BiTree(T);//������� 
				break;
			}
		case 6:
			{
				system("cls");
				cout<<"   		��������Ӧ��"<<endl;
				cout<<"			  �������"<<endl;	
				CreatHWen_BiTree();		
				BiTree T;
				Init_BiTree(T);//����������
				Creat_BiTree(T);//��ʼ��������
					cout<<endl;	  
				Postorder_BiTree(T);//�������
				break;
			}
		case 7:
			{
				system("cls");
				cout<<"   		��������Ӧ��"<<endl;
				cout<<"		��������ǵݹ�"<<endl;
				CreatHWen_BiTree();			
				BiTree T;
				Init_BiTree(T);//����������
				Creat_BiTree(T);//��ʼ�������� 
					cout<<endl;	 
				Preorder__BiTree(T);//������� 
				break;
			}
		case 8:
			{
				system("cls");
				cout<<"   		��������Ӧ��"<<endl;
				cout<<"		  ��������ǵݹ�"<<endl;
				CreatHWen_BiTree();	 		
				BiTree T;
				Init_BiTree(T);//����������
				Creat_BiTree(T);//��ʼ�������� 
					cout<<endl;	
				Inorder__BiTree(T);//�������
				break; 
			}
		case 9:
			{
				system("cls");
				cout<<"   		��������Ӧ��"<<endl;
				cout<<"		   ��������ǵݹ�"<<endl;
				CreatHWen_BiTree();	 		
				BiTree T;
				Init_BiTree(T);//����������
				Creat_BiTree(T);//��ʼ�������� 
					cout<<endl;	
				Postorder__BiTree(T);//�������
				break;
			}
		case 10:
			{
				system("cls");
				cout<<"   		��������Ӧ��"<<endl;
				cout<<"		�ж��Ƿ�Ϊ����������"<<endl;
				CreatHWen_BiTree();	
				BiTree T;
				Init_BiTree(T);//����������
				Creat_BiTree(T);//��ʼ�������� 
				cout<<endl;	
				cout<<"1(true)or 0(false):"<<Paixu_BiTree(T)<<endl;
				break;
			}
		default:
				cout<<"input data is error!";
							
	}
	return 0;
}
