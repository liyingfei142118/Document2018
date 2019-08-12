#include<iostream>
using namespace std;
#include<malloc.h>
#include<stdlib.h>
#include<string.h>
#define N 8//��Ȩֵ��Ҷ�ӽڵ�����������Ҫ������ַ���
#define M 2*N-1//n��Ҷ�ӽڵ㹹��Ĺ���������2n-1�����
#define MAX 10000

//��̬��������洢�ṹ
typedef struct{
	int weight;//Ȩֵֻ��������
	int parent;
	int lchild;
	int rchild;
}HTNode;
typedef HTNode HuffmanTree[M+1];//0�ŵ�Ԫ��ʹ��

//��HT[1...k]��ѡ��parentΪ0����Ȩֵ��С��2��㣬����ŷֱ�Ϊs1,s2��parent��Ϊ0˵���ý���Ѿ����빹���ˣ��ʲ����ٿ���
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
void Create_HuffmanTree(HuffmanTree &HT, int *w, int n)
{
	if(n <= 1)
		return;
	//��������ֵ
	for(int i = 1; i <= n; i++)//HTǰn�������洢Ҷ�ӽڵ㣬���Ǿ�����Ȩֵ
	{
		HT[i].weight = w[i];
		HT[i].lchild = 0;
		HT[i].parent = 0;
		HT[i].rchild = 0;
	}
	for(int i=n+1; i <=M; i++)//HT��m-n�������洢�м��㣬���һ��������Ȼ���������ĸ��ڵ�
	{
		HT[i].weight = 0;
		HT[i].lchild = 0;
		HT[i].parent = 0;
		HT[i].rchild = 0;
	}
	//��ʼ��������������������HT�ĺ�m-n�����Ĺ��̣�ֱ�����������ڵ㡣�ù������㷨
	for(int i = n+1; i <= M; i++)
	{
		int s1, s2;
		select(HT, i-1, s1, s2);
//��HT[1...i-1]��ѡ��parentΪ0����Ȩֵ��С��2��㣬����ŷֱ�Ϊs1,s2��
//parent��Ϊ0˵���ý���Ѿ����빹���ˣ��ʲ����ٿ���
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
}
typedef char * HuffmanCode[N+1];//�洢ÿ���ַ��Ĺ����������
//��һ���ַ�ָ�����飬ÿ������Ԫ����ָ���ַ�ָ���ָ��
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
	//char *tmp = (char *)malloc(n * sizeof(char));//��ÿһ���ַ���Ӧ�ı��������ʱ�����ռ�tmp�
	//ÿ���ַ��ı��볤�Ȳ��ᳬ��n
	char tmp[N];
	tmp[N-1] = '\0';//����Ľ�����
	int start, c, f;
	for(int i = 1; i <= N; i++)
	{//���ڵ�i���������ַ�����i����Ȩֵ��Ҷ�ӽڵ�
		start = N-1;//���������Ժ�start��ָ��������ʼλ��
		c = i;
		f = HT[i].parent;

		while(f)
		{//f!=0,��f���Ǹ��ڵ�ĸ��ڵ�
			if(HT[f].lchild == c)
			{
				tmp[start] = '0';
				start--;
			}
			else{//HT[f].rchild == c,ע��:���ڹ���������ֻ����Ҷ�ӽڵ�Ͷ�Ϊ2�Ľڵ㣬���Գ���Ҷ�ӽڵ㣬�ڵ�һ��������2����֧
				tmp[start] = '1';
				start--;
			}
			c = f;
			f = HT[f].parent;
		}
		HC[i] = (char *)malloc((N-start)*sizeof(char));//ÿ��tmp�ĺ�n-start��λ���б������
		strcpy(HC[i], &tmp[start]);//��tmp�ĺ�n-start��Ԫ�طָ�H[i]ָ��ĵ��ַ���
	}
}
//��ӡ�����������������������Ժ��Ժ�Ϳ��Զ��ַ������б����ˣ�ֻҪ��Ӧ��������ת������ 
typedef char * HuffmanCode[N+1];//�洢ÿ���ַ��Ĺ����������
//��һ���ַ�ָ�����飬ÿ������Ԫ����ָ���ַ�ָ���ָ��
int main()
{
	HuffmanTree HT;	
	char ch[N+1];//0�ŵ�Ԫ��ʹ�ã��洢n���ȴ�������ַ�
	int w[N+1];//0�ŵ�Ԫ��ʹ�ã��洢n���ַ���Ӧ��Ȩֵ
	
	cout<<"������N���ַ��Լ����ַ���Ӧ��Ȩֵ:"<<endl;
	for(int i = 1; i <= N; i++){
		cin>>ch[i]>>w[i];
	}//��w���i��Ȩֵ��Ӧ����ch���i���ַ�Ԫ��
	Create_HuffmanTree(HT, w , N);//������������
	Print_HuffmanTree(HT, ch);
	
	HuffmanCode HC;//HC��n��Ԫ�أ�ÿ��Ԫ����һ��ָ���ַ�����ָ�룬
	//��ÿ��Ԫ����һ��char *�ı���
	Encode_HuffmanCode(HT, HC);//Ϊÿ���ַ�������������
	Print_HuffmanCode(HC, ch);
	return 0;
}
