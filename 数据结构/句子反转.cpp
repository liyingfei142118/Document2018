/*题目描述
给定一个句子（只包含字母和空格）， 将句子中的单词位置反转，单词用空格分割, 单词之间只有一个空格，前后没有空格。 
比如： （1） “hello xiao mi”-> “mi xiao hello”
输入描述:
输入数据有多组，每组占一行，包含一个句子(句子长度小于1000个字符)
输出描述:
对于每个测试示例，要求输出句子中单词反转后形成的句子*/
#include<iostream>
#include<string.h>
using namespace std;
#define max 1001
int main()
{
	char str[max];
	gets(str);
	int length=strlen(str);
	length--;
	int index=length;
	
	for(;length>=0;length--)
	{
		if(str[length]==' ')
		{
			for(int i=length+1;i<=index;i++)
			cout<<str[i];
			cout<<str[length];
			index=length-1;
		}
		if(length==0)
		{
			for(int i=length;i<=index;i++)
			cout<<str[i];
		}
	}
}
/*#include<iostream>
#include<string>
#include <algorithm>
using namespace std;
#include<vector>
int main()
{

	vector<string>str;

		string temp;
		while(cin>>temp) 
		{
			str.push_back(temp);
			if (getchar() == '\n')
   			break;
		}
vector<string>::iterator it;
it=str.begin();
it=it+str.size()-1;
for (; it >= str.begin(); it--)
    cout << *it<<" " ;
	return 0;
}

/*
#include<iostream>
#include<stack>
#include<string>
using namespace std;
int main(){
    string s;
    stack<string> sstack;
    while(cin>>s){
        sstack.push(s);
          if (getchar() == '\n')
   			break;
    }
 while (!sstack.empty()) 
 {
  cout << sstack.top() << " ";
  sstack.pop();
 }
 cout << endl;
    return 0;
}*/
