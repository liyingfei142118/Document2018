#include<iostream>
using namespace std;
#include<malloc.h>
#define max 100 
typedef struct{
	int *elem;
	int length;
}Sqlist;
void Init_creat_list(Sqlist &L)//����˳��� 
{
	L.elem=(int *)malloc(max*sizeof(int));
	if(!L.elem)throw("error");
	cout<<"the sum of number:";//��ʼ��˳��� 
	int n;
	cin>>n;
	cout<<endl;
	for(int i=0;i<n;i++)
	{
		cin>>L.elem[i];//����n���� 
	}
	L.length=n;	
}
void Print_list(Sqlist L)//��ӡ˳��� 
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
		if(i%5==0)//���5������ 
		cout<<endl;
		cout<<L.elem[i]<<" ";
	}
}
void Insert_sq(Sqlist &L,int e,int j,int i)//��e���뵽L.elem[j]ǰ�� 
{
	for(int k=i;k>j;k--)
	{
		L.elem[k]=L.elem[k-1];
	}
	L.elem[j]=e;
}
void Insert_array(Sqlist &L)//�������� 
{
	for(int i=1;i<L.length;i++)
	{
		for(int j=0;j<i;j++)
		if(L.elem[i]<=L.elem[j])
		{
			Insert_sq(L,L.elem[i],j,i);//��L.elem[i]���뵽L.elem[j]ǰ�� 
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
