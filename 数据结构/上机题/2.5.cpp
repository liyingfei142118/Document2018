#include<iostream>
using namespace std;
void print(int a[],int n);
int middle(int *a,int n)//实现在已经排序好的数组中插入数 
{
	int i,j; 
	for(i=1;i<n;i++)
	for(j=0;j<i;j++)
	{
		if(a[i]<a[j])
			{
				int t=a[i];//*在下面元素后移时以防元素值被改变 
				for(int k=i;k>j;k--)//
					a[k]=a[k-1];//在i 位置后的元素往后移 
				a[j]=t;
			}
	}
	print(a,n);
	int key=0;//标志是否找到此元素 
	for(i=1;i<n;i++)
		{
			//cout<<a[i]<<endl;
			int s1,s2;
			for(int k=(i-1);k>=0;k--) //从当前位置出发，从右往左 
			{
				if(a[k]<a[i])//找到一个数就可以确定小于当前数的总数 
				{
					s1=k+1;
					break;
					}	
				
			}
			for(int k1=(i+1);k1<n;k1++)  //从当前位置出发，从左往右 
			{
				if(a[k1]>a[i])//找到一个数就可以确定大于当前数的总数
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
				key=1;//不能直接返回，如果就会出现健壮性不会
				break; 
			}
	/*		int m=0,t=0;			
			for(int k=0;k<i;k++)//循环判断元素i前面的个数 
			{
				if(a[k]<a[i])
				m++;
			}
			int ss=i+1;
			for(;ss<n;ss++)//循环判断元素i后面的个数 
			{
				if(a[ss]>a[i])
				t++;
			}
			if(m==t&&m!=0)
			{
				cout<<"the number:"<<a[i]<<endl;
				key=1;//不能直接返回，如果就会出现健壮性不会
				break; 
			}*/
			
		}
		if(key==1)
			return 1;
		else 
			return 0;
}
void print(int a[],int n)//输出数组 
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
