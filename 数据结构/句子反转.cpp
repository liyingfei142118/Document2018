/*��Ŀ����
����һ�����ӣ�ֻ������ĸ�Ϳո񣩣� �������еĵ���λ�÷�ת�������ÿո�ָ�, ����֮��ֻ��һ���ո�ǰ��û�пո� 
���磺 ��1�� ��hello xiao mi��-> ��mi xiao hello��
��������:
���������ж��飬ÿ��ռһ�У�����һ������(���ӳ���С��1000���ַ�)
�������:
����ÿ������ʾ����Ҫ����������е��ʷ�ת���γɵľ���*/
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
