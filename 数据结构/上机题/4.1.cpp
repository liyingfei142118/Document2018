//����ϡ����󣬽���ϡ�������Ԫ��˳��ṹ��ʵ��ת�ã�1��2����
#include<iostream>
using namespace std;
#include<malloc.h>

#define max 100

typedef struct
{
	int i,j;//�±� 
	int e;
}Tripe;
 typedef struct 
 {
 	Tripe *data;
 	Tripe *data1;
 	int mu,nu,tu;//mu ���� nu���� tu����Ԫ���� 
 }Ts;
 
 void Init_Ts(Ts &s)//�������� 
 {
	s.data1=s.data=(Tripe *)malloc(max*sizeof(Tripe));
	if(!s.data)exit(0);
	cout<<"please input ���� and ���� and ����Ԫ����:";
	cin>>s.mu>>s.nu>>s.tu;
	cout<<endl;	
 }
 void Fu_Ts(Ts &s)//��ֵ���� 
 {
 	cout<<"please input ���з���Ԫ��������������ֵ:";
 	for(int i=0;i<s.tu;i++)
 	{
 		cin>>s.data->i>>s.data->j>>s.data->e;
		s.data++; 
	 }
 	
 }
 void Print_Ts(Ts s)//��ӡ����
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
 			int word=0;//��־��λ���Ƿ������ֵ 
 				Q.data1=s.data1;//��ֹλ�øı� 
	 			for(int s2=0;s2<s.tu;s2++)//����˳��� 
	 				{ 
					 	if(s0==Q.data1[s2].i&&s1==Q.data1[s2].j)//������� 
	 						{
	 							cout<<" "<<Q.data1[s2].e;//�����Ӧ��ֵ 
	 							word=1;
	 							break;//����ѭ�� 
							 }
				 	}
			 if(word==0)//������λ��û�����ֵ�����0 
			 {
			 	cout<<" 0";
			 }
 				
		 }
		 cout<<endl;//ÿһ�к��� 
	}
  } 
 void Trans1_Ts(Ts &s)//��ת�ú����� 
{
	Ts Q;
	Q.data1=s.data1;	
	for(int i=0;i<s.tu;i++)//ת��
 		{
 			int t=Q.data1->i;
 			Q.data1->i=Q.data1->j;
			Q.data1->j=t;
			Q.data1++; 
		 }
		 
	Q.data1=s.data1;
	for(int i1=1;i1<s.tu;i1++)//����
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
 void Trans2_Ts(Ts &s)//�������ת�� 
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
	for(int k=0;k<s.tu;k++)//����˳��� 
	 	++num[Q.data1[k].j];*/
 for(int col=0;col<s.nu;col++)//����ÿһ�� 
		 	{
			 	num[col]=0;//��ʼ��Ϊ0
 				for(int k=0;k<s.tu;k++)//����˳��� 
 				{
 				
 					if(col==Q.data1[k].j)//������֣���1 
 						num[col]++;
			 	}
			}
	cpot[0]=0;//ȷ��ÿһ�е�һ������Ԫ�� 
	for(int col=1;col<s.nu;col++)
	{
		cpot[col]=cpot[cnol-1]+num[col-1];
	}	
	

	Print_Ts(s);
	for(int p=0;p<s.tu;p++)
	{
		int col=s.data1[p].j;//������ 
		int q=cpot[col];////ȷ�����е�һ������Ԫ��
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
	s.nu=ss;//���л��� 
}
 int main()
 {
 	Ts s;
 	Init_Ts(s);//���� 
 	Fu_Ts(s);//��ֵ 
 	Print_Ts(s);//��ӡ 
 	
 //	cout<<endl;
 //	Trans1_Ts(s);//��ת�ú�����
 //	Print_Ts(s);
 
 //	Trans2_Ts(s);//�������ת��
 //	Print_Ts(s);
 
 	Trans3_Ts(s);//����ת��
 	Print_Ts(s);
	 return 0;
 }
