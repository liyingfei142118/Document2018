#include<iostream>
using namespace std;
#include<malloc.h>
#include<ctime>
#include<cstdlib>
#include<fstream>
#include<string>


#define max 20001
#define min 10

typedef struct
{
	int *elem;
	int length;
	int listsize;
}SqList;

struct QNode
{
	int data;
	QNode *next;
};

typedef struct LinkQueue
{
	QNode *front;
	QNode *rear;
}*Link_Queue;

bool InitQueue(Link_Queue &Q);
void DestroyQueue(Link_Queue Q);
void RadixSort(int *L,int l_len);//�������� 
void Distribute(QNode *Node_head,LinkQueue *Queue,int i);//���� 
void Collection(QNode *Node_head,LinkQueue *Queue); //�ռ� 
int Get_key(QNode *p,int i);//�õ�λֵ 
void Traverse(int *L,int l_len);
void Init_sq(SqList &L);
void Creat_sq(SqList &L,int n);//��˳����ʼ��
void Traverse_sq(SqList L);//��������Ԫ��
void InsertSort(SqList &L);//�򵥲�������
void ShellInsert(SqList &L,int dk);//ϣ������ 
void ShellSort(SqList &L,int dlta[],int t);//ϣ������
void BubbleSort(SqList &L);//ð������ 
int Partion(SqList &L,int low,int high);//ȷ��L.elem[i]Ԫ�ص�λ�� 
void QSort(SqList &L,int low,int high);//�������� 
void SelectSort(SqList &L);//��ѡ������
void HeapAdjust(SqList &L,int s,int m);//�󶥶� 
void HeadSort(SqList &L);//������ 
void Merge(SqList S,SqList &T,int s,int m,int t);//�鲢 
void MergePass(SqList &S,SqList T,int n,int h);//һ�ι鲢������
void MergeSort(SqList &S,SqList T,int n); //�鲢����
void fuzhi_wen(SqList &L);//���ļ��е��ļ����ݴ���˳��� 
void creat_wen();//�����ļ� 
void creat1_wen();//�����ļ� 
void creat1_wen();//�����ļ� 
  
void Init_sq(SqList &L)
{
	L.elem=(int *)malloc(max*sizeof(int));
	if(!L.elem)exit(0);
	L.length=0;
	L.listsize=max;
}

void Creat_sq(SqList &L,int n)//��˳����ʼ�� 
{
	
	if(n>max)exit(0);
	for(int i=1;i<=n;i++)
	{	
		
		cin>>L.elem[i];
		L.length++;
	}
}
void Traverse_sq(SqList L)//��������Ԫ�� 
{
		if (!L.elem)
		return;
		int i=1;
		while(L.elem[i]&&i<=L.length)
		{
			if((i)%100==0)
			{ 
				cout<<endl;
			}
			cout<<L.elem[i]<<" ";
			i++;
		}
		cout<<endl;
}
void InsertSort(SqList &L)//�򵥲������� 
{//����������������δ����� 
	for(int i=1;i<=L.length;i++)
	{
		if(L.elem[i]>L.elem[i-1])//���������������һ�������������� 
			continue;
		else
			{
				int t=i-1;
				while(L.elem[i]<L.elem[t])//ѭ���ҵ�����λ�� 
				{
					t--;
				}
				t++;//����λ��
			int temp=L.elem[i];//��¼��ʱ 
				for(int j=i;j>t;j--)//���� 
				{
					L.elem[j]=L.elem[j-1];
				}
				
			L.elem[t]=temp;	
			}
	}
}
void ShellInsert(SqList &L,int dk)//ϣ������ 
{
	for(int i=dk;i<=L.length;i++)//��dk+1��ʼ 
	{
		if(L.elem[i]<L.elem[i-dk])
		{
			int t=L.elem[i];//��ʱλ�� 
			int j=i-dk;
			while(j>=0&&(t<L.elem[j]))//�����м��dk�������� 
			{
				L.elem[j+dk]=L.elem[j];
				//��¼���ƣ���Ϊ����������λ�ã���Ӱ�����λ�õ�ϣ������ 
				j-=dk;
			}
			
			L.elem[j+dk]=t;
		}
	}
		
}
void ShellSort(SqList &L,int dlta[],int t)//ϣ������
{
	for(int k=0;k<t;k++)
	{
		ShellInsert(L,dlta[k]);
	}
	
 } 
 void BubbleSort(SqList &L)//ð������ 
 {
 	for(int i=0;i<=L.length;i++)
 		for(int j=i+1;j<=L.length;j++)
 		{
 			if(L.elem[i]>L.elem[j])
 			{
 				int t=L.elem[i];
 				L.elem[i]=L.elem[j];
 				L.elem[j]=t;
			 }
		 }
 }
int Partion(SqList &L,int low,int high)//ȷ��L.elem[i]Ԫ�ص�λ�� 
 {
 	int i=low;
 	int j=high;
 	int t=L.elem[i];
 	while(i<j)
 	{
 		while(L.elem[j]>=t&&i<j)
 		{
 			j--;
		}
 		L.elem[i]=L.elem[j];
		while(L.elem[i]<=t&&i<j)
 		{
 			i++;
		}
 			L.elem[j]=L.elem[i];
	}
	L.elem[i]=t;
	return i;
 }
 void QSort(SqList &L,int low,int high)//�������� 
 {
 	if(low<high)
 	{
 		int key=Partion(L,low,high);
		 QSort(L,low,key-1);
		 QSort(L,key+1,high);	
	 }
 }
 void SelectSort(SqList &L)//��ѡ������
 //��i֮��ѡ��һ����С��������iλ�� 
 {
 	for(int i=0;i<=L.length-1;i++)
 		{
 			int t=L.elem[i];
 			for(int j=i+1;j<=L.length;j++)
 			{
 				if(L.elem[j]<t)
 				{
 					int t1=L.elem[j];
 					L.elem[j]=t;
 					t=t1;
				 }
			 }
			 L.elem[i]=t;
		 }
 }
 void HeapAdjust(SqList &L,int s,int m)//�󶥶� 
 {
 	int t=L.elem[s];
 	for(int j=2*s;j<=m;j*=2)//�ӷ�Ҷ�ӽڵ�����������С��ֵ���ڸ� 
 	{
 		if(j<m&&(L.elem[j]<L.elem[j+1]))
		 j++;//�Ƚ������Һ��ӣ�jָ��ϴ��� 
 		if(t>L.elem[j])
		 break;//���t�����Һ��Ӷ��� 
 			L.elem[s]=L.elem[j];//��sλ�÷������Һ��ӵ�����ֵ 
		 	s=j;//s���Ƶ�j λ�� 
 		
	 }
	 L.elem[s]=t;//�����sλ���ѱ� 
 }
 void HeadSort(SqList &L)//������ 
 {
 	for(int i=L.length/2;i>0;i--)
 		HeapAdjust(L,i,L.length);
 	for(int j=L.length;j>1;j--)
 	{
 		int t=L.elem[1];
 		L.elem[1]=L.elem[j];
 		L.elem[j]=t;//������ֵ�������һ��λ�� 
 		HeapAdjust(L,1,j-1);//ȥ�����һ��ֵ���´����󶥶� 
	 }
 }
 void Merge(SqList S,SqList &T,int s,int m,int t)//�鲢 
 {//��S�е����ݹ鲢������T�� sΪ��һ������������� m+1Ϊ�ڶ�������������� 
 	int i=s,j=m+1,k=s;//��¼λ�� 
 	while(i<=m&&j<=t)
 	{
 		if(S.elem[i]<=S.elem[j])
			T.elem[k++]=S.elem[i++];
		else
				T.elem[k++]=S.elem[j++];
	 }
	 if(i<=m)
		while(i<=m)
	 	T.elem[k++]=S.elem[i++];
	else while(j<=t)
		T.elem[k++]=S.elem[j++];
 }
 void MergePass(SqList &S,SqList T,int n,int h)//һ�ι鲢������
 {
 	int i=1;
 	while(i<=n-2*h+1)//�����зֳ�hΪ��λ������ 
 	{
 		Merge(S,T,i,i+h-1,i+2*h-1);//�鲢0-h h-2h�� 
 		i+=2*h;//ÿ2h�鲢һ�� 
	 }
	 if(i<n-h+1)Merge(S,T,i,i+h-1,n);//���һ�����в���h Ϊ��λ��������С��h 
	 else//ʣ��һ��������û�й鲢 
	 {
	 	for(int k=i;k<=n;k++)
	 	{
	 		T.elem[k]=S.elem[k];
		 }
	 }
 }
 void MergeSort(SqList &S,SqList T,int n) 
 {
 	int h=1;//��ʼ�����г���Ϊ1 nΪ���г��� 
 	while(h<n)
 	{
 		MergePass(S,T,n,h);//h�ĳ��Ȳ��ϱ仯 
 		h=2*h;
 		MergePass(T,S,n,h);
 		h=2*h;
	 }
 }
 
 #define key 5
 bool InitQueue(LinkQueue *Q)
{
	Q->front=new QNode;
	if(!(Q->front))
		return false; 
	Q->front->next=NULL;
	Q->front->data=-1;
	Q->rear=Q->front;
	return true;
}
void DestroyQueue(LinkQueue *Q)
{
	Q->rear=NULL;
	delete Q->front;
	Q->front=NULL;
}
void RadixSort(SqList &L,int l_len)//�������� 
{
	LinkQueue *Queue=new LinkQueue[10];
	QNode *Node_head=new QNode,*p,*pre_p;
	int i;
	for(i=0;i<10;i++)
		InitQueue(Queue+i);//����Ͱ 
	pre_p=Node_head;
	for(i=1;i<=l_len;i++)//˳���ת���� 
	{
		p=new QNode;
		p->data=L.elem[i];
		pre_p->next=p;
		pre_p=p;
	}
	pre_p->next=NULL;
	for(i=1;i<=key;i++)//���䡢�ռ� 
	{
		Distribute(Node_head,Queue,i);
		Collection(Node_head,Queue);
	}
	p=Node_head->next;
	for(i=1;i<=l_len;i++,p=p->next)//������Ϣд��˳���  
		L.elem[i]=p->data; 
	pre_p=Node_head;
	while(pre_p)
	{
		p=pre_p->next;
		delete pre_p;
		pre_p=p;
	}
	for(i=0;i<10;i++)
		DestroyQueue(Queue+i);
	delete []Queue;
}
void Distribute(QNode *Node_head,Link_Queue Queue,int i)//���� 
{
	QNode *p=Node_head->next;
	int t;
	while(p)
	{
		t=Get_key(p,i);
		Queue[t].rear->next=p;
		Queue[t].rear=p;
		p=p->next;
		Queue[t].rear->next=NULL;
	}
	Node_head->next=NULL;
}
int Get_key(QNode *p,int i)//�õ�λ�� 
{
	int j,s=p->data;
	for(j=1;j<i;j++)
		s/=10;
	return s%10; 
}
void Collection(QNode *Node_head,Link_Queue Queue)//�ռ� 
{
	int i;
	QNode *p=Node_head;
	for(i=0;i<10;i++)
		if(Queue[i].front->next)
		{
			p->next=Queue[i].front->next;
			p=Queue[i].rear;
			Queue[i].front->next=NULL;
			Queue[i].rear=Queue[i].front;
		}
}
void fuzhi_wen(SqList &L)//���ļ��е��ļ����ݴ���˳��� 
{
	fstream file;
	file.open("paixu.txt",ios::in);
	if(file.fail())
	{
		cout<<"file open is error!"<<endl;
		exit(0);
	}
	int t,i=1;
	file>>t;
	L.length=0;
	while(!file.eof())
	{
		L.elem[i]=t;
		L.length++;
		i++;
		file>>t;
	}
	file.close();	
}
void creat_wen()//�����ļ� 
{
	fstream file;
	file.open("paixu.txt",ios::out);
	if(file.fail())
	{
		cout<<"file open is error!"<<endl;
		exit(0);
	}
	for(int i=1;i<max;i++)
	{	
		
		file<<i<<" ";
		//cout<<i<<" ";
	}
	file.close();
	
//	fstream file;
/*	file.open("paixu.txt",ios::in);
	if(file.fail())
	{
		cout<<"file open is error!"<<endl;
		exit(0);
	}
	int t;
	file>>t;
	while(!file.eof())
	{
		cout<<t<<" ";
		file>>t;
	}
	file.close();**/
}
void creat1_wen()//�����ļ� 
{
	fstream file;
	file.open("paixu.txt",ios::out);
	if(file.fail())
	{
		cout<<"file open is error!"<<endl;
		exit(0);
	}
	int t=max-1;
	for(int i=1;i<max;i++)
	{	
		
		file<<t<<" ";
		t--;
		
	}
	file.close();
}
void creat2_wen()//�����ļ� 
{
	fstream file;
	file.open("paixu.txt",ios::out);
	if(file.fail())
	{
		cout<<"file open is error!"<<endl;
		exit(0);
	}
	int t;
	srand((unsigned)time(NULL));
	t=rand()%20000;
	for(int i=1;i<max;i++)
	{	
		
		file<<t<<" ";
		t=rand()%20000;
		
	}
	file.close();
}
int main()
{//ֱ�Ӳ�������ϣ������ð�����򡢿�������ѡ�����򡢶����򣬹鲢���򡢻�������
	cout<<"			�����㷨�Ƚ�"<<endl;
	cout<<"			0.�����ļ�"<<endl;
	cout<<"			1.ֱ�Ӳ�������"<<endl;
	cout<<"			2.ϣ������"<<endl;
	cout<<"			3.ð������"<<endl;
	cout<<"			4.��������"<<endl;
	cout<<"			5.ѡ������"<<endl;
	cout<<"			6.������"<<endl;
	cout<<"			7.�鲢����"<<endl;
	cout<<"			8.��������"<<endl;
	cout<<"			9.�Ƚ�"<<endl;
	int chioce;
	cout<<"please int your choice:";
	cin>>chioce;
	switch(chioce)
	{
		
		case 0:
			{
				
				system("cls");
				cout<<"			�����㷨�Ƚ�"<<endl;
				cout<<"			  �����ļ�"<<endl;
				cout<<"			1.����"<<endl;
				cout<<"			2.����"<<endl;
				cout<<"			3.����"<<endl;
				int c;
				cout<<"please input your choice:";
				cin>>c;
				switch(c)
				{
					case 1:
						creat_wen();
						break;
					case 2:
						creat2_wen();
						break;
					case 3:
						creat1_wen();
						break;
					default:
						cout<<"chioce input is error!"<<endl;
						break;			
					}	
			/*	SqList L;
				Init_sq(L);
				fuzhi_wen(L);
				Traverse_sq(L);*/
				break;
			}
		case 1:
			{
				system("cls");
				cout<<"			�����㷨�Ƚ�"<<endl;
				cout<<"			ֱ�Ӳ�������"<<endl;
				SqList L;
				Init_sq(L);
				fuzhi_wen(L);
				double cost_time;
				clock_t start,end;
				start=clock();
				InsertSort(L);
				end=clock();
				cost_time=(double) (end-start)/(CLOCKS_PER_SEC);
				Traverse_sq(L);
				cout<<endl;
				cout<<"time:"<<cost_time<<endl;
				break;
			}
		case 2:
			{
				system("cls");
				cout<<"			�����㷨�Ƚ�"<<endl;
				cout<<"			 ϣ������"<<endl;
				SqList L;
				Init_sq(L);
				int a[3]={5,3,1};
				fuzhi_wen(L);
				double cost_time;
				clock_t start,end;
				start=clock();
				ShellSort(L,a,3);
				end=clock();
				cost_time=(double) (end-start)/(CLOCKS_PER_SEC);
				Traverse_sq(L);
				cout<<"time:"<<cost_time<<endl;
				break;
			}
		case 3: 
			{
				system("cls");
				cout<<"			�����㷨�Ƚ�"<<endl;
				cout<<"			ð������"<<endl;
				SqList L;
				Init_sq(L);
				fuzhi_wen(L);
				double cost_time;
				clock_t start,end;
				start=clock();
				BubbleSort(L);
				end=clock();
				cost_time=(double) (end-start)/(CLOCKS_PER_SEC);
				Traverse_sq(L);
				cout<<"time:"<<cost_time<<endl;
				break;
			}
		case 4:
			{
				system("cls");
				cout<<"			�����㷨�Ƚ�"<<endl;
				cout<<"			 ��������"<<endl;
				SqList L;
				Init_sq(L);
				fuzhi_wen(L);
				double cost_time;
				clock_t start,end;
				start=clock();
				QSort(L,0,L.length);
				end=clock();
				cost_time=(double) (end-start)/(CLOCKS_PER_SEC);
				Traverse_sq(L);
				cout<<"time:"<<cost_time<<endl;
				break;
			}
		case 5:
			{
				system("cls");
				cout<<"			�����㷨�Ƚ�"<<endl;
				cout<<"			 ѡ������"<<endl;	
				SqList L;
				Init_sq(L);
				fuzhi_wen(L);
				double cost_time;
				clock_t start,end;
				start=clock();
				SelectSort(L);
				end=clock();
				cost_time=(double) (end-start)/(CLOCKS_PER_SEC);
				Traverse_sq(L);
				cout<<"time:"<<cost_time<<endl; 				
				break;
			}
		case 6:
			{
				system("cls");
				cout<<"			�����㷨�Ƚ�"<<endl;
				cout<<"			 ������"<<endl;
				SqList L;
				Init_sq(L);
				fuzhi_wen(L);
				double cost_time;
				clock_t start,end;
				start=clock();
				HeadSort(L);
				end=clock();
				cost_time=(double) (end-start)/(CLOCKS_PER_SEC);
				Traverse_sq(L);
				cout<<"time:"<<cost_time<<endl; 
				break;
			}
		case 7:
			{
				system("cls");
				cout<<"			�����㷨�Ƚ�"<<endl;
				cout<<"			 �鲢����"<<endl;
				SqList L,L1;
				Init_sq(L);
				Init_sq(L1);
				fuzhi_wen(L);
				for(int i=1;i<=L.length;i++)
				{
						L1.elem[i]=L.elem[i];
				}
				L1.length=L.length;
				double cost_time;
				clock_t start,end;
				start=clock();
				MergeSort(L,L1,L.length);
			end=clock();
				cost_time=(double) (end-start)/(CLOCKS_PER_SEC);
				Traverse_sq(L);
				cout<<"time:"<<cost_time<<endl;
				break;
			} 
		case 8:
			{
				system("cls");
				cout<<"			�����㷨�Ƚ�"<<endl;
				cout<<"			 ��������"<<endl;
				SqList L;
				Init_sq(L);
				fuzhi_wen(L);
				double cost_time;
				clock_t start,end;
				start=clock();
				RadixSort(L,L.length);
				end=clock();
				cost_time=(double) (end-start)/(CLOCKS_PER_SEC);
				Traverse_sq(L);
				cout<<"time:"<<cost_time<<endl;
				break;
			}
		case 9:
			{
				system("cls");
				cout<<"			�����㷨�Ƚ�"<<endl;
				cout<<"			 �Ƚ�"<<endl;
				SqList L,L1;
				Init_sq(L);
				fuzhi_wen(L);
				double cost_time;
				clock_t start,end;
				start=clock();
				InsertSort(L);
				end=clock();
				cost_time=(double) (end-start)/(CLOCKS_PER_SEC);
				cout<<"InsertSort time:"<<cost_time<<endl;
				
				int a[3]={5,3,1};
				fuzhi_wen(L);
				start=clock();
				end=clock();
				cost_time=(double) (end-start)/(CLOCKS_PER_SEC);
				cout<<"ShellSort time:"<<cost_time<<endl;
				
				fuzhi_wen(L);
				start=clock();
				BubbleSort(L);
				end=clock();
				cost_time=(double) (end-start)/(CLOCKS_PER_SEC);
				cout<<"BubbleSort time:"<<cost_time<<endl;
				
				fuzhi_wen(L);
				start=clock();
				QSort(L,0,L.length);
				end=clock();
				cost_time=(double) (end-start)/(CLOCKS_PER_SEC);
				cout<<"QSort time:"<<cost_time<<endl;
				
				fuzhi_wen(L);
				start=clock();
				SelectSort(L);
				end=clock();
				cost_time=(double) (end-start)/(CLOCKS_PER_SEC);
				cout<<"SelectSort time:"<<cost_time<<endl;
				
				fuzhi_wen(L);
				start=clock();
				HeadSort(L);
				end=clock();
				cost_time=(double) (end-start)/(CLOCKS_PER_SEC);
				cout<<"HeadSort time:"<<cost_time<<endl;
				
				Init_sq(L1);
				fuzhi_wen(L);
				for(int i=1;i<=L.length;i++)
				{
						L1.elem[i]=L.elem[i];
				}
				L1.length=L.length;
				start=clock();
				MergeSort(L,L1,L.length);
				end=clock();
				cost_time=(double) (end-start)/(CLOCKS_PER_SEC);
				cout<<"MergeSort time:"<<cost_time<<endl;
				
				fuzhi_wen(L);
				start=clock();
				RadixSort(L,L.length);
				end=clock();
				cost_time=(double) (end-start)/(CLOCKS_PER_SEC);
				cout<<"RadixSort time:"<<cost_time<<endl;
				break;
					
			}	
		default:
			cout<<"chioce input is error!"<<endl;
			break;
			
	}
	return 0;
}
