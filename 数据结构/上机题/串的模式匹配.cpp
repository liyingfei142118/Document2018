#include <stdio.h> 
#include <stdlib.h>
 #include <string.h>
  #define STRING_INIT_SIZE 100 //����ʼ����
   int Index(char *S, char *T, int pos)
   { //�����ִ�T������S�е�pos���ַ�֮���λ�á��������ڣ�����ֵΪ0. //���У�T�ǿգ�1<=pos<=StrLength(s). 
   int i = pos; 
   int j = 1; 
   while (i <= S[0] && j <= T[0])
   {
    	if (S[i++] != T[j++])
		{ 
			i = i - j + 2;
	 		j = 1; 
	
	 	} 
 	} 
	 return (j > T[0]) ? i - T[0] : -1;
 }
int get_next(char *T, int next[] )
{ //��ģʽ��T��next����ֵ����������next��
 	int i = 1, j = 0;
  	next[1] = 0; 
  while (i<T[0])
  { 
  	if (j == 0 || T[i] == T[j]) 
  		next[++i] = ++j; 
  	else 
	  j = next[j]; 
  }
   return *next;
 } 
int Index_KMP(char *S, char *T, int pos)	
{ //����ģʽ��T��next������T������S�е�pos���ַ�֮���λ�õ�KMP�㷨������T�ǿգ�1<=pos<=StrLength(S).
	int next[100];
	*next = get_next(T, next); 
	int j = 1, i = pos; 
	while (i <= S[0] && j <= T[0])
	{ 
	if (j == 0 || S[i] == T[j])
	   { 
	   	++i; ++j;
	    } 	
		else j = next[j]; 
		}
	    return (j > T[0]) ? i - T[0] : -1;
 } 
int main()
{ 
	char S[STRING_INIT_SIZE],T[STRING_INIT_SIZE]; 
	int s; //���������ݴ洢��ʽ��
		 //{[Ԫ��0:���ĳ���],[Ԫ��1:��1���ַ�],[Ԫ��2:��2���ַ�],[Ԫ��3:��3���ַ�]����} 
	 printf("������������"); 
	 gets(S + 1); //��[1]��Ԫ��ʼ��Ŵ� *S = strlen(S + 1); 
		 //�����ĳ��ȱ�����[0]��Ԫ
	 printf("�������Ӵ���");
	 gets(T + 1); 
	*T = strlen(T + 1);
	 printf("��ʼƥ���λ�ã�"); 
	 scanf("%d",&s); 
	 s = Index(S, T, s); 
		   //ʹ����ͨ��ʽƥ�� 
	printf("�Ӵ���λ��(��ͨ)��%d\n",s);
	s = Index_KMP(S, T, s); 
			//ʹ�øĽ���ʽƥ��
	 printf("�Ӵ���λ��(�Ľ�)��%d\n",s);
	system("pause"); 
}

