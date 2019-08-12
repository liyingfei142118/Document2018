//1. 编程实现书P121  ADT BinaryTree 基本操作20个，用二叉链表结构实现；
#include<iostream>
using namespace std;
#include<malloc.h>
typedef struct BiTNode
{
	int data;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

void Init_BiTree(BiTree &T)
{
	T=(BiTNode *)malloc(sizeof(BiTNode));
	if(!T)exit(0);
	T->lchild=T->rchild=NULL;	
} 
void Creat_BiTree(BiTree &T)
{
	int e;
	cin>>e;
	if(e==0)
		T=NULL;
	else
	{
		T=(BiTNode *)malloc(sizeof(BiTNode));
		if(!T)exit(0);
		T->data=e;
		Creat_BiTree(T->lchild);
		Creat_BiTree(T->rchild);
	}	
}
void Destory_BiTree(BiTree &T)
{
	if(T)
	{
		Destory_BiTree(T->lchild);
		Destory_BiTree(T->rchild);
		free(T);
		T=NULL;	
	}
}
void Clear_BiTree(BiTree &T)
{
	if(T)
	{
		Clear_BiTree(T->lchild);
		Clear_BiTree(T->rchild);
		free(T);
		T=NULL;	
	}
	
}
bool Empty_BiTree(BiTree T)
{
	if(!T)
		return false;
}
int max(int x,int y)
{
	if(x>y)
		return x;
	else
		return y;
}
int Depth_BiTree(BiTree T)
{
	if(T==NULL)
		return 0;
/*	else
		{
			int l,r;
			l=Depth_BiTree(T->lchild);
			r=Depth_BiTree(T->rchild);
			if(l>r)
				return (l+1);
			else
				return (r+1);
		}*/
		else
		 return(max(Depth_BiTree(T->lchild),Depth_BiTree(T->rchild))+1);
			
}
int Root_BiTree(BiTree T)
{
	if(T)
		return T->data;
}
/*void Value_BiTree(BiTree T)
{
	if(T)
	{
		cout<<T->data;
		Preorder_BiTree(T->lchild);
		Preorder_BiTree(T->rchild);
	}
	
}*/
void Assign_BiTree(BiTree &T,char e,char value)
{
	if(T)
	{
		if(T->data==e)
			{
				T->data=value;
			}
		Assign_BiTree(T->lchild,e,value);
		Assign_BiTree(T->rchild,e,value);
	}
}
char Parent_BiTree(BiTree T,char e,int flag,char value)
{
	if(flag)return value;
	if(T)
	{
		if(T->lchild->data==e||T->rchild->data==e)
		{
			flag=1;
			value=T->data;
			return value;
		}
		else
		{
			value=Parent_BiTree(T->lchild,e,flag,value);
			value=Parent_BiTree(T->rchild,e,flag,value);
		}
		

	}		
}
char Left_BiTree(BiTree T,char e,int flag,char value)
{
	if (flag) return value; 
	if(T)
	{
		if(T->data==e)
			{
				if(T->lchild)
					{
						T=T->lchild;
						flag=1;
						value=T->data;
						return value;
					}
				else
					{
						flag=1;
						value='$';
					}
			}
		else
		{
			value=Left_BiTree(T->lchild,e,flag,value);
			value=Left_BiTree(T->rchild,e,flag,value);
		}
		
	}
	return value;	
}
char Right_BiTree(BiTree T,char e,int flag,char value)
{
	if (flag) return value; 
	if(T)
	{
		if(T->data==e)
			{
				if(T->rchild)
					{
						T=T->rchild;
						flag=1;
						value=T->data;
						return value;
					}
				else
					{
						flag=1;
						value='$';
					}	
			}
		else
		{
			value=Left_BiTree(T->lchild,e,flag,value);
			value=Left_BiTree(T->rchild,e,flag,value);
		}
		
	}
	return value;

}
void Insert_BiTree(BiTree &T,char e,char c)
{
	if(T)
	{
		if(T->data==e)
			{
				BiTree T1;
				T1=(BiTNode *)malloc(sizeof(BiTNode));
				T1->data=c;
				if(T->lchild==NULL)
				{
					T->lchild=T1;
					T->lchild->lchild=NULL;
					T->lchild->rchild=NULL;
				}		
				else if(T->rchild==NULL)
				{
					T->rchild=T1;
					T->rchild->lchild=NULL;
					T->rchild->rchild=NULL;
				}	
			}
		else
		{
			Insert_BiTree(T->lchild,e,c);
			Insert_BiTree(T->rchild,e,c);
		}
		
	}
	
}
void Delete_BiTree(BiTree &T,char e)
{
	if(T)
	{
		if(T->data==e)
			{
			Clear_BiTree(T);
			}
		else
		{
			Delete_BiTree(T->lchild,e);
			Delete_BiTree(T->rchild,e);
		}
	
	}
}
void Preorder_BiTree(BiTree T)
{
	if(T)
	{
		cout<<T->data<<" ";
		Preorder_BiTree(T->lchild);
		Preorder_BiTree(T->rchild);
	}
}
void Inorder_BiTree(BiTree T)
{
		if(T)
	{
		Inorder_BiTree(T->lchild);
		cout<<T->data;
		Inorder_BiTree(T->rchild);
	}	
}
void Postorder_BiTree(BiTree T)
{
		if(T)
	{
		
		Postorder_BiTree(T->lchild);
		Postorder_BiTree(T->rchild);
		cout<<T->data;
	}
}
void Levelorder_BiTree(BiTree T)
{
}
int Leaf_BiTree(BiTree T)
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
int Paixu_BiTree(BiTree T)
{
	if(T==NULL)exit(0);
	else
	{
		if(T->lchild)
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
		else
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
int main()
{
	BiTree T;
	Init_BiTree(T);//构建二叉树 
	cout<<"please input the all data:";
	Creat_BiTree(T);//初始化二叉树 
	cout<<"Depth:"<<Depth_BiTree(T)<<endl;
	Preorder_BiTree(T);//先序遍历 
	cout<<endl;
	cout<<Paixu_BiTree(T)<<endl;
	//cout<<Leaf_BiTree(T)<<endl;
/*	Inorder_BiTree(T);//中序遍历 
	cout<<endl;
	Postorder_BiTree(T);//后序遍历 
	cout<<endl;*/
	
/*	Clear_BiTree(T);//清空二叉树 
	Preorder_BiTree(T);//先序遍历 
/*	char e,value;
	cout<<"please input e and value:";
	cin>>e>>value;
	Assign_BiTree(T,e,value);//改变某节点的值 
	cout<<endl;
	Preorder_BiTree(T);
	cout<<endl;
	char c=Parent_BiTree(T,e,0,'0');//找某节点的双亲 
	if(c=='0')
		cout<<"e is no exit!"<<endl;
	else if(c=='$')
		cout<<"e has no parent!"<<endl;
	else
		cout<<"e parent:"<<c<<endl;
		
	char ch=Left_BiTree(T,e,0,'0');//找某节点的左孩子 
	if(ch=='0')
		cout<<"e is no 
		exit!"<<endl;
	else if(ch=='$')
		cout<<"e has no left child!"<<endl;
	else
		cout<<"e left child:"<<ch<<endl;
	
	char ch1=Right_BiTree(T,e,0,'0');//找某节点的右孩子 
	if(ch1=='0')
		cout<<"e is no exit!"<<endl;
	else if(ch1=='$')
		cout<<"e has no right child!"<<endl;
	else
		cout<<"e right child:"<<ch1<<endl;*/
	

	
/*	char m,m1,c;
	cout<<"please input the root of what you want to insert  or delete and m:";
	cin>>m>>m1>>c;
	cout<<endl;
	/*Insert_BiTree(T,m,c);//插入结点 
	Preorder_BiTree(T);*/
/*	Delete_BiTree(T,m1);//删除结点 
	Preorder_BiTree(T);*/
	return 0;
}
