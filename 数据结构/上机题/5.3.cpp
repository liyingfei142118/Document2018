//3. 编程实现，对二叉树中每个元素值为x的结点，删除以它为根的子树，并释放相应空间。
#include<iostream>
using namespace std;
#include<malloc.h>
typedef struct BiTNode
{
	char data;
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
	char e;
	cin>>e;
	if(e=='$')
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
void Preorder_BiTree(BiTree T)
{
	if(T)
	{
		cout<<T->data;
		Preorder_BiTree(T->lchild);
		Preorder_BiTree(T->rchild);
	}
}
void Delete_node(BiTree &T,char ch)
{
	if(T)
	{
		if(T->data==ch)
			Clear_BiTree(T);
		else
		{
			Delete_node(T->lchild,ch);
			Delete_node(T->rchild,ch);
		}
		
	}
	
}
int main()
{
	BiTree T;
	Init_BiTree(T);//构建二叉树 
	cout<<"please input the all data:";
	Creat_BiTree(T);//初始化二叉树 
	char ch;
	cout<<"please input the node what you want to delete:";
	cin>>ch;
	Delete_node(T,ch);
	Preorder_BiTree(T);//先序遍历
	return 0;
}
