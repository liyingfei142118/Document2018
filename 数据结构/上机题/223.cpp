#include<iostream>
using namespace std;
#include<malloc.h>
void print(int a[10][10])
{
	for(int i=0;i<10;i++)
	for(int j=0;j<10;j++)
	{
		cout<<a[i][j]<<"    ";
		if(j==9)
			cout<<endl;
		
	}	

	cout<<endl;
}
int  Find(int a[10][10],int i,int j,int &k,int &flag)
{
	if(flag)return 0;
	a[i][j]=k;
	print(a);
	k++;
	if(i==8&&j==8)
	{
		flag=1;
		return 1;
	}
		
	else
	{
		if(a[i-1][j]==1)//ио 
			{			
				Find(a,i-1,j,k,flag);			
			}
		 if(a[i][j+1])//ср 
			{
				
				Find(a,i,j+1,k,flag);
					
			}
		 if(a[i+1][j]==1)//об 
			{
				
				Find(a,i+1,j,k,flag);	
			}
		 if(a[i][j-1]==1)//вС 
		 {
		 		Find(a,i,j-1,k,flag);
		 }
	}
		
	
}
void Solution3()
{
	int a[10][10];
	int k=2;
	for(int i=0;i<10;i++)
	for(int j=0;j<10;j++)
	{
		if(i==0||i==9||j==0||j==9)
			a[i][j]=0;
		else if(j==1&&i==8)
			a[i][j]=0;
		else if(j==2&&(i==4||i==6||i==7))
			a[i][j]=0;
		else if(j==3&&(i==1||i==2||i==4||i==7))
			a[i][j]=0;
		else if(j==4&&(i==4||i==5||i==7))
			a[i][j]=0;
		else if(j==5&&i==3)
			a[i][j]=0;
		else if(j==6&&(i==3||i==6||i==7))
			a[i][j]=0;
		else if(j==7&&(i==1||i==2||i==7))
			a[i][j]=0;
		else
			a[i][j]=1;
	}
	print(a);
	int s=2,flag=0;
	cout<<Find(a,1,1,s,flag)<<endl;
}
int main()
{
	Solution3();
}
