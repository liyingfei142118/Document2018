/*
题目描述
给定一个英文字符串,请写一段代码找出这个字符串中首先出现三次的那个英文字符(需要区分大小写)。
输入描述:
输入数据一个字符串，包括字母,数字等。
输出描述:
输出首先出现三次的那个英文字符
输入
Have you ever gone shopping and
输出
e
*/

#include <iostream>
#include <string>
using namespace std;
 
int main()
{
    string str;
    getline(cin, str);
    int a[1000] = { 0 };
    for (int i = 0;i<str.size();++i)
    {
        if(str[i]>='a'&&str[i]<='z'||str[i]>='A'&&str[i]<='Z')           
            ++a[str[i]];
        if(a[str[i]]==3)
        {
            printf("%c\n",str[i]);
            break;
        }
    }
    return 0;
}

/*#include<iostream>
#include <map>
using namespace std;
 
int main()
{
    map<char, int> letter;
    char l;
    while (cin >>l)
    {
        if((l>='a'&&l<='z')||l>='A'&&l<='Z')
        {
            ++letter[l];
            if (letter[l] == 3)
            {
            cout << l;
            break;
            }
        }
         
    }
 
    system("pause");
    return 0;
}*/
