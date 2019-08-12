#include<iostream>
using namespace std;
#include<malloc.h>
#define max 100 
typedef struct{
	int *elem;
	int length;
}Sqlist;
void Init_creat_list(Sqlist &L)
{
	L.elem=(int *)malloc(max*sizeof(int));
	if(!L.elem)throw("error");
	cout<<"the sum of the people:";
	int n;
	cin>>n;
	cout<<endl;
	for(int i=0;i<n;i++)
	{
		L.elem[i]=i;
	}
	L.length=n;	
}
void Print_list(Sqlist L)
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
		if(i%5==0)
		cout<<endl;
		cout<<L.elem[i]<<" ";
	}
}
void Daozhi_list(Sqlist &L)
{
	if(!L.elem)throw("The sqlist data is empty.");
	int i,t,j=L.length-1;
	for(i=0;i<L.length/2;i++)
	{
		t=L.elem[i];
		L.elem[i]=L.elem[j];
		L.elem[j]=t;
		j--; 
	}
}
int main()
{
	Sqlist L;
	Init_creat_list(L);
	Print_list(L);
	cout<<endl;
	Daozhi_list(L);
	Print_list(L);
	cout<<endl;
} 
