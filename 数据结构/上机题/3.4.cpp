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
void Init_window(Window &s)//����˳��� 
{
	s.elem=(Location *)malloc(max*sizeof(Location));
	if(!s.elem)exit(0);
}
void Creat_window(Window &s,int n)//���봰�ڵ�λ�� 
{
	int x1,y1,x2,y2,m=n;//m�������Ƿ�ֹnֵ���ı� 
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
void Print_window(Window s,int  n)//��ӡ���ڵ�λ�� 
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
void Chang_window(Window &s,int s1,int s2,int n)//�ı䴰��λ��
{
	for(int t=1;t<=n;t++)
	{
		if(s.div[t]<s1)//�ȱ�Ϊ1�Ĵ���С��++,���಻�� 
			s.div[t]++;	
		if(t==s2)
			s.div[t]=1; 
	} 
}
void Click_window(Window &s,int n,int m)//������� 
{
	int x,y;
	cout<<"click location x and y:"; 
	for(int i=1;i<=m;i++)
	{
		cin>>x>>y;
		int word=0;// �ж����еĴ����Ƿ�����Ч 
		cout<<"x:"<<x<<" y:"<<y<<endl;
		for(int s1=1;s1<=n;s1++)//s1Ϊ��ǰ����,��˼���ǶԵ���ӵ�һ�����ڿ�ʼ�ж� 
		{
			int key=0;//�ж� ��ĳһ�������ж��Ƿ���� 
			for(int s2=1;s2<=n;s2++)//����˳��� 
			{
				if(s.div[s2]==s1&&(x>=s.elem[s2].x1 && y>=s.elem[s2].y1 && x<=s.elem[s2].x2 && y<=s.elem[s2].y2))//�ӵ�һ�����ڿ�ʼ���� 
				{
					cout<<" div:";
				//	cout<<s.div[s2];// ��������ڵ�ǰ���ڵĵڼ��� 
					cout<<s2;//������ڱ�� 
					cout<<endl;
					Chang_window(s,s1,s2,n);//����λ�ñ�Ϊ1�͸ı����ര��λ�� 
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
	Init_window(s);//����˳��� 
	
	int n,m;//n������m����� 
	cout<<"please input n and m:";
	cin>>n>>m;
	cout<<endl;
	Creat_window(s,n);//���봰�ڵ�λ��
	Print_window(s,n);//��ӡ���ڵ�λ�� 

	Click_window(s,n,m);//�������
	return 0;
}

