//输入稀疏矩阵，建立稀疏矩阵三元组顺序结构，实现转置（1、2）；
#include<iostream>
using namespace std;
#include<malloc.h>

#define max 100

typedef struct
{
	int i,j;//下标 
	int e;
}Tripe;
 typedef struct 
 {
 	Tripe *data;
 	Tripe *data1;
 	int mu,nu,tu;//mu 行数 nu列数 tu非零元个数 
 }Ts;
 
 void Init_Ts(Ts &s)//构建矩阵 
 {
	s.data1=s.data=(Tripe *)malloc(max*sizeof(Tripe));
	if(!s.data)exit(0);
	cout<<"please input 行数 and 列数 and 非零元个数:";
	cin>>s.mu>>s.nu>>s.tu;
	cout<<endl;	
 }
 void Fu_Ts(Ts &s)//赋值矩阵 
 {
 	cout<<"please input 所有非零元的行数和列数及值:";
 	for(int i=0;i<s.tu;i++)
 	{
 		cin>>s.data->i>>s.data->j>>s.data->e;
		s.data++; 
	 }
 	
 }
 void Print_Ts(Ts s)//打印矩阵
 {
 /*for(int i=0;i<s.tu;i++)
 	{
 		cout<<s.data1->i<<" "<<s.data1->j<<" "<<s.data1->e<<endl;
		s.data1++; 
	 }*/
	Ts Q;
	 for(int s0=0;s0<s.mu;s0++)
	 {
 		for(int s1=0;s1<s.nu;s1++)
 		{
 			int word=0;//标志此位置是否有这个值 
 				Q.data1=s.data1;//防止位置改变 
	 			for(int s2=0;s2<s.tu;s2++)//遍历顺序表 
	 				{ 
					 	if(s0==Q.data1[s2].i&&s1==Q.data1[s2].j)//如果存在 
	 						{
	 							cout<<" "<<Q.data1[s2].e;//输出对应的值 
	 							word=1;
	 							break;//结束循环 
							 }
				 	}
			 if(word==0)//如果这个位置没有这个值，输出0 
			 {
			 	cout<<" 0";
			 }
 				
		 }
		 cout<<endl;//每一列后换行 
	}
  } 
 void Trans1_Ts(Ts &s)//先转置后排序 
{
	Ts Q;
	Q.data1=s.data1;	
	for(int i=0;i<s.tu;i++)//转置
 		{
 			int t=Q.data1->i;
 			Q.data1->i=Q.data1->j;
			Q.data1->j=t;
			Q.data1++; 
		 }
		 
	Q.data1=s.data1;
	for(int i1=1;i1<s.tu;i1++)//排序
		for(int j1=0;j1<s.tu-i1;j1++)
 		{
 			if(Q.data1[j1].i >Q.data1[j1+1].i)
 			{
 				int t=Q.data1[j1].i,t1=Q.data1[j1].j,m=Q.data1[j1].e;
 				Q.data1[j1].i=Q.data1[j1+1].i;
 				Q.data1[j1].j=Q.data1[j1+1].j;
 				Q.data1[j1].e=Q.data1[j1+1].e;
 				Q.data1[j1+1].i=t;
 				Q.data1[j1+1].j=t1;
 				Q.data1[j1+1].e=m;
			 }
		 }
  }
 void Trans2_Ts(Ts &s)//先排序后转置 
{
	Ts Q;
	Q.data1=s.data1;
	for(int i1=1;i1<s.tu;i1++)
		for(int j1=0;j1<s.tu-i1;j1++)
 		{
 			if(Q.data1[j1].j >Q.data1[j1+1].j)
 			{
 				int t=Q.data1[j1].i,t1=Q.data1[j1].j,m=Q.data1[j1].e;
 				Q.data1[j1].i=Q.data1[j1+1].i;
 				Q.data1[j1].j=Q.data1[j1+1].j;
 				Q.data1[j1].e=Q.data1[j1+1].e;
 				Q.data1[j1+1].i=t;
 				Q.data1[j1+1].j=t1;
 				Q.data1[j1+1].e=m;
			 }
		 }
	Q.data1=s.data1;	
	for(int i=0;i<s.tu;i++)
 		{
 			int t=Q.data1->i;
 			Q.data1->i=Q.data1->j;
			Q.data1->j=t;
			Q.data1++; 
		 }
		 
	
	
  }
void Trans3_Ts(Ts &s)
{
	Ts Q,Q1;
	Init_Ts(Q1);
	Q.data1=s.data1;
	int num[s.nu],cpot[s.nu];
/*	for(int col=0;col<s.nu;col++)
		num[col]=0;
	for(int k=0;k<s.tu;k++)//遍历顺序表 
	 	++num[Q.data1[k].j];*/
 for(int col=0;col<s.nu;col++)//遍历每一列 
		 	{
			 	num[col]=0;//初始都为0
 				for(int k=0;k<s.tu;k++)//遍历顺序表 
 				{
 				
 					if(col==Q.data1[k].j)//如果出现，加1 
 						num[col]++;
			 	}
			}
	cpot[0]=0;//确定每一列第一个非零元素 
	for(int col=1;col<s.nu;col++)
	{
		cpot[col]=cpot[cnol-1]+num[col-1];
	}	
	

	Print_Ts(s);
	for(int p=0;p<s.tu;p++)
	{
		int col=s.data1[p].j;//出现列 
		int q=cpot[col];////确定此列第一个非零元素
		cout<<endl;
		//cout<<s.data1[p].j<<endl;
		Q1.data1[q].i=s.data1[p].j;
		Q1.data1[q].j=s.data1[p].i;
		Q1.data1[q].e=s.data1[p].e;
		++cpot[col];
	}
	s.data1=Q1.data1;
	
	int ss=s.mu;
	s.mu=s.nu;
	s.nu=ss;//行列互换 
}
 int main()
 {
 	Ts s;
 	Init_Ts(s);//构建 
 	Fu_Ts(s);//赋值 
 	Print_Ts(s);//打印 
 	
 //	cout<<endl;
 //	Trans1_Ts(s);//先转置后排序
 //	Print_Ts(s);
 
 //	Trans2_Ts(s);//先排序后转置
 //	Print_Ts(s);
 
 	Trans3_Ts(s);//快速转置
 	Print_Ts(s);
	 return 0;
 }
