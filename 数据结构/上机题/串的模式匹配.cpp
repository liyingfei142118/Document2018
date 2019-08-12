#include <stdio.h> 
#include <stdlib.h>
 #include <string.h>
  #define STRING_INIT_SIZE 100 //串初始长度
   int Index(char *S, char *T, int pos)
   { //返回字串T在主串S中第pos个字符之后的位置。若不存在，则函数值为0. //其中，T非空，1<=pos<=StrLength(s). 
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
{ //求模式串T的next函数值并存入数组next。
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
{ //利用模式串T的next函数求T在主串S中第pos个字符之后的位置的KMP算法，其中T非空，1<=pos<=StrLength(S).
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
	int s; //数组内数据存储格式：
		 //{[元素0:串的长度],[元素1:第1个字符],[元素2:第2个字符],[元素3:第3个字符]……} 
	 printf("请输入主串："); 
	 gets(S + 1); //从[1]单元开始存放串 *S = strlen(S + 1); 
		 //将串的长度保存至[0]单元
	 printf("请输入子串：");
	 gets(T + 1); 
	*T = strlen(T + 1);
	 printf("开始匹配的位置："); 
	 scanf("%d",&s); 
	 s = Index(S, T, s); 
		   //使用普通方式匹配 
	printf("子串的位置(普通)：%d\n",s);
	s = Index_KMP(S, T, s); 
			//使用改进方式匹配
	 printf("子串的位置(改进)：%d\n",s);
	system("pause"); 
}

