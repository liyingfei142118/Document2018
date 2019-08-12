#include<iostream>
using namespace std;
#include<malloc.h>
#define max 100
typedef struct 
{
	int x1;
	int y1;
	int x2;
	int y2;
}Location;
typedef struct
{
	Location *elem;
	int div[max];
}Window;
void Init_window(Window &s)//创建顺序表 
{
	s.elem=(Location *)malloc(max*sizeof(Location));
	if(!s.elem)exit(0);
}
void Creat_window(Window &s,int n)//输入窗口的位置 
{
	int x1,y1,x2,y2,m=n;//m的作用是防止n值被改变 
	cout<<"please input x1,y1,x2,y2:"<<endl;
	for(int i=1;i<=n;i++)
	{
		cin>>x1>>y1>>x2>>y2;
		s.elem[i].x1=x1;
		s.elem[i].y1=y1;
		s.elem[i].x2=x2;
		s.elem[i].y2=y2;
		s.div[i]=m;
		m--;
	}
}
void Print_window(Window s,int  n)//打印窗口的位置 
{
	for(int i=1;i<=n;i++)
	{

		cout<<" x1:"<<s.elem[i].x1;
		cout<<" y1:"<<s.elem[i].y1;
		cout<<" x2:"<<s.elem[i].x2;
		cout<<" y2:"<<s.elem[i].y2;
		cout<<" div"<<"["<<i<<"]:"<<s.div[i]<<endl;
	}
}
void Chang_window(Window &s,int s1,int s2,int n)//改变窗口位置
{
	for(int t=1;t<=n;t++)
	{
		if(s.div[t]<s1)//比变为1的窗口小的++,其余不变 
			s.div[t]++;	
		if(t==s2)
			s.div[t]=1; 
	} 
}
void Click_window(Window &s,int n,int m)//点击窗口 
{
	int x,y;
	cout<<"click location x and y:"; 
	for(int i=1;i<=m;i++)
	{
		cin>>x>>y;
		int word=0;// 判断所有的窗口是否点击有效 
		cout<<"x:"<<x<<" y:"<<y<<endl;
		for(int s1=1;s1<=n;s1++)//s1为当前窗口,意思就是对点击从第一个窗口开始判断 
		{
			int key=0;//判断 从某一个窗口判断是否成立 
			for(int s2=1;s2<=n;s2++)//遍历顺序表 
			{
				if(s.div[s2]==s1&&(x>=s.elem[s2].x1 && y>=s.elem[s2].y1 && x<=s.elem[s2].x2 && y<=s.elem[s2].y2))//从第一个窗口开始遍历 
				{
					cout<<" div:";
				//	cout<<s.div[s2];// 输出窗口在当前窗口的第几层 
					cout<<s2;//输出窗口编号 
					cout<<endl;
					Chang_window(s,s1,s2,n);//窗口位置变为1和改变其余窗口位置 
					Print_window(s,n);
					cout<<endl;
					key=1;
					break;					
				}
			}
			if(key==1)
				{
					word=1;
					break;
				}		
		}
		if(word==0)
		cout<<"IGNORED!"<<endl;
	}
	
}
int main()
{
	Window s;
	Init_window(s);//创建顺序表 
	
	int n,m;//n个窗口m个点击 
	cout<<"please input n and m:";
	cin>>n>>m;
	cout<<endl;
	Creat_window(s,n);//输入窗口的位置
	Print_window(s,n);//打印窗口的位置 

	Click_window(s,n,m);//点击窗口
	return 0;
}

