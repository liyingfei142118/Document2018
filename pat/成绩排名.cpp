/*����n��ѧ����������ѧ�š��ɼ����ֱ�����ɼ���ߺͳɼ����ѧ����������ѧ�š�
�����ʽ��ÿ�������������1��������������ʽΪ
  ��1�У�������n
  ��2�У���1��ѧ�������� ѧ�� �ɼ�
  ��3�У���2��ѧ�������� ѧ�� �ɼ�
  ... ... ...
  ��n+1�У���n��ѧ�������� ѧ�� �ɼ�
����������ѧ�ž�Ϊ������10���ַ����ַ������ɼ�Ϊ0��100֮���һ��������
���ﱣ֤��һ�����������û������ѧ���ĳɼ�����ͬ�ġ�
�����ʽ����ÿ�������������2�У���1���ǳɼ����ѧ����������ѧ�ţ�
��2���ǳɼ����ѧ����������ѧ�ţ��ַ�������1�ո�
����������
3
Joe Math990112 89
Mike CS991301 100
Mary EE990830 95
���������
Mike CS991301
Joe Math990112
*/
#include<iostream>
using namespace std;
typedef struct
{
	char name[11];
	char ID[11];
	int grad;
}student;
int main()
{
	int n;
	cin>>n;
	student stu[n+1];
	int max=0,m,min=100,n1;
	for(int i=1;i<=n;i++)
	{
			cin>>stu[i].name;
			cin>>stu[i].ID;
			cin>>stu[i].grad;
		if(stu[i].grad>max)
		{
			max=stu[i].grad;
			m=i;
		}
		if(stu[i].grad<min)
		{
			min=stu[i].grad;
			n1=i;
		}	
	}
	cout<<stu[m].name<<" "<<stu[m].ID<<endl;
	cout<<stu[n1].name<<" "<<stu[n1].ID<<endl;
}
