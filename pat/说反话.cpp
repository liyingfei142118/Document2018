/*����һ��Ӣ�Ҫ�����д���򣬽��������е��ʵ�˳��ߵ������
�����ʽ�������������һ��������������һ���ڸ����ܳ��Ȳ�����80���ַ�����
�ַ��������ɵ��ʺ����ɿո���ɣ�
���е�������Ӣ����ĸ����Сд�����֣���ɵ��ַ���������֮����1���ո�ֿ���
���뱣֤����ĩβû�ж���Ŀո�
�����ʽ��ÿ���������������ռһ�У���������ľ��ӡ�
����������
Hello World Here I Come
���������
Come I Here World Hello*/
#include<stdio.h>  
  
int main()  
{  
    char str[40][80] = {0};            //�����ά����   
    int i, j;                        //�����Ա���   
    int out = 0;  
    int cnt = 0;  
    //Ϊ��ά��������ַ���   
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
       
    //����ַ�   
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
