#include<iostream>
using namespace std;
#include<malloc.h>
#define seat 100

typedef struct 
{
	int *data;
	int length;
}Seat;

void Init_Seat(Seat &s)//����˳��� 
{
	s.data=(int *)malloc(seat*sizeof(int));
	if(!s.data)exit(0);
	s.length=100;
}

void Fu_Seat(Seat &s)//��ʼ�� 
{
	if(s.length==0)exit(0);
	for(int i=1;i<=100;i++)
	{
		s.data[i]=1;
	}
}
void Print_Seat(Seat s)//��ӡ˳��� 
{
	if(s.length==0)exit(0);
	for(int i=1;i<=s.length;i++)
	{
		cout<<" "<<s.data[i];
		if(i%5==0)
			cout<<endl;
	}
}
void Gou_Seat(Seat &s)//��Ʊ���� 
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
			case 1://��1��Ʊ
				{
					for(int ss=1;ss<=s.length;ss++)//��ͷ��ʼ����  
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
			case 2://��2��Ʊ
				{
					int word=0;
					for(int ss=1;ss<=s.length;ss++)
					{
						if(ss%5!=0)//����ǹ�2��Ʊ�Ͳ��ܴ�5�ı�����ʼ�� 
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
					if(word==1)//word�Ǳ�־�Ƿ��������Ʊ 
							break;
					else//������ 
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
			
			case 3://��3��Ʊ
				{
					int word=0;
					for(int ss=1;ss<=s.length;ss++)
					{			
						if((ss%5<=3)&&(ss%5!=0))//����ǹ�3��Ʊ�Ͳ��ܴ�5�ı�����ʼ�� 
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
					if(word==1)//word�Ǳ�־�Ƿ��������Ʊ 
							break;
					else//������ 
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
			case 4://��4��Ʊ
				{
					int word=0;
					for(int ss=1;ss<=s.length;ss++)
					{			
						if((ss%5<=2)&&(ss%5!=0))//����ǹ�4��Ʊ�Ͳ��ܴ�5�ı�����ʼ�� 
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
					if(word==1)//word�Ǳ�־�Ƿ��������Ʊ 
							break;
					else//������ 
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
			case 5://��5��Ʊ
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
					if(word==1)//word�Ǳ�־�Ƿ��������Ʊ 
							break;
					else//������ 
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



