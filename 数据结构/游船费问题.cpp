#include<iostream>
using namespace std;
#define max 100
int n,r[max][max],m[max][max];

void search(int rr[max][max],int mm[max][max],int nn)
{
	int i,j,k,t,temp;
		mm[nn][nn]=0;
		for(i=0;i<nn;i++)
			{
			for(j=i+1;j<=nn;j++)
				{
					
					mm[i][j]=r[i][j];
				}
				mm[i][i]=0;
			}
		for(t=2;t<=nn;t++)//间隔数 
		{
			for(i=0;i<=nn-t;i++)//起始点	
			{
				j=t+i;
				temp=mm[i][j];//t+i(j)终点 
				for(k=i+1;k<j;k++)//遍历中间的点 
				{
					if(temp>mm[i][k]+mm[k][j])
						temp=mm[i][k]+mm[k][j];
				}
				mm[i][j]=temp;
			}
		}
			
 } 
int main()
{
	int i,j,num=0,a;
	while(cin>>n)
	{
		if(n==0)break;
		else
		{
			num++;
			for(i=0;i<n;i++)
			{
				for(j=i+1;j<=n;j++)
				{
					cin>>a;
					r[i][j]=a;
				}
			}
			search(r,m,n);
			cout<<"Case:"<<num<<":"<<endl;
			cout<<m[0][n]<<endl;
		}
	}
	return 0;
 } 
