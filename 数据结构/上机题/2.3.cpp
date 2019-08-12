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
	cout<<"the sum of the people:";//初始化顺序表 
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
	for(i=0; i<L.length; i++)
	{
		if(i%5==0)
		cout<<endl;
		cout<<L.elem[i]<<" ";
	}
}
void Combine_array(Sqlist &L,Sqlist L1)//合并两个顺序表 
{
	int t=L.length+L1.length;
	if(t>max) //判断顺序表的长度 
		{
		Sqlist Q;
		Q.elem=(int *)realloc(L.elem,(max+(t-max))*sizeof(int));
		if(!Q.elem)throw("error1");
		L.elem=Q.elem;
		}
	for(int i=0;i<L1.length;i++)
	for(int j=0;j<L.length;j++)
	{
		if(L1.elem[i]==L.elem[j])//如果相等，就不插入 
			break;
		if(L1.elem[i]<L.elem[j])
		{
			for(int k=L.length;k>j;k--)//在链表中插入 
					L.elem[k]=L.elem[k-1];//j位置后面的元素全部后移 
			L.elem[j]=L1.elem[i];//在j位置插入 
			L.length++;// L中元素加1 
			break;
		}
		if(j==(L.length-1)&&L1.elem[i]>L.elem[j])//在链表的最后 
		{
			L.elem[L.length]=L1.elem[i];
			L.length++;
			break;
		}
	}
			
}
int main()
{
	Sqlist L,L1;//定义2个顺序表 
	Init_creat_list(L);//创建第一个顺序表 
	Print_list(L);//打印顺序表 
	cout<<endl; 
	Init_creat_list(L1);//创建第二个顺序表 
	Print_list(L1);//打印顺序表
	cout<<endl;
	Combine_array(L,L1);
	Print_list(L);
	return 0;
} 
