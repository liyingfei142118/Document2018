/*��Ŀ����
һֻ����Ҫ�Ӻ���������Ӷ԰����Ӻܿ����Ǻ��м���˺ܶ�׮�ӣ�ÿ��һ�׾���һ����
ÿ��׮���϶���һ�����ɣ��������������ϾͿ������ĸ�Զ��ÿ������������ͬ����һ�����ִ�������������
�����������Ϊ5���ʹ��������һ������ܹ���5�ף����Ϊ0���ͻ��ݽ�ȥ�޷�������Ծ��
����һ��N�׿������ʼλ�þ��ڵ�һ���������棬Ҫ�������һ������֮���������ˣ�����ÿ�����ɵ�������
�����������Ҫ�������ܹ�����԰�������޷��������-1
��������:
��������У���һ�������鳤��N (1 �� N �� 10000)���ڶ�����ÿһ���ֵ���ÿո�ָ���
�������:
������ٵ��������޷��������-1
����
5
2 0 1 1 1
���
4*/
#include<iostream>
using namespace std;
int main()
 {
 	int N;
 	cin>>N;
 	int str[10001],count[10001];
 	for(int i=0;i<N;i++)
 		cin>>str[i];
 		count[0]=0;
for(int i=1;i<(N+1);i++)
	count[i]=10001;//��ʼ�����ֵ 
 	for(int i=1;i<=N;i++)//�ӵڶ�λ�ÿ�ʼ 
 	{
 		
 		for(int j=i-1;j>=0;j--)//��i-1λ�ú���ɨ�� 
 		{
 			if(str[j]==0)
 			{
				continue;
		 	}

		 	if(j+str[j]>=i)//j+str[j]��ʾjλ�ÿ�������iλ�ü���� 
			 count[i]=min(count[i],count[j]+1);//ȡ��Сֵ 
		 }
		// cout<<i<<":"<<count[i]<<endl;
	 }
	if(count[N]==10001)
		cout<<"-1"<<endl;
	else
		cout<<count[N]<<endl;
 }
/*#include<iostream>
#include<vector>
using namespace std;
int GetCount(vector<int>& num)
{
    int n = num.size();
    vector<int> dp(n + 1, 10000);
    dp[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = i - 1; j >= 0; j--)
        {
            if (num[j] == 0)
                continue;
            if (j + num[j] >= i)
                dp[i] = min(dp[i], dp[j] + 1);
        }
    }
    if (dp[n] == 10000)
        return -1;
    else
        return dp[n] - 1;
}
 
int main()
{
    int N = 0;
    cin >> N;
    vector<int> num(N,0);
    for (int i = 0; i < N; i++)
        cin >> num[i];
    cout << GetCount(num) << endl;
    return 0;
}*/
