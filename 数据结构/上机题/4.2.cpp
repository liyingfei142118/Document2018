#include<iostream>
using namespace std;
#include<malloc.h>
#define seat 100

typedef struct 
{
	int *data;
	int length;
}Seat;

void Init_Seat(Seat &s)//构建顺序表 
{
	s.data=(int *)malloc(seat*sizeof(int));
	if(!s.data)exit(0);
	s.length=100;
}

void Fu_Seat(Seat &s)//初始化 
{
	if(s.length==0)exit(0);
	for(int i=1;i<=100;i++)
	{
		s.data[i]=1;
	}
}
void Print_Seat(Seat s)//打印顺序表 
{
	if(s.length==0)exit(0);
	for(int i=1;i<=s.length;i++)
	{
		cout<<" "<<s.data[i];
		if(i%5==0)
			cout<<endl;
	}
}
void Gou_Seat(Seat &s)//购票操作 
{
	int n;
	cout<<"please input the number of n:";
	cin>>n;
	cout<<endl;
	for(int i=1;i<=n;i++)
	{
		int k;
		cout<<i<<":";
		cin>>k;
		switch(k)
		{
			case 1://购1张票
				{
					for(int ss=1;ss<=s.length;ss++)//从头开始遍历  
					{
						if(s.data[ss]==1)
						{
							cout<<ss<<endl;
							s.data[ss]=0;
							//	Print_Seat(s);
							break;
						}
					}
					break;	
				}
			case 2://购2张票
				{
					int word=0;
					for(int ss=1;ss<=s.length;ss++)
					{
						if(ss%5!=0)//如果是购2张票就不能从5的倍数开始找 
						{
							if(s.data[ss]==1&&s.data[ss+1]==1)
							{
							cout<<ss<<" "<<ss+1<<endl;
							s.data[ss]=s.data[ss+1]=0;
							word=1;
							break;
							}
						}						
					}
					if(word==1)//word是标志是否存在相邻票 
							break;
					else//不存在 
							{
								for(int ss=1;ss<=s.length;ss++)
								{
									int k=0;
									if(k==2)						
										break;
									if(s.data[ss]!=0)
									{
										cout<<" "<<ss;
										s.data[ss]=0;
										k++;
									}
									
								}
								break;
							}				
				}
			
			case 3://购3张票
				{
					int word=0;
					for(int ss=1;ss<=s.length;ss++)
					{			
						if((ss%5<=3)&&(ss%5!=0))//如果是购3张票就不能从5的倍数开始找 
						{
							if(s.data[ss]==1&&s.data[ss+1]==1&&s.data[ss+2]==1)
							{
								cout<<" "<<ss<<" "<<ss+1<<" "<<ss+2<<endl;
								s.data[ss]=s.data[ss+1]=s.data[ss+2]=0;
								word=1;
							//	Print_Seat(s);
								break;
							}
						}
					}
					if(word==1)//word是标志是否存在相邻票 
							break;
					else//不存在 
							{
								for(int ss=1;ss<=s.length;ss++)
								{
									int k=0;
									if(k==3)
										break;
									if(s.data[ss]!=0)
									{
										cout<<" "<<ss;
										s.data[ss]=0;
										k++;
									}		
								}
								break;
							}										

				}						
			case 4://购4张票
				{
					int word=0;
					for(int ss=1;ss<=s.length;ss++)
					{			
						if((ss%5<=2)&&(ss%5!=0))//如果是购4张票就不能从5的倍数开始找 
						{
							if(s.data[ss]==1&&s.data[ss+1]==1&&s.data[ss+2]==1&&s.data[ss+3]==1)
							{
								cout<<" "<<ss<<" "<<ss+1<<" "<<ss+2<<" "<<ss+3<<endl;
								s.data[ss]=s.data[ss+1]=s.data[ss+2]=s.data[ss+3]=0;
								word=1;
							//	Print_Seat(s);
								break;
							}
						}
					}
					if(word==1)//word是标志是否存在相邻票 
							break;
					else//不存在 
							{
								for(int ss=1;ss<=s.length;ss++)
								{
									int k=0;
									if(k==4)
										break;
									if(s.data[ss]!=0)
									{
										cout<<" "<<ss;
										s.data[ss]=0;
										k++;
									}		
								}
								break;
							}										

				}
			case 5://购5张票
				{
					int word=0;
					for(int ss=1;ss<=s.length;ss++)
					{			
						if(ss%5==1) 
						{
							if(s.data[ss]==1&&s.data[ss+1]==1&&s.data[ss+2]==1&&s.data[ss+3]==1&&s.data[ss+4]==1)
							{
								cout<<" "<<ss<<" "<<ss+1<<" "<<ss+2<<" "<<ss+3<<" "<<ss+4<<endl;
								s.data[ss]=s.data[ss+1]=s.data[ss+2]=s.data[ss+3]=s.data[ss+4]=0;
								word=1;
							//	Print_Seat(s);
								break;
							}
						}
					}
					if(word==1)//word是标志是否存在相邻票 
							break;
					else//不存在 
							{
								for(int ss=1;ss<=s.length;ss++)
								{
									int k=0;
									if(k==5)
										break;
									if(s.data[ss]!=0)
									{
										cout<<" "<<ss;
										s.data[ss]=0;
										k++;
									}		
								}
								break;
							}										

				}
		}
		cout<<endl;
	}
	 
	
}
int main()
{
	Seat s;
	Init_Seat(s);
	Fu_Seat(s);
	Print_Seat(s);
	
	Gou_Seat(s);
	return 0;
}



