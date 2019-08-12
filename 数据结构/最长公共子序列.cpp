#include<iostream>
using namespace std;
#include<string.h>
#define max 100

int Mx(int x,int y)
{
	if(x>=y)
	return x;
	else
	return y;
}
 void LCS(char str1[max],char str2[max],int L[max][max],int m,int n)
 {
 	int i,j;
	for(i=0;i<m;i++)
	{
		L[i][0]=0;
	}
	for(j=0;j<m;j++)
	{
		L[0][j]=0;
	}
		for(i=1;i<=m;i++)
			for(j=1;j<=n;j++)
			{
				if(str1[i]==str2[j])
					L[i][j]=L[i-1][j-1]+1;
				else
					L[i][j]=Mx(L[i-1][j],L[i][j-1]);
			}
	cout<<L[m][n];
 }
int main()
{

   int i;
   char str1[max],str2[max];
   int L[max][max];
	int m,n;
	cout<<"please input str1:"<<endl;
	cin>>str1;
	m=strlen(str1);
for(i=m;i>0;i--)
{
	str1[i]=str1[i-1];
}
	cout<<"please input str2:"<<endl;
	cin>>str2;
	n=strlen(str2);
for(i=n;i>0;i--)
{
	str2[i]=str2[i-1];
}
	LCS(str1,str2,L,m,n);
}
