import java.util.Scanner;

public class Zf {
	public static void main(String []args)
	{
		Scanner scanner=new Scanner(System.in);
		String s=scanner.nextLine();
		System.out.println(s);
		//int a=s.length();
		//bool k=1;
		while(true)
		{
				int a=s.length();
				//char c[]=new char[2];
				char c=s.charAt(0);
				//c[1]=\0
				s.replaceAll("c","");
				System.out.println(s);
				int b=s.length();
				if(a-b==3)
					{
						System.out.println(c);
						break;
					}
		
		}
	}
}
