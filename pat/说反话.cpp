/*给定一句英语，要求你编写程序，将句中所有单词的顺序颠倒输出。
输入格式：测试输入包含一个测试用例，在一行内给出总长度不超过80的字符串。
字符串由若干单词和若干空格组成，
其中单词是由英文字母（大小写有区分）组成的字符串，单词之间用1个空格分开，
输入保证句子末尾没有多余的空格。
输出格式：每个测试用例的输出占一行，输出倒序后的句子。
输入样例：
Hello World Here I Come
输出样例：
Come I Here World Hello*/
#include<stdio.h>  
  
int main()  
{  
    char str[40][80] = {0};            //定义二维数组   
    int i, j;                        //定义自变量   
    int out = 0;  
    int cnt = 0;  
    //为二维数组填充字符串   
    for (i = 0; i < 40; i++)  
    {  
        for (j = 0; j < 80; j++)  
        {  
            scanf("%c", &str[i][j]);  
            if (' ' == str[i][j])  
            {  
                str[i][j] = '\0';  
                cnt++;  
                break;  
            }  
            if ('\n' == str[i][j])  
            {  
                str[i][j] = '\0';  
                out = 1;   
                break;  
            }      
        }  
        if (out)  
            break;  
    }      
       
    //输出字符   
    while (cnt >= 0)  
    {  
        if (cnt > 0)  
            printf("%s ", str[cnt]);  
        else  
            printf("%s", str[cnt]);      
        cnt--;      
    }  
    printf("\n");  
       
    return 0;  
}  
