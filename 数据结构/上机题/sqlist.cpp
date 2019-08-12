#include<iostream>
using namespace std;
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

#define max 100
#define add 10
typedef struct
{
	int *elem;
	int length;
	int listsize;
}SqList;
void InitList_sq(SqList &L)// 构造顺序表 
{
	L.elem=(int *)malloc(max*sizeof(int));
	if(!L.elem)throw("error!");
	L.length=0;
	L.listsize=max;
}
void DestroyList(SqList &L)//销毁表 
{
	free(L.elem);
	L.elem=NULL;
}
void ClearList(SqList &L)//清空表 
{
	free(L.elem);
	L.elem=NULL;
}
bool ListEmpty(SqList L)//判断表是否为空 
{
	if(L.elem==NULL)//if(L.length!=0)
	return true;
	else
	return false;
}
int ListLength(SqList L)//返回表的长度 
{
	return L.length;
}

void GetElem(SqList L,int i,int &e)//从表中得到位置i的元素 
{
	if(i<0||i>L.length)throw("error!");
	e=L.elem[i-1];
}
void LocateElem(SqList L,int e)//确定元素的位置 
{
	if(!L.elem)throw("error");
	int i;
	for(i=0;i<L.length;i++)
	{
		if(L.elem[i]==e)
		cout<<"the e position:"<<(i+1)<<endl;
	}
	if(i==L.length-1&&L.elem[i]!=e)
		cout<<"the e no exit."<<endl;
}
void PriorElem(SqList L,int cur_e,int &pre_e)//找到当前元素的前一个数 
{
	if(!L.elem)throw("error");
	int i;
	for(i=0;i<L.length;i++)
	{
		if(L.elem[i]==cur_e)
		pre_e=L.elem[i-1];	
	}
		if(i==L.length-1&&L.elem[i]!=cur_e)
		cout<<"the e no exit."<<endl;
	
}
void NextElem(SqList L,int cur_e,int &next_e)//找到当前元素的后一个数 
{
	if(!L.elem)throw("error");
	int i;
	for(int i=0;i<L.length;i++)
	{
		if(L.elem[i]==cur_e&&i<(L.length-1))
		next_e=L.elem[i+1];
	}
	if(i==L.length-1)
		cout<<"the e no exit."<<endl;
}
void ListInsert(SqList &L,int i,int e)//在位置i插入元素 
{
	if(i<0&&i>L.length)throw("you input is error!")	
	if(L.length==L.listsize)
	{
		SqList Q;
		Q.elem=(int *)malloc((max+add)*sizeof(int));
		if(!Q.elem)throw("error1");
		Q.elem=L.elem;
	}
	for(int j=L.length;j>=i;j--)
		L.elem[j]=L.elem[j-1];
	
	L.elem[i-1]=e;
	L.length++;	
}
void ListDelete(SqList &L,int i,int e)//删除位置i的元素 
{
	if(i<0&&i>L.length)throw("you input is error!");
	e=L.elem[i-1];
	for(int j=i;j<L.length;j++)
	L.elem[j-1]=L.elem[j];
	L.length--;	
}
void visit(int i)//输出所有元素 
{
	cout<<i<<" ";
}
void ListTraverse(SqList L)//遍历所有元素 
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
			visit(L.elem[i]);
			i++;
		}
}
void fuzhi(SqList &L)//对顺序表初始化 
{
	for(int i=0;i<max;i++)
	{	
		L.elem[i]=i+1;
		cout<<L.elem[i]<<" ";
		L.length++;
	}
}
int main()
{
	SqList L;
	InitList_sq(L);
	fuzhi(L);
	ListTraverse(L);
	cout<<endl;
	//DestroyList(L);

/*	int i,e;
	cout<<"the location of the element what you want:";
	cin>>i;
	GetElem(L,i,e);
	cout<<"the element:"<<e<<endl;*/
	
/*	int k;
	cout<<"the number which you want defining:";
	cin>>k;
	LocateElem(L,k);*/

/*	int cur_e,pre_e,next_e;
	cout<<"the cur_e:";
	cin>>cur_e;
	PriorElem(L,cur_e,pre_e);
	NextElem(L,cur_e,next_e);
	cout<<"the pre_e:"<<pre_e<<endl;
	cout<<"the next_e:"<<next_e;*/
	
	/*int m,n;
	cout<<"the location and the element:";
	cin>>m>>n;
	ListInsert(L,m,n);	*/
	
	int i,e;
	cout<<"the delete element:";
	cin>>i; 
	ListDelete(L,i,e);
	cout<<"the delete element:"<<e;
	ListTraverse(L);

	return 0;
}



