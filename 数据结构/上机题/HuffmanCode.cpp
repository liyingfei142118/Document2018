#include<iostream>
using namespace std;
#include<malloc.h>
#include<stdlib.h>
#include<string.h>
#define N 8//带权值的叶子节点数或者是需要编码的字符数
#define M 2*N-1//n个叶子节点构造的哈夫曼树有2n-1个结点
#define MAX 10000

//静态三叉链表存储结构
typedef struct{
	int weight;//权值只能是正数
	int parent;
	int lchild;
	int rchild;
}HTNode;
typedef HTNode HuffmanTree[M+1];//0号单元不使用

//在HT[1...k]里选择parent为0的且权值最小的2结点，其序号分别为s1,s2，parent不为0说明该结点已经参与构造了，故不许再考虑
void select(HuffmanTree HT, int k, int &s1, int &s2)//k代表表当前位置前面s1代表最小值s2表次小值
{
	//假设s1对应的权值总是<=s2对应的权值
 int tmp = MAX, word = 0;//tmp用于找到最小值，word用于标记位置 
	for(int i = 1; i <= k; i++)
	{
		if(!HT[i].parent)//parent必须为0
		{
			if(tmp > HT[i].weight)
			{
				tmp = HT[i].weight;//tmp最后为最小的weight
				word = i;
			}
		}
	}
	s1 = word;	
	tmp = MAX;
	int key = 0;//tmp用于找到次小值，key用于标记位置
	for(int i = 1; i <= k; i++)
	{
		if((!HT[i].parent) && i!=s1)//parent必须为0和不能等于最小值 
		{
			if(tmp > HT[i].weight)
			{
				tmp = HT[i].weight;
				key = i;
			}
		}
	}
	s2 = key;
}
//构造哈夫曼树
void Create_HuffmanTree(HuffmanTree &HT, int *w, int n)
{
	if(n <= 1)
		return;
	//对树赋初值
	for(int i = 1; i <= n; i++)//HT前n个分量存储叶子节点，他们均带有权值
	{
		HT[i].weight = w[i];
		HT[i].lchild = 0;
		HT[i].parent = 0;
		HT[i].rchild = 0;
	}
	for(int i=n+1; i <=M; i++)//HT后m-n个分量存储中间结点，最后一个分量显然是整棵树的根节点
	{
		HT[i].weight = 0;
		HT[i].lchild = 0;
		HT[i].parent = 0;
		HT[i].rchild = 0;
	}
	//开始构建哈夫曼树，即创建HT的后m-n个结点的过程，直至创建出根节点。用哈夫曼算法
	for(int i = n+1; i <= M; i++)
	{
		int s1, s2;
		select(HT, i-1, s1, s2);
//在HT[1...i-1]里选择parent为0的且权值最小的2结点，其序号分别为s1,s2，
//parent不为0说明该结点已经参与构造了，故不许再考虑
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
}
typedef char * HuffmanCode[N+1];//存储每个字符的哈夫曼编码表，
//是一个字符指针数组，每个数组元素是指向字符指针的指针
void Print_HuffmanCode(HuffmanCode HC, char ch[])
{
	cout<<endl;
	for(int i = 1; i <= N; i++)
	{
		cout<<ch[i]<<" :"<<HC[i]<<"  ";
	}
	cout<<endl;
}
void Print_HuffmanTree(HuffmanTree HT, char ch[])
{
	cout<<endl;
	cout<<"data, weight, parent, lchild, rchild"<<endl;
	for(int i = 1; i <= M; i++){
		if(i > N)
		{
			cout<<"-"<<" "<<HT[i].weight<<" "<<HT[i].parent<<" "<<HT[i].lchild<<" "<<HT[i].rchild<<endl;
		}
		else
		{
			cout<<ch[i]<<" "<<HT[i].weight<<" "<<HT[i].parent<<" "<<HT[i].lchild<<" "<<HT[i].rchild<<endl;
		}
	}
}
void Encode_HuffmanCode(HuffmanTree HT, HuffmanCode &HC)
{
	//char *tmp = (char *)malloc(n * sizeof(char));//将每一个字符对应的编码放在临时工作空间tmp里，
	//每个字符的编码长度不会超过n
	char tmp[N];
	tmp[N-1] = '\0';//编码的结束符
	int start, c, f;
	for(int i = 1; i <= N; i++)
	{//对于第i个待编码字符即第i个带权值的叶子节点
		start = N-1;//编码生成以后，start将指向编码的起始位置
		c = i;
		f = HT[i].parent;

		while(f)
		{//f!=0,即f不是根节点的父节点
			if(HT[f].lchild == c)
			{
				tmp[start] = '0';
				start--;
			}
			else{//HT[f].rchild == c,注意:由于哈夫曼树中只存在叶子节点和度为2的节点，所以除开叶子节点，节点一定有左右2个分支
				tmp[start] = '1';
				start--;
			}
			c = f;
			f = HT[f].parent;
		}
		HC[i] = (char *)malloc((N-start)*sizeof(char));//每次tmp的后n-start个位置有编码存在
		strcpy(HC[i], &tmp[start]);//将tmp的后n-start个元素分给H[i]指向的的字符串
	}
}
//打印哈夫曼编码表，当编码表生成以后，以后就可以对字符串进行编码了，只要对应编码表进行转换即可 
typedef char * HuffmanCode[N+1];//存储每个字符的哈夫曼编码表，
//是一个字符指针数组，每个数组元素是指向字符指针的指针
int main()
{
	HuffmanTree HT;	
	char ch[N+1];//0号单元不使用，存储n个等待编码的字符
	int w[N+1];//0号单元不使用，存储n个字符对应的权值
	
	cout<<"请输入N个字符以及该字符对应的权值:"<<endl;
	for(int i = 1; i <= N; i++){
		cin>>ch[i]>>w[i];
	}//即w里第i个权值对应的是ch里第i个字符元素
	Create_HuffmanTree(HT, w , N);//构建哈夫曼树
	Print_HuffmanTree(HT, ch);
	
	HuffmanCode HC;//HC有n个元素，每个元素是一个指向字符串的指针，
	//即每个元素是一个char *的变量
	Encode_HuffmanCode(HT, HC);//为每个字符求解哈夫曼编码
	Print_HuffmanCode(HC, ch);
	return 0;
}
