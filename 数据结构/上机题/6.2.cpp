#include<iostream>
using namespace std;
#define max 100
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define N 4//��Ȩֵ��Ҷ�ӽڵ�����������Ҫ������ַ���
#define M 2*N-1//n��Ҷ�ӽڵ㹹��Ĺ���������2n-1�����
#define MAX 10000
typedef char TElemType;
//��̬��������洢�ṹ
typedef struct{
	int weight;//Ȩֵֻ��������
	int parent;
	int lchild;
	int rchild;
}HTNode;//, *HuffmanTree;
typedef HTNode HuffmanTree[M+1];//0�ŵ�Ԫ��ʹ��
void select(HuffmanTree HT, int k, int &s1, int &s2);
typedef char * HuffmanCode[N+1];//�洢ÿ���ַ��Ĺ����������
//��һ���ַ�ָ�����飬ÿ������Ԫ����ָ���ַ�ָ���ָ��
//�����������
void createHuffmanTree(HuffmanTree &HT, int *w, int n)
{
	if(n <= 1)
		return;
	//��������ֵ
	for(int i = 1; i <= n; i++){//HTǰn�������洢Ҷ�ӽڵ㣬���Ǿ�����Ȩֵ
		HT[i].weight = w[i];
		HT[i].lchild = 0;
		HT[i].parent = 0;
		HT[i].rchild = 0;
	}
	for(int i=n+1; i <=M; i++){//HT��m-n�������洢�м��㣬���һ��������Ȼ���������ĸ��ڵ�
		HT[i].weight = 0;
		HT[i].lchild = 0;
		HT[i].parent = 0;
		HT[i].rchild = 0;
	}
	//��ʼ��������������������HT�ĺ�m-n�����Ĺ��̣�ֱ�����������ڵ㡣�ù������㷨
	for(int i = n+1; i <= M; i++){
		int s1, s2;
		select(HT, i-1, s1, s2);//��HT[1...i-1]��ѡ��parentΪ0����Ȩֵ��С��2��㣬����ŷֱ�Ϊs1,s2��parent��Ϊ0˵���ý���Ѿ����빹���ˣ��ʲ����ٿ���
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
}
//��HT[1...k]��ѡ��parentΪ0����Ȩֵ��С��2��㣬����ŷֱ�Ϊs1,s2��parent��Ϊ0˵���ý���Ѿ����빹���ˣ��ʲ����ٿ���
void select(HuffmanTree HT, int k, int &s1, int &s2){
	//����s1��Ӧ��Ȩֵ����<=s2��Ӧ��Ȩֵ
 int tmp = MAX, tmpi = 0;
	for(int i = 1; i <= k; i++)
	{
		if(!HT[i].parent){//parent����Ϊ0
			if(tmp > HT[i].weight)
			{
				tmp = HT[i].weight;//tmp���Ϊ��С��weight
				tmpi = i;
			}
		}
	}
	s1 = tmpi;	
	tmp = MAX;
	tmpi = 0;
	for(int i = 1; i <= k; i++)
	{
		if((!HT[i].parent) && i!=s1)
		{//parentΪ0
			if(tmp > HT[i].weight)
			{
				tmp = HT[i].weight;
				tmpi = i;
			}
		}
	}
	s2 = tmpi;
}
//��ӡ����������
void printHuffmanTree(HuffmanTree HT, char ch[]){
	printf("\n");
	printf("data, weight, parent, lchild, rchild\n");
	for(int i = 1; i <= M; i++){
		if(i > N){
			printf("  -, %5d, %5d, %5d, %5d\n", HT[i].weight, HT[i].parent, HT[i].lchild, HT[i].rchild);
		}else{
			printf("  %c, %5d, %5d, %5d, %5d\n", ch[i], HT[i].weight, HT[i].parent, HT[i].lchild, HT[i].rchild);
		}
	}
	printf("\n");
}
//Ϊÿ���ַ������������룬��Ҷ�ӵ����������ÿ���ַ��Ĺ���������
void encodingHuffmanCode(HuffmanTree HT, HuffmanCode &HC){
	//char *tmp = (char *)malloc(n * sizeof(char));//��ÿһ���ַ���Ӧ�ı��������ʱ�����ռ�tmp�ÿ���ַ��ı��볤�Ȳ��ᳬ��n
	char tmp[N];
	tmp[N-1] = '\0';//����Ľ�����
	int start, c, f;
	for(int i = 1; i <= N; i++)
	{//���ڵ�i���������ַ�����i����Ȩֵ��Ҷ�ӽڵ�
		start = N-1;//���������Ժ�start��ָ��������ʼλ��
		c = i;
		f = HT[i].parent;

		while(f){//f!=0,��f���Ǹ��ڵ�ĸ��ڵ�
			if(HT[f].lchild == c)
			{
				tmp[--start] = '0';
			}
			else{//HT[f].rchild == c,ע��:���ڹ���������ֻ����Ҷ�ӽڵ�Ͷ�Ϊ2�Ľڵ㣬���Գ���Ҷ�ӽڵ㣬�ڵ�һ��������2����֧
				tmp[--start] = '1';
			}
			c = f;
			f = HT[f].parent;
		}
		HC[i] = (char *)malloc((N-start)*sizeof(char));//ÿ��tmp�ĺ�n-start��λ���б������
		strcpy(HC[i], &tmp[start]);//��tmp�ĺ�n-start��Ԫ�طָ�H[i]ָ��ĵ��ַ���
	}
}
//��ӡ�����������������������Ժ��Ժ�Ϳ��Զ��ַ������б����ˣ�ֻҪ��Ӧ��������ת������ 

//��ӡ�����������
void printHuffmanCoding(HuffmanCode HC, char ch[]){
	printf("\n");
	for(int i = 1; i <= N; i++){
		printf("%c:%s\n", ch[i], HC[i]);
	}
	printf("\n");
}
//������̣��ӹ��������ĸ��ڵ���������ַ�'0'��'1'ȷ���������ӻ��Һ��ӣ�ֱ���ҵ�Ҷ�ӽڵ㼴�ɣ�����ø��ִ���Ӧ���ַ�
void decodingHuffmanCode(HuffmanTree HT, char *ch, char testDecodingStr[], int len, char *result){
	int p = M;//HT�����һ���ڵ��Ǹ��ڵ㣬ǰn���ڵ���Ҷ�ӽڵ�
	int i = 0;//ָʾ���Դ��еĵ�i���ַ�
	//char result[30];//�洢�����Ժ���ַ���
	int j = 0;//ָʾ������еĵ�j���ַ�
	while(i<len){
		if(testDecodingStr[i] == '0'){
			p = HT[p].lchild;
		}
		if(testDecodingStr[i] == '1'){
			p = HT[p].rchild;
		}

		if(p <= N){//p<=N�����pΪҶ�ӽڵ�,��Ϊ�ڹ����������HTʱ��HT��m���ڵ���ǰn���ڵ�ΪҶ�ӽڵ�
			result[j] = ch[p];
			j++;
			p = M;//p����ָ����ڵ�
		}
		i++;
	}
	result[j] = '\0';//������Ľ�����	
}
int main()
{
	HuffmanTree HT;
	
	TElemType ch[N+1];//0�ŵ�Ԫ��ʹ�ã��洢n���ȴ�������ַ�
	int w[N+1];//0�ŵ�Ԫ��ʹ�ã��洢n���ַ���Ӧ��Ȩֵ
	printf("������%d���ַ��Լ����ַ���Ӧ��Ȩֵ(��:a,20):\n", N);
	for(int i = 1; i <= N; i++){
		scanf("%c,%d", &ch[i], &w[i]);
		getchar();//�Ե����з�
	}//��w���i��Ȩֵ��Ӧ����ch���i���ַ�Ԫ��


	createHuffmanTree(HT, w , N);//������������
	printHuffmanTree(HT, ch);
	
	HuffmanCode HC;//HC��n��Ԫ�أ�ÿ��Ԫ����һ��ָ���ַ�����ָ�룬
	//��ÿ��Ԫ����һ��char *�ı���
	encodingHuffmanCode(HT, HC);//Ϊÿ���ַ�������������
	printHuffmanCoding(HC, ch);

	//�������������abaccda----01000101101110
	char * testDecodingStr = "01000101101110";
	int testDecodingStrLen = 14;
	printf("����%s��Ӧ���ַ����ǣ�", testDecodingStr);
	char result[30];//�洢�����Ժ���ַ���
	decodingHuffmanCode(HT, ch, testDecodingStr, testDecodingStrLen, result);//���루���룩��ͨ��һ�θ����ı��뷭��ɶ�Ӧ���ַ���
	printf("%s\n", result);
	return 0;
}
