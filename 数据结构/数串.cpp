/*//��ʵ����Ǹ��ַ�����ð����������ַ���A+B>B+A��ô��ΪA>B
//�Դ�Ϊ׼�򣬲���ð������ķ������ַ�������С����Ȼ������Ϳ�����
/*����n�������������������ӳ�һ�ţ����һ�����Ķ�λ������
��:n=3ʱ��3������13,312,343,���ɵ��������Ϊ34331213��
��:n=4ʱ,4������7,13,4,246���ӳɵ��������Ϊ7424613��
�ж������������ÿ����������������У���һ��Ϊһ������N��N<=100�����ڶ��а���N����(ÿ����������1000���ո�ֿ�)��*/

#include<iostream>
#include<string>
#include <algorithm>
using namespace std;

#include<vector>
#define max 100

bool Comp(const string& a, const string& b) 
{
    return (a+b) > (b+a);
}
int main()
{
	int n;
	cin>>n;
	vector<string>str;
	for(int i=1;i<=n;i++)
	{
		string temp;
		cin>>temp;
		str.push_back(temp);
	}

sort(str.begin(),str.end(), Comp);
vector<string>::iterator it;
for (it = str.begin(); it != str.end(); it++)
    cout << *it ;
	return 0;
}


/*#include <algorithm>
sort(vec.begin(), vec.end()); //���õ��Ǵ�С���������
//�����Ӵ�С���򣬿��Բ������淴ת������Ҳ���Բ������淽��:
bool Comp(const int& a, const int& b) {
    return a > b;
}
sort(vec.begin(), vec.end(), Comp);*/

/*#include<stdio.h>
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
}*/
