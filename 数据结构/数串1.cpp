//其实这就是个字符串的冒泡排序，如果字符串A+B>B+A那么认为A>B
//以此为准则，采用冒泡排序的方法将字符串按大小排序，然后输出就可以了
/*设有n个正整数，将他们连接成一排，组成一个最大的多位整数。
如:n=3时，3个整数13,312,343,连成的最大整数为34331213。
如:n=4时,4个整数7,13,4,246连接成的最大整数为7424613。
有多组测试样例，每组测试样例包含两行，第一行为一个整数N（N<=100），第二行包含N个数(每个数不超过1000，空格分开)。*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
    int i,j;
    int num=0;
    char data[100][5]={'\0'};
    char tempa[7]={'\0'},tempb[7]={'\0'},temp[5]={'\0'};
    scanf("%d",&num);
    for(i=0;i<num;i++)
    {
        scanf("%s",data[i]);
    }
    strcpy(temp,data[0]);
    for(i=0;i<num;i++)
    {
        for(j=i+1;j<num;j++)
        {
            strcpy(tempa,data[i]);
            strcat(tempa,data[j]);
            
            strcpy(tempb,data[j]);         
            strcat(tempb,data[i]);
            
            if(strcmp(tempa,tempb)<0)
            {
                strcpy(temp,data[j]);
                strcpy(data[j],data[i]);
                strcpy(data[i],temp);
            }
        }
        printf("%s",data[i]);
    }
    system("pause");
    return 0;
}