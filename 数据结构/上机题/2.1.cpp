#include<iostream>
using namespace std;
#include<malloc.h>
#define max 100 
typedef struct{
	int *elem;
	int length;
}Sqlist;
void Init_creat_list(Sqlist &L)//创建顺序表 
{
	L.elem=(int *)malloc(max*sizeof(int));
	if(!L.elem)throw("error");
	cout<<"the sum of number:";//初始化顺序表 
	int n;
	cin>>n;
	cout<<endl;
	for(int i=0;i<n;i++)
	{
		cin>>L.elem[i];//输入n个数 
	}
	L.length=n;	
}
void Print_list(Sqlist L)//打印顺序表 
{
	if(!L.elem)throw("The sqlist data is empty.");
	int i=1;
/*	while(L.elem[i]&&i<=L.length)
	{
		if((i)%6==0)
		cout<<endl;
		cout<<L.elem[i]<<" ";
		i++;
	}*/
	for(i=0; i<L.length; i++)
	{
		if(i%5==0)//输出5个后换行 
		cout<<endl;
		cout<<L.elem[i]<<" ";
	}
}
void Insert_sq(Sqlist &L,int e,int j,int i)//将e插入到L.elem[j]前面 
{
	for(int k=i;k>j;k--)
	{
		L.elem[k]=L.elem[k-1];
	}
	L.elem[j]=e;
}
void Insert_array(Sqlist &L)//插入排序法 
{
	for(int i=1;i<L.length;i++)
	{
		for(int j=0;j<i;j++)
		if(L.elem[i]<=L.elem[j])
		{
			Insert_sq(L,L.elem[i],j,i);//将L.elem[i]插入到L.elem[j]前面 
		}
	}
}

int main()
{
	Sqlist L;
	Init_creat_list(L);
	Print_list(L);
	Insert_array(L);
	Print_list(L);
	return 0;
} 
