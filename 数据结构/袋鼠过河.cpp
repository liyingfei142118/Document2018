/*题目描述
一只袋鼠要从河这边跳到河对岸，河很宽，但是河中间打了很多桩子，每隔一米就有一个，
每个桩子上都有一个弹簧，袋鼠跳到弹簧上就可以跳的更远。每个弹簧力量不同，用一个数字代表它的力量，
如果弹簧力量为5，就代表袋鼠下一跳最多能够跳5米，如果为0，就会陷进去无法继续跳跃。
河流一共N米宽，袋鼠初始位置就在第一个弹簧上面，要跳到最后一个弹簧之后就算过河了，给定每个弹簧的力量，
求袋鼠最少需要多少跳能够到达对岸。如果无法到达输出-1
输入描述:
输入分两行，第一行是数组长度N (1 ≤ N ≤ 10000)，第二行是每一项的值，用空格分隔。
输出描述:
输出最少的跳数，无法到达输出-1
输入
5
2 0 1 1 1
输出
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
	count[i]=10001;//初始化最大值 
 	for(int i=1;i<=N;i++)//从第二位置开始 
 	{
 		
 		for(int j=i-1;j>=0;j--)//从i-1位置后面扫描 
 		{
 			if(str[j]==0)
 			{
				continue;
		 	}

		 	if(j+str[j]>=i)//j+str[j]表示j位置可以跳到i位置及其后 
			 count[i]=min(count[i],count[j]+1);//取最小值 
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
