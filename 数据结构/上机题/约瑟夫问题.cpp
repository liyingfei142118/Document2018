#include<iostream>
using namespace std;
#include<malloc.h>
#define max 100 
//n people ,baoshu s,outquoue m;
typedef struct{
	int *elem;
	int length;
}yuosefu;
void Init_creat_list(yuosefu &L)
{
	L.elem=(int *)malloc(max*sizeof(int));
	if(!L.elem)throw("error");
	cout<<"the sum of the people:";
	int n;
	cin>>n;
	cout<<endl;
	for(int i=1;i<=n;i++)
	{
		L.elem[i]=i;
	}
	L.length=n;	
}
void Print_list(yuosefu L)
{
	if(!L.elem)throw("The sqlist data is empty.");
	int i=1;
	while(L.elem[i]&&i<=L.length)
	{
		if((i)%6==0)
		cout<<endl;
		cout<<L.elem[i]<<" ";
		i++;
	}
}
void operation(yuosefu L,int s,int m)
{
	int i=s,k=1;
	int g=L.length;
	do
	{
		if(L.elem[i]!=0)
		if(k==m)
			{
			cout<<L.elem[i]<<" ";
			L.elem[i]=0;
			k=1;
			g--;
		}
		else
			k++;
		i++;
		if(i>L.length)
			i=1	;		
	}while(g!=0);
}
int main()
{
	yuosefu L;
	Init_creat_list(L);
	Print_list(L);
	cout<<endl;
	int s,m;
	cout<<"The first people who begin and the number who outqueue:";
	cin>>s>>m;
	operation(L,s,m);
	
}

 
