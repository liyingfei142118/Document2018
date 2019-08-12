//5. 设二叉排序树T，元素值为整数，输入整数X，若存在输出该结点，
//若不存在，输出最接近X 值的两个结点（有可能一个）。
#include<iostream>
using namespace std;
#include<malloc.h>
#define max 100
#define min 10
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
void Preorder_BiTree(BiTree T)
{
	if(T)
	{
		cout<<T->data<<" ";
		Preorder_BiTree(T->lchild);
		Preorder_BiTree(T->rchild);
	}
}
typedef struct
{
	int *elem;
	int length;
	int listsize;
}SqList;
void Init_sq(SqList &L)
{
	L.elem=(int *)malloc(max*sizeof(int));
	if(!L.elem)exit(0);
	L.length=0;
	L.listsize=max;
}
void Traverse_sq(SqList L)//遍历所有元素 
{
		if (!L.elem)
		return;
		int i=0;
		while(L.elem[i]&&i<L.length)
		{
			if((i)%10==0)
			{ 
				cout<<endl;
			}
			cout<<L.elem[i]<<" ";
			i++;
		}
		cout<<endl;
}
int Linkx_BiTree(BiTree T,SqList &L,int &i)
{
	if(T)
	{
		Linkx_BiTree(T->lchild,L,i) ;
		L.elem[i]=T->data;
		i++;
		L.length++;
		Linkx_BiTree(T->rchild,L,i);
	}

}
int main()
{
	BiTree T;
	Init_BiTree(T);//构建二叉树 
	cout<<"please input the all data:";
	Creat_BiTree(T);//初始化二叉树
	Preorder_BiTree(T);
	cout<<endl;
	int x;
	cout<<"please input x:";
	cin>>x;
	SqList L;
	Init_sq(L);
	int i=0;
	Linkx_BiTree(T,L,i); 
	Traverse_sq(L);
	cout<<endl;
	if(x<L.elem[0])
		{
			cout<<L.elem[0]<<endl;
		}
	else if(x>L.elem[L.length-1])
	{
		cout<<L.elem[L.length]<<endl;
	}
	else
	for(int i=0;i<L.length;i++)
	{
		cout<<"i:"<<i<<" ";
		if(x==L.elem[i])
		{
			cout<<x<<endl;
			break;
		}
		if((x>L.elem[i])&&(x<L.elem[i+1]))
		{
			cout<<L.elem[i]<<" "<<L.elem[i+1];
			break;
		}
	}
}
