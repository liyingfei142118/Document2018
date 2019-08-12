/*题目描述
春天是鲜花的季节，水仙花就是其中最迷人的代表，数学上有个水仙花数，
他是这样定义的： “水仙花数”是指一个三位数，它的各位数字的立方和等于其本身，比如：153=1^3+5^3+3^3。
 现在要求输出所有在m和n范围内的水仙花数。
输入描述:
输入数据有多组，每组占一行，包括两个整数m和n（100 ≤ m ≤ n ≤ 999）。*/
import java.util.Scanner;
public class Falower {
	public static void main(String [] args)
	{
		Scanner s=new Scanner(System.in);
		try {
		int m=s.nextInt();
		int n=s.nextInt();
		for(int i=m;i<=n;i++)
		{
			int count,temp,m1;

			int j=3;
			m1=i;
			count=0;
			while(j>0)
			{
				temp=m1%10;
				m1=m1/10;
				count+=(temp*temp*temp);
				j--;
			}
			if(count==i)
				System.out.println(i);
		}
		}
		finally
		{
			s.close();
		}
	}
}
