#include<iostream>
using namespace std;
void print(int a[],int n);
int middle(int *a,int n)//ʵ�����Ѿ�����õ������в����� 
{
	int i,j; 
	for(i=1;i<n;i++)
	for(j=0;j<i;j++)
	{
		if(a[i]<a[j])
			{
				int t=a[i];//*������Ԫ�غ���ʱ�Է�Ԫ��ֵ���ı� 
				for(int k=i;k>j;k--)//
					a[k]=a[k-1];//��i λ�ú��Ԫ�������� 
				a[j]=t;
			}
	}
	print(a,n);
	int key=0;//��־�Ƿ��ҵ���Ԫ�� 
	for(i=1;i<n;i++)
		{
			//cout<<a[i]<<endl;
			int s1,s2;
			for(int k=(i-1);k>=0;k--) //�ӵ�ǰλ�ó������������� 
			{
				if(a[k]<a[i])//�ҵ�һ�����Ϳ���ȷ��С�ڵ�ǰ�������� 
				{
					s1=k+1;
					break;
					}	
				
			}
			for(int k1=(i+1);k1<n;k1++)  //�ӵ�ǰλ�ó������������� 
			{
				if(a[k1]>a[i])//�ҵ�һ�����Ϳ���ȷ�����ڵ�ǰ��������
				{
					s2=n-k1;
					break;
				}
			}
			//cout<<s1<<" "<<s2<<endl;
			if(s1==s2&&s1!=0)
			{
				cout<<endl;
				cout<<"the number:"<<a[i]<<endl;
				key=1;//����ֱ�ӷ��أ�����ͻ���ֽ�׳�Բ���
				break; 
			}
	/*		int m=0,t=0;			
			for(int k=0;k<i;k++)//ѭ���ж�Ԫ��iǰ��ĸ��� 
			{
				if(a[k]<a[i])
				m++;
			}
			int ss=i+1;
			for(;ss<n;ss++)//ѭ���ж�Ԫ��i����ĸ��� 
			{
				if(a[ss]>a[i])
				t++;
			}
			if(m==t&&m!=0)
			{
				cout<<"the number:"<<a[i]<<endl;
				key=1;//����ֱ�ӷ��أ�����ͻ���ֽ�׳�Բ���
				break; 
			}*/
			
		}
		if(key==1)
			return 1;
		else 
			return 0;
}
void print(int a[],int n)//������� 
{
	for(int i=0;i<n;i++)
	{
		if(i%5==0)
		cout<<endl;
		cout<<a[i]<<" ";
	}
		
}
 int main()
 {
 	int n,a[1000];
 	cout<<"Please input n number:";
 	cin>>n;
 	for(int i=0;i<n;i++)
 		cin>>a[i];
 	cout<<endl;
 	cout<<"the middle number:"<<middle(a,n)<<endl;
 	return 0;
 }
