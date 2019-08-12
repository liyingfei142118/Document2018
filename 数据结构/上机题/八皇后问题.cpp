#include<iostream>
using namespace std;
#include<malloc.h>

#define max 100
#define add 10
 
 typedef struct
 {
 	int i;
 	int j;
 }Position;
 typedef struct
 {
 	Position *base;
 	Position *top;
 	int stacksize;
 }Sqstack;
 void Init_stack(Sqstack &L)
 {
 	L.base=(Position *)malloc(max*sizeof(Position));
 	if(!L.base)exit(0);
 	L.top=L.base;
 	L.stacksize=max;
 }
 void Push(Sqstack &L,int x,int y)
 {
 
	 	if((L.top-L.base)>=L.stacksize)
	 	{
	 		L.base=(Position *)realloc(L.base,(L.stacksize +add)*sizeof(Position));
	 		if(!L.base)exit(0);
	 		L.top=L.base+L.stacksize;
	 		L.stacksize+=add;
		 }
		 L.top->i=x;
		 L.top->j=y;
		 L.top++;

 }
 void Pop(Sqstack &L)
 {
 	if(L.base==L.top)exit(0);
 	L.top--;
 }
 void Print_stack(Sqstack L)
 {
 	if(L.base==L.top)throw("empty");
 	while(L.base<L.top)
 	{
 		cout<<"i:"<<L.base->i<<" j:"<<L.base->j<<endl;
 		L.base++;
	 } 	
 }
  int Getstacki(Sqstack L)
 {
	 if(L.base==L.top)exit(0);
	 L.top--;
	 return L.top->i;
 }
 int Getstackj(Sqstack L)
 {
	 if(L.base==L.top)exit(0);
	 L.top--;
	 return L.top->j;
 }
 bool Solution(Sqstack L,int x,int y)
 {
 	int m=L.top-L.base,word=0;
 	for(int k=0;k<m;k++)
 	{
 		if((L.base->i==x)||(L.base->j==y)||(x-L.base->i==-(y-L.base->j))||(x-L.base->i==(y-L.base->j)))
 			{
			 word=1;
			 break;
			}
			L.base++;
	 }
	 if(word==1)
	 	return 1;
	 else 
	 	return 0;
 }
 void ClearStack(Sqstack &L)//清空栈 
{
	free(L.base);
	L.top=L.base=NULL;
}
 int main()
 {

	int a[8][8];
	Sqstack L;
	Init_stack(L);
 /*	for(int k=0;k<8;k++)
		{	*/
	for(int i=0;i<8;i++)
	for(int j=0;j<8;j++)
	{
		a[i][j]=0;
	 }
	int s1=0,s2=0,Word=0;//s1行坐标s2列坐标
	while(s1<8)
	{
	//int key=0;//判断一行是否有可放置位	
	while(s2<8)
		{
		if(s1==0&&s2==0)//如果是0，0直接放入栈，并且行坐标加1和此位置为令为1
			{
				//Word++;
				a[s1][s2]=1;//此位置为令为1
				Push(L,s1,s2);//存入栈
				s1++;//行坐标加1
				break;//执行下一个循环
			}
		if(!Solution(L,s1,s2))//如果可以，存入栈。此位置为令为1
				 		{
				 			Push(L,s1,s2);//存入栈
				 			//Word++;
				 			a[s1][s2]=1;//此位置为令为1
							s1++;//行加1
							s2=0;//列变为0
						//	key=1;//此处可放
								Print_stack(L);
				for(int m=0;m<8;m++)
				for(int j=0;j<8;j++)
				{
					cout<<a[m][j]<<"    ";
					if(j==7)
						cout<<endl;
					
				}
				cout<<endl;
				 			break;
						 }
			else if(Solution(L,s1,s2)==1&&s2==7)//如果是最后一个位置，并且不可以放
			{
				
				if(Getstackj(L)<7)
				{	
					s1=Getstacki(L);//行-1
					cout<<"s1:"<<s1<<endl;
					s2=Getstackj(L)+1;//列变为原来上一行的加1
					a[Getstacki(L)][Getstackj(L)]=0;//上一行的位置变为0
					Pop(L);//删除上一行
				}
				else
				{
					s1=Getstacki(L)-1;//行-1
					a[Getstacki(L)][Getstackj(L)]=0;//上一行的位置变为0
					Pop(L);//删除上一行
					a[Getstacki(L)][Getstackj(L)]=0;
					s2=Getstackj(L)+1;//列变为原来上一行的加1
					Pop(L);//删除上一行
				}
			}
			else
				s2++;
			
		}	
	}
		/*	int Word=1;
			a[0][k]=1;
			Sqstack L;
			Init_stack(L); 			 		
			Push(L,0,k);
			cout<<endl;
				 	for(int i1=1;i1<8;i1++)
				 	for(int j=0;j<8;j++)
				 	{
				 		if(!Solution(L,i1,j))
				 		{
				 			Push(L,i1,j);
				 			Word++;
				 			a[i1][j]=1;
				 			break;
						 }
					}
			cout<<"word:"<<Word<<endl;
					for(int i2=0;i2<8;i2++)
				for(int j=0;j<8;j++)
				{
					cout<<a[i2][j]<<"    ";
					if(j==7)
						cout<<endl;
					
				}
				cout<<endl;
			if(Word==8)
			{
			Print_stack(L);
				for(int i=0;i<8;i++)
				for(int j=0;j<8;j++)
				{
					cout<<a[i][j]<<"    ";
					if(j==7)
						cout<<endl;
					
				}
				cout<<endl;
				break;
			}		
			else
			{
				ClearStack(L);
			}
		}*/
	Print_stack(L);
				for(int m=0;m<8;m++)
				for(int j=0;j<8;j++)
				{
					cout<<a[m
						][j]<<"    ";
					if(j==7)
						cout<<endl;
					
				}
				cout<<endl;
	return 0;
 }
