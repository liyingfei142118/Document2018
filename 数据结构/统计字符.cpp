/*
��Ŀ����
����һ��Ӣ���ַ���,��дһ�δ����ҳ�����ַ��������ȳ������ε��Ǹ�Ӣ���ַ�(��Ҫ���ִ�Сд)��
��������:
��������һ���ַ�����������ĸ,���ֵȡ�
�������:
������ȳ������ε��Ǹ�Ӣ���ַ�
����
Have you ever gone shopping and
���
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
