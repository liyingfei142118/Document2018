/*��Ŀ����
�������ʻ��ļ��ڣ�ˮ�ɻ��������������˵Ĵ�����ѧ���и�ˮ�ɻ�����
������������ģ� ��ˮ�ɻ�������ָһ����λ�������ĸ�λ���ֵ������͵����䱾�����磺153=1^3+5^3+3^3��
 ����Ҫ�����������m��n��Χ�ڵ�ˮ�ɻ�����
��������:
���������ж��飬ÿ��ռһ�У�������������m��n��100 �� m �� n �� 999����*/
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
