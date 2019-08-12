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
void RadixSort(int *L,int l_len);//基数排序 
void Distribute(QNode *Node_head,LinkQueue *Queue,int i);//分配 
void Collection(QNode *Node_head,LinkQueue *Queue); //收集 
int Get_key(QNode *p,int i);//得到位值 
void Traverse(int *L,int l_len);
void Init_sq(SqList &L);
void Creat_sq(SqList &L,int n);//对顺序表初始化
void Traverse_sq(SqList L);//遍历所有元素
void InsertSort(SqList &L);//简单插入排序
void ShellInsert(SqList &L,int dk);//希尔排序 
void ShellSort(SqList &L,int dlta[],int t);//希尔排序
void BubbleSort(SqList &L);//冒泡排序 
int Partion(SqList &L,int low,int high);//确定L.elem[i]元素的位置 
void QSort(SqList &L,int low,int high);//快速排序 
void SelectSort(SqList &L);//简单选择排序
void HeapAdjust(SqList &L,int s,int m);//大顶堆 
void HeadSort(SqList &L);//堆排序 
void Merge(SqList S,SqList &T,int s,int m,int t);//归并 
void MergePass(SqList &S,SqList T,int n,int h);//一次归并并排序
void MergeSort(SqList &S,SqList T,int n); //归并排序
void fuzhi_wen(SqList &L);//将文件中的文件内容传给顺序表 
void creat_wen();//正序文件 
void creat1_wen();//逆序文件 
void creat1_wen();//逆序文件 
  
void Init_sq(SqList &L)
{
	L.elem=(int *)malloc(max*sizeof(int));
	if(!L.elem)exit(0);
	L.length=0;
	L.listsize=max;
}

void Creat_sq(SqList &L,int n)//对顺序表初始化 
{
	
	if(n>max)exit(0);
	for(int i=1;i<=n;i++)
	{	
		
		cin>>L.elem[i];
		L.length++;
	}
}
void Traverse_sq(SqList L)//遍历所有元素 
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
void InsertSort(SqList &L)//简单插入排序 
{//在有序的序列里插入未有序的 
	for(int i=1;i<=L.length;i++)
	{
		if(L.elem[i]>L.elem[i-1])//如果大于有序的最后一个数，不用排序 
			continue;
		else
			{
				int t=i-1;
				while(L.elem[i]<L.elem[t])//循环找到待插位置 
				{
					t--;
				}
				t++;//待插位置
			int temp=L.elem[i];//记录临时 
				for(int j=i;j>t;j--)//后移 
				{
					L.elem[j]=L.elem[j-1];
				}
				
			L.elem[t]=temp;	
			}
	}
}
void ShellInsert(SqList &L,int dk)//希尔排序 
{
	for(int i=dk;i<=L.length;i++)//从dk+1开始 
	{
		if(L.elem[i]<L.elem[i-dk])
		{
			int t=L.elem[i];//临时位置 
			int j=i-dk;
			while(j>=0&&(t<L.elem[j]))//对所有间隔dk的数排序 
			{
				L.elem[j+dk]=L.elem[j];
				//记录后移，因为如果放在这个位置，会影响这个位置的希尔排序 
				j-=dk;
			}
			
			L.elem[j+dk]=t;
		}
	}
		
}
void ShellSort(SqList &L,int dlta[],int t)//希尔排序
{
	for(int k=0;k<t;k++)
	{
		ShellInsert(L,dlta[k]);
	}
	
 } 
 void BubbleSort(SqList &L)//冒泡排序 
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
int Partion(SqList &L,int low,int high)//确定L.elem[i]元素的位置 
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
 void QSort(SqList &L,int low,int high)//快速排序 
 {
 	if(low<high)
 	{
 		int key=Partion(L,low,high);
		 QSort(L,low,key-1);
		 QSort(L,key+1,high);	
	 }
 }
 void SelectSort(SqList &L)//简单选择排序
 //在i之后选择一个最小的数置于i位置 
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
 void HeapAdjust(SqList &L,int s,int m)//大顶堆 
 {
 	int t=L.elem[s];
 	for(int j=2*s;j<=m;j*=2)//从非叶子节点向下搜索最小的值置于根 
 	{
 		if(j<m&&(L.elem[j]<L.elem[j+1]))
		 j++;//比较左孩子右孩子，j指向较大者 
 		if(t>L.elem[j])
		 break;//如果t比左右孩子都大 
 			L.elem[s]=L.elem[j];//将s位置放置左右孩子的最大的值 
		 	s=j;//s下移到j 位置 
 		
	 }
	 L.elem[s]=t;//这里的s位置已变 
 }
 void HeadSort(SqList &L)//堆排序 
 {
 	for(int i=L.length/2;i>0;i--)
 		HeapAdjust(L,i,L.length);
 	for(int j=L.length;j>1;j--)
 	{
 		int t=L.elem[1];
 		L.elem[1]=L.elem[j];
 		L.elem[j]=t;//将最大的值放在最后一个位置 
 		HeapAdjust(L,1,j-1);//去除最后一个值重新创建大顶堆 
	 }
 }
 void Merge(SqList S,SqList &T,int s,int m,int t)//归并 
 {//将S中的数据归并并排序T中 s为第一个有序序列起点 m+1为第二个有序序列起点 
 	int i=s,j=m+1,k=s;//记录位置 
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
 void MergePass(SqList &S,SqList T,int n,int h)//一次归并并排序
 {
 	int i=1;
 	while(i<=n-2*h+1)//将序列分成h为单位的序列 
 	{
 		Merge(S,T,i,i+h-1,i+2*h-1);//归并0-h h-2h到 
 		i+=2*h;//每2h归并一次 
	 }
	 if(i<n-h+1)Merge(S,T,i,i+h-1,n);//最后一个序列不是h 为单位的序列且小于h 
	 else//剩下一个子序列没有归并 
	 {
	 	for(int k=i;k<=n;k++)
	 	{
	 		T.elem[k]=S.elem[k];
		 }
	 }
 }
 void MergeSort(SqList &S,SqList T,int n) 
 {
 	int h=1;//初始子序列长度为1 n为序列长度 
 	while(h<n)
 	{
 		MergePass(S,T,n,h);//h的长度不断变化 
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
void RadixSort(SqList &L,int l_len)//基数排序 
{
	LinkQueue *Queue=new LinkQueue[10];
	QNode *Node_head=new QNode,*p,*pre_p;
	int i;
	for(i=0;i<10;i++)
		InitQueue(Queue+i);//构造桶 
	pre_p=Node_head;
	for(i=1;i<=l_len;i++)//顺序表转链表 
	{
		p=new QNode;
		p->data=L.elem[i];
		pre_p->next=p;
		pre_p=p;
	}
	pre_p->next=NULL;
	for(i=1;i<=key;i++)//分配、收集 
	{
		Distribute(Node_head,Queue,i);
		Collection(Node_head,Queue);
	}
	p=Node_head->next;
	for(i=1;i<=l_len;i++,p=p->next)//链表信息写入顺序表  
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
void Distribute(QNode *Node_head,Link_Queue Queue,int i)//分配 
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
int Get_key(QNode *p,int i)//得到位数 
{
	int j,s=p->data;
	for(j=1;j<i;j++)
		s/=10;
	return s%10; 
}
void Collection(QNode *Node_head,Link_Queue Queue)//收集 
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
void fuzhi_wen(SqList &L)//将文件中的文件内容传给顺序表 
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
void creat_wen()//正序文件 
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
void creat1_wen()//逆序文件 
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
void creat2_wen()//乱序文件 
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
{//直接插入排序、希尔排序，冒泡排序、快速排序、选择排序、堆排序，归并排序、基数排序
	cout<<"			排序算法比较"<<endl;
	cout<<"			0.创建文件"<<endl;
	cout<<"			1.直接插入排序"<<endl;
	cout<<"			2.希尔排序"<<endl;
	cout<<"			3.冒泡排序"<<endl;
	cout<<"			4.快速排序"<<endl;
	cout<<"			5.选择排序"<<endl;
	cout<<"			6.堆排序"<<endl;
	cout<<"			7.归并排序"<<endl;
	cout<<"			8.基数排序"<<endl;
	cout<<"			9.比较"<<endl;
	int chioce;
	cout<<"please int your choice:";
	cin>>chioce;
	switch(chioce)
	{
		
		case 0:
			{
				
				system("cls");
				cout<<"			排序算法比较"<<endl;
				cout<<"			  创建文件"<<endl;
				cout<<"			1.正序"<<endl;
				cout<<"			2.乱序"<<endl;
				cout<<"			3.逆序"<<endl;
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
				cout<<"			排序算法比较"<<endl;
				cout<<"			直接插入排序"<<endl;
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
				cout<<"			排序算法比较"<<endl;
				cout<<"			 希尔排序"<<endl;
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
				cout<<"			排序算法比较"<<endl;
				cout<<"			冒泡排序"<<endl;
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
				cout<<"			排序算法比较"<<endl;
				cout<<"			 快速排序"<<endl;
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
				cout<<"			排序算法比较"<<endl;
				cout<<"			 选择排序"<<endl;	
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
				cout<<"			排序算法比较"<<endl;
				cout<<"			 堆排序"<<endl;
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
				cout<<"			排序算法比较"<<endl;
				cout<<"			 归并排序"<<endl;
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
				cout<<"			排序算法比较"<<endl;
				cout<<"			 基数排序"<<endl;
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
				cout<<"			排序算法比较"<<endl;
				cout<<"			 比较"<<endl;
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
