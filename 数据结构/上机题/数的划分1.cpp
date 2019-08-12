#include<iostream>
using namespace std;
int a[100];
int total;
int k=0;
void sort(int n)
{
	int i;
	for(i=n-1;i>0;i--)
	{	
		a[k]=i;
		k++;
		int t=n-i;
		if(i>=t&&k<6)
		{
			a[k]=t;
			for(i=0;i<=k;i++)
				{
					cout<<a[i]<<"+";
				}
				k=0;
				cout<<endl;
		}
		if(i<=t&&k<6)
		{		
		sort(n-i);
		k--;
		}
	}
}
int main()
{
	int n;
	cout<<"n:";
	cin>>n;
	cout<<endl;
	sort(n);
 } 
