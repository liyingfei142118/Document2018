/*题目描述
酒店房间的价格录入是通过时间段来录入的，比如10月1日至10月7日800元，
10月8日至10月20日500元，请实现以下函数int[][] merge(int[][] dateRangePrices)，
输入是某个酒店多个日期段的价格，每个日期段（终止日期大于等于起始日期）和对应的价格使用长度为3的数组来表示，
比如[0, 19, 300], [10, 40, 250]分别表示从某天开始第1天到第20天价格都是300，第11天到第41天价格都是250，
这些日期端有可能重复，重复的日期的价格以后面的为准， 请以以下规则合并并输出合并结果：
1.相邻两天的价格如果相同，那么这两个日期段应该合并
2.合并的结果应该以起始日期从小到大排序
输入描述:
输入数据包括多行，如样例输入所示。
输出描述:
输出数据为一行，如样例输出所示
输入
1 1 100
2 3 100
4 5 110
输出
[1, 3, 100],[4, 5, 110]*/
/*题目描述
Please create a function to extract the filename extension from the given path,
return the extracted filename extension or null if none.
输入描述:
输入数据为一个文件路径
输出描述:
对于每个测试实例，要求输出对应的filename extension
示例1
输入
Abc/file.txt
输出
txt*/
#include<iostream>
using namespace std;
#define max 10000
int main()
{
	 
}
