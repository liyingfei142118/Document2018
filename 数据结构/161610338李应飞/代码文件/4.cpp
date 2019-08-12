#include<iostream>
using namespace std;
#include<fstream>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>
#define MAX 10000

typedef struct Eglish//存文章的字符 及次数 
{
	char ascall[128];//字符 
	int weight[128];//次数 
	int n;
	int M;//开辟数组的长度 
	
}English;
//静态三叉链表存储结构
typedef struct//编码表 
{
	int weight;//权值只能是正数
	int parent;
	int lchild;
	int rchild;
}HTNode;
typedef struct//文件结构体 
{
	char ch;
	int weight;//权值只能是正数
	int parent;
	int lchild;
	int rchild;
}H;
typedef HTNode HuffmanTree[128];//0号单元不使用
typedef char * HuffmanCode[128];//存储每个字符的哈夫曼编码表，
//是一个字符指针数组，每个数组元素是指向字符指针的指针
typedef char * HuffmanCode[128];//存储每个字符的哈夫曼编码表

void Creat_wen(English &E);//创建文件
void select(HuffmanTree HT, int k, int &s1, int &s2);//k代表表当前位置前面s1代表最小值s2表次小值
void Create_HuffmanTree(HuffmanTree &HT,Eglish E);//创建编码表 
void open_code();//open哈夫曼编码表
void Decode_HuffmanCode(HuffmanTree HT,Eglish E, char Str[], int len, char result[]);//解码 
void Print_HuffmanTree(HuffmanTree HT, Eglish E);//打印编码表 
void Put(HuffmanCode HC,Eglish E);//将英文文章翻译成编码文章 
void Get(HuffmanTree HT,English E);//将编码文章翻译英文文章 
void Print_HuffmanCode(HuffmanCode HC, Eglish E);//每个字符的编码 
void Encode_HuffmanCode(HuffmanTree HT,Eglish E ,HuffmanCode &HC);//编码 加密
 
void Creat_wen(English &E)//创建文件 
{
	fstream file;
	int Ascall[128]={0};
	file.open("haff.txt",ios::in);
	if(file.fail())
	{
		cout<<"file open error!"<<endl;
		exit(0);
	}
	char ch;
	file.get(ch);
	while(!file.eof())
	{
		Ascall[ch]++;
		file.get(ch);
	}
	file.close();
	
	E.n=0;
	for(int i=0;i<128;i++)//筛选需要的字符 
	{
		if(Ascall[i]>0)
		{
			E.ascall[E.n]=i;
			E.weight[E.n]=Ascall[i];
			E.n++;
		}
	}
	for(int i=0;i<E.n;i++)
	{
		if(i!=0&&(i%10==0))
			cout<<endl;
		cout<<E.ascall[i]<<":"<<E.weight[i]<<"    ";
	
	}
	cout<<endl;
}
//parent不为0说明该结点已经参与构造了，故不许再考虑
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
//void Create_HuffmanTree(HuffmanTree &HT, int *w, int n)
void Create_HuffmanTree(HuffmanTree &HT,Eglish E)
{
	if(E.n <=0)
		return;
	//对树赋初值
	for(int i = 0; i <=E.n; i++)	{
		HT[i].weight = E.weight[i];
		HT[i].lchild = 0;
		HT[i].parent = 0;
		HT[i].rchild = 0;
	}
	int	M=2*E.n-1;
	for(int i=E.n; i <=E.M; i++)
	{
		HT[i].weight = 0;
		HT[i].lchild = 0;
		HT[i].parent = 0;
		HT[i].rchild = 0;
	}
	for(int i =E.n; i <=E.M; i++)
	{
		int s1, s2;
		select(HT, i-1, s1, s2);
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
	fstream file;
	file.open("code.dat",ios::out|ios::binary);
	if(file.fail())
	{
		cout<<"file  open is error!"<<endl;
		exit(0);
	}
	H f;
	for(int i = 0; i <= E.M; i++)	
	{	
		if(i > E.n)
			f.ch='-';
		else
			f.ch=E.ascall[i];
		f.lchild=HT[i].lchild;
		f.parent=HT[i].parent;
		f.rchild=HT[i].rchild;
		f.weight=HT[i].weight;
		file.write((char *)&f,sizeof(f));
	}
	file.close();
}
void open_code()//open哈夫曼编码表，
{
	fstream file;
	file.open("code.dat",ios::in|ios::binary);
	if(file.fail())
	{
		cout<<"file  open is error!"<<endl;
		exit(0);
	}
	H f;
	file.read((char *)&f,sizeof(f));
	while(!file.eof())
	{
		cout<<f.ch <<" "<<f.weight<<" "<<f.parent<<" "<<f.lchild<<" "<<f.rchild<<endl;
		file.read((char *)&f,sizeof(f));
	}
	file.close();
}

void Decode_HuffmanCode(HuffmanTree HT,Eglish E, char Str[], int len, char result[])//解码 
{	fstream file1;
	file1.open("haff2.txt",ios::out);
	if(file1.fail())
	{
		cout<<"file1 open error!"<<endl;
		exit(0);
	}
	int p =E.M;//HT的最后一个节点是根节点，前n个节点是叶子节点
	int i = 0;//指示测试串中的第i个字符
	//char result[30];//存储解码以后的字符串
	int j = 0;//指示结果串中的第j个字符
	while(i<len)
	{
		if(Str[i] == '0')
		{
			p = HT[p].lchild;
		}
		if(Str[i] == '1')
		{
			p = HT[p].rchild;
		}

		if(p <= E.n)
		{//p<=N则表明p为叶子节点,因为在构造哈夫曼树HT时，HT的m个节点中前n个节点为叶子节点
			result[j] = E.ascall[p];
			cout<<result[j];
			file1<<E.ascall[p]<<" ";
			j++;
			p = E.M;//p重新指向根节点
		}
		i++;
	}
	cout<<endl;
	cout<<"j:"<<j<<endl;
//	result[j] = '\0';//结果串的结束符
	file1.close();
		
}
void Print_HuffmanTree(HuffmanTree HT, Eglish E)//打印编码表 
{
	cout<<endl;
	cout<<"data, weight, parent, lchild, rchild"<<endl;
	for(int i = 0; i <= E.M; i++){
		if(i > E.n)
		{
			cout<<"-"<<" "<<HT[i].weight<<" "<<HT[i].parent<<" "<<HT[i].lchild<<" "<<HT[i].rchild<<endl;
		}
		else
		{
			cout<<E.ascall[i]<<" "<<HT[i].weight<<" "<<HT[i].parent<<" "<<HT[i].lchild<<" "<<HT[i].rchild<<endl;
		}
	}
}
void Put(HuffmanCode HC,Eglish E)//将英文文章翻译成编码文章 
{
	fstream file,file1;
	file.open("haff.txt",ios::in);
	if(file.fail())
	{
		cout<<"file open error!"<<endl;
		exit(0);
	}
	file1.open("haff1.txt",ios::out);
	if(file1.fail())
	{
		cout<<"file1 open error!"<<endl;
		exit(0);
	}
	char ch;
	file.get(ch);
	while(!file.eof())
	{
		//cout<<HC[E.ascall[ch]]<<" ";
		for(int i=1;i<=E.n;i++)
		{
			if(E.ascall[i]==ch)
			{
				file1<<HC[i];
				break;
			}
				
		}
		file.get(ch);
	}
	file.close();
	file1.close();
	
	file.open("haff1.txt",ios::in);
	if(file.fail())
	{
		cout<<"file open error!"<<endl;
		exit(0);
	}
	char c;
	file.get(c);
	while(!file.eof())
	{
		cout<<c;
		file.get(c);
	}
	file.close();
}
void Get(HuffmanTree HT,English E)//将编码文章翻译英文文章 
{
	char str[1000000];
	fstream file,file1;
	file.open("haff1.txt",ios::in);
	if(file.fail())
	{
		cout<<"file open error!"<<endl;
		exit(0);
	}

	char ch;
	file>>ch;
	int i=0;
	while(!file.eof())
	{
		str[i]=ch;
		i++;
		file>>ch;
	}
	file.close();
	str[i]='\0';
	char result[1000001];
	cout<<endl;
/*	cout<<"222"<<endl;
	for(int j=0;j<i;j++)
	{
		cout<<str[j];
	}*/
	Decode_HuffmanCode(HT, E,str, i, result);
	
	file1.open("haff2.txt",ios::in);
	if(file1.fail())
	{
		cout<<"file1 open error!"<<endl;
		exit(0);
	
	}
	file1>>ch;
	while(!file1.eof())
	{
		cout<<ch<<" ";
		file1>>ch;
	}
	for(int j=0;result[j]!='\0';j++)
	{
		
		cout<<result[j];
	}
	file1.close();
}
void Print_HuffmanCode(HuffmanCode HC, Eglish E)//每个字符的编码 
{
	cout<<endl;
	for(int t=1,i = 0; i <=E.n; t++,i++)
	{
		if(t%4==0)
			cout<<endl;
		cout<<E.ascall[i]<<":"<<HC[i]<<"       ";
	}
	cout<<endl;
}
void Encode_HuffmanCode(HuffmanTree HT,Eglish E ,HuffmanCode &HC)
{
	
	//每个字符的编码长度不会超过n
	char tmp[E.n];
	tmp[E.n-1] = '\0';//编码的结束符
	int start, c, f;
	for(int i = 0; i <=E.n; i++)
	{//对于第i个待编码字符即第i个带权值的叶子节点
		start =E.n-1;//编码生成以后，start将指向编码的起始位置
		c = i;
		f = HT[i].parent;

		while(f)
		{//f!=0,即f不是根节点的父节点
			if(HT[f].lchild == c)
			{
				tmp[--start] = '0';
				
			}
			else
			{//HT[f].rchild == c,注意:由于哈夫曼树中只存在叶子节点和度为2的节点，
			//所以除开叶子节点，节点一定有左右2个分支
				tmp[--start] = '1';
			}
			c = f;
			f = HT[f].parent;
		}
		HC[i] = (char *)malloc((E.n-start)*sizeof(char));//每次tmp的后n-start个位置有编码存在
		strcpy(HC[i], &tmp[start]);//将tmp的后n-start个元素分给H[i]指向的的字符串
	}
}
int main()
{
	English E;
	Creat_wen(E);//创建编码数组 即从文件中读出字符的及其次数 
	E.M=2*E.n-1;//编码表的长度 
	HuffmanTree HT;	
	Create_HuffmanTree(HT,E);
	 open_code();//编码表 
	//Print_HuffmanTree(HT,E);//输出编码表 
	HuffmanCode HC;//HC有n个元素，每个元素是一个指向字符串的指针，
	//即每个元素是一个char *的变量
	Encode_HuffmanCode(HT,E, HC);//为每个字符求解哈夫曼编码
	Print_HuffmanCode(HC,E);
	Put(HC,E);
	Get(HT,E);
}
