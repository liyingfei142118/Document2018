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
	cout<<"the sum of the people:";//��ʼ��˳��� 
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
	for(i=0; i<L.length; i++)
	{
		if(i%5==0)
		cout<<endl;
		cout<<L.elem[i]<<" ";
	}
}
void Combine_array(Sqlist &L,Sqlist L1)//�ϲ�����˳��� 
{
	int t=L.length+L1.length;
	if(t>max) //�ж�˳���ĳ��� 
		{
		Sqlist Q;
		Q.elem=(int *)realloc(L.elem,(max+(t-max))*sizeof(int));
		if(!Q.elem)throw("error1");
		L.elem=Q.elem;
		}
	for(int i=0;i<L1.length;i++)
	for(int j=0;j<L.length;j++)
	{
		if(L1.elem[i]==L.elem[j])//�����ȣ��Ͳ����� 
			break;
		if(L1.elem[i]<L.elem[j])
		{
			for(int k=L.length;k>j;k--)//�������в��� 
					L.elem[k]=L.elem[k-1];//jλ�ú����Ԫ��ȫ������ 
			L.elem[j]=L1.elem[i];//��jλ�ò��� 
			L.length++;// L��Ԫ�ؼ�1 
			break;
		}
		if(j==(L.length-1)&&L1.elem[i]>L.elem[j])//���������� 
		{
			L.elem[L.length]=L1.elem[i];
			L.length++;
			break;
		}
	}
			
}
int main()
{
	Sqlist L,L1;//����2��˳��� 
	Init_creat_list(L);//������һ��˳��� 
	Print_list(L);//��ӡ˳��� 
	cout<<endl; 
	Init_creat_list(L1);//�����ڶ���˳��� 
	Print_list(L1);//��ӡ˳���
	cout<<endl;
	Combine_array(L,L1);
	Print_list(L);
	return 0;
} 
