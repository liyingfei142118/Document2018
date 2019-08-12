#include<iostream>
using namespace std;
#include<fstream>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>
#define MAX 10000

typedef struct Eglish//�����µ��ַ� ������ 
{
	char ascall[128];//�ַ� 
	int weight[128];//���� 
	int n;
	int M;//��������ĳ��� 
	
}English;
//��̬��������洢�ṹ
typedef struct//����� 
{
	int weight;//Ȩֵֻ��������
	int parent;
	int lchild;
	int rchild;
}HTNode;
typedef struct//�ļ��ṹ�� 
{
	char ch;
	int weight;//Ȩֵֻ��������
	int parent;
	int lchild;
	int rchild;
}H;
typedef HTNode HuffmanTree[128];//0�ŵ�Ԫ��ʹ��
typedef char * HuffmanCode[128];//�洢ÿ���ַ��Ĺ����������
//��һ���ַ�ָ�����飬ÿ������Ԫ����ָ���ַ�ָ���ָ��
typedef char * HuffmanCode[128];//�洢ÿ���ַ��Ĺ����������

void Creat_wen(English &E);//�����ļ�
void select(HuffmanTree HT, int k, int &s1, int &s2);//k�����ǰλ��ǰ��s1������Сֵs2���Сֵ
void Create_HuffmanTree(HuffmanTree &HT,Eglish E);//��������� 
void open_code();//open�����������
void Decode_HuffmanCode(HuffmanTree HT,Eglish E, char Str[], int len, char result[]);//���� 
void Print_HuffmanTree(HuffmanTree HT, Eglish E);//��ӡ����� 
void Put(HuffmanCode HC,Eglish E);//��Ӣ�����·���ɱ������� 
void Get(HuffmanTree HT,English E);//���������·���Ӣ������ 
void Print_HuffmanCode(HuffmanCode HC, Eglish E);//ÿ���ַ��ı��� 
void Encode_HuffmanCode(HuffmanTree HT,Eglish E ,HuffmanCode &HC);//���� ����
 
void Creat_wen(English &E)//�����ļ� 
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
	for(int i=0;i<128;i++)//ɸѡ��Ҫ���ַ� 
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
//parent��Ϊ0˵���ý���Ѿ����빹���ˣ��ʲ����ٿ���
void select(HuffmanTree HT, int k, int &s1, int &s2)//k�����ǰλ��ǰ��s1������Сֵs2���Сֵ
{
	//����s1��Ӧ��Ȩֵ����<=s2��Ӧ��Ȩֵ
 int tmp = MAX, word = 0;//tmp�����ҵ���Сֵ��word���ڱ��λ�� 
	for(int i = 1; i <= k; i++)
	{
		if(!HT[i].parent)//parent����Ϊ0
		{
			if(tmp > HT[i].weight)
			{
				tmp = HT[i].weight;//tmp���Ϊ��С��weight
				word = i;
			}
		}
	}
	s1 = word;	
	tmp = MAX;
	int key = 0;//tmp�����ҵ���Сֵ��key���ڱ��λ��
	for(int i = 1; i <= k; i++)
	{
		if((!HT[i].parent) && i!=s1)//parent����Ϊ0�Ͳ��ܵ�����Сֵ 
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
//�����������
//void Create_HuffmanTree(HuffmanTree &HT, int *w, int n)
void Create_HuffmanTree(HuffmanTree &HT,Eglish E)
{
	if(E.n <=0)
		return;
	//��������ֵ
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
void open_code()//open�����������
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

void Decode_HuffmanCode(HuffmanTree HT,Eglish E, char Str[], int len, char result[])//���� 
{	fstream file1;
	file1.open("haff2.txt",ios::out);
	if(file1.fail())
	{
		cout<<"file1 open error!"<<endl;
		exit(0);
	}
	int p =E.M;//HT�����һ���ڵ��Ǹ��ڵ㣬ǰn���ڵ���Ҷ�ӽڵ�
	int i = 0;//ָʾ���Դ��еĵ�i���ַ�
	//char result[30];//�洢�����Ժ���ַ���
	int j = 0;//ָʾ������еĵ�j���ַ�
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
		{//p<=N�����pΪҶ�ӽڵ�,��Ϊ�ڹ����������HTʱ��HT��m���ڵ���ǰn���ڵ�ΪҶ�ӽڵ�
			result[j] = E.ascall[p];
			cout<<result[j];
			file1<<E.ascall[p]<<" ";
			j++;
			p = E.M;//p����ָ����ڵ�
		}
		i++;
	}
	cout<<endl;
	cout<<"j:"<<j<<endl;
//	result[j] = '\0';//������Ľ�����
	file1.close();
		
}
void Print_HuffmanTree(HuffmanTree HT, Eglish E)//��ӡ����� 
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
void Put(HuffmanCode HC,Eglish E)//��Ӣ�����·���ɱ������� 
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
void Get(HuffmanTree HT,English E)//���������·���Ӣ������ 
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
void Print_HuffmanCode(HuffmanCode HC, Eglish E)//ÿ���ַ��ı��� 
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
	
	//ÿ���ַ��ı��볤�Ȳ��ᳬ��n
	char tmp[E.n];
	tmp[E.n-1] = '\0';//����Ľ�����
	int start, c, f;
	for(int i = 0; i <=E.n; i++)
	{//���ڵ�i���������ַ�����i����Ȩֵ��Ҷ�ӽڵ�
		start =E.n-1;//���������Ժ�start��ָ��������ʼλ��
		c = i;
		f = HT[i].parent;

		while(f)
		{//f!=0,��f���Ǹ��ڵ�ĸ��ڵ�
			if(HT[f].lchild == c)
			{
				tmp[--start] = '0';
				
			}
			else
			{//HT[f].rchild == c,ע��:���ڹ���������ֻ����Ҷ�ӽڵ�Ͷ�Ϊ2�Ľڵ㣬
			//���Գ���Ҷ�ӽڵ㣬�ڵ�һ��������2����֧
				tmp[--start] = '1';
			}
			c = f;
			f = HT[f].parent;
		}
		HC[i] = (char *)malloc((E.n-start)*sizeof(char));//ÿ��tmp�ĺ�n-start��λ���б������
		strcpy(HC[i], &tmp[start]);//��tmp�ĺ�n-start��Ԫ�طָ�H[i]ָ��ĵ��ַ���
	}
}
int main()
{
	English E;
	Creat_wen(E);//������������ �����ļ��ж����ַ��ļ������ 
	E.M=2*E.n-1;//�����ĳ��� 
	HuffmanTree HT;	
	Create_HuffmanTree(HT,E);
	 open_code();//����� 
	//Print_HuffmanTree(HT,E);//�������� 
	HuffmanCode HC;//HC��n��Ԫ�أ�ÿ��Ԫ����һ��ָ���ַ�����ָ�룬
	//��ÿ��Ԫ����һ��char *�ı���
	Encode_HuffmanCode(HT,E, HC);//Ϊÿ���ַ�������������
	Print_HuffmanCode(HC,E);
	Put(HC,E);
	Get(HT,E);
}
