
import java.util.Scanner;  
public class Main {  
    public static void main(String[] args) {  
        Scanner in = new Scanner(System.in);  
        while (in.hasNextInt()) {//注意while处理多个case  
            int a = in.nextInt();  
            int[] stump = new int[a];
            //树桩的所有弹力
            for(int i = 0; i < a; i++){  
                stump[i] = in.nextInt();  
            }  
            //定义一个数组用来记录每到第几米所需要的最少条次数,因为包含0米，
            //而河的宽度是a要跳到第a米，所以需要数组长度为a+1  
            int[] dp = new int[a+1];  
            dp[0] = 0;//跳到第0米只需要跳0次  
            //初始化最小跳次数数组，因为还没哟开始跳，可以设初始值很大  
            for(int i = 1; i < dp.length; i++){  
                dp[i] = 100001;  
            }  
            //依次计算跳到第几米所需要的最小跳的次数，从第1米的树桩开始,到第a米结束 
            for(int i = 1; i <= a; i++){  
                //关键在于如何统计出跳到当前米所需要的最小次数  
                //思路：遍历前边所有这样的节点：跳一次就能跳到当前米的节点，因为前一个树桩的最小跳次数已经确定，
            	//所以就可以筛选出跳到  当前树桩最小跳次数  
                //为什么只要遍历跳一次到当前树桩，而不是2次呢？
            	//因为要到当前树桩，肯定是最后一跳到这里，所以只要统计数能够最后一跳到这里的树桩  
                //就可以了  
                for(int j = i-1; j >= 0; j--){//遍历前面所有树桩，找到能够一跳就能到当前树桩i的树桩位置j  
                    if(stump[j] == 0) continue;//树桩没有用  
                    if(j+stump[j] >= i) dp[i] = Math.min(dp[i], dp[j]+1);
                    //位置j米+弹力stump[j]能够到当前树桩第i米，找到了位置，就更新  
                    //跳到第i米最少条d[i] 
                }  
            }  
            //统计完所有树桩的最小跳次数，答案就出来了  
            if(dp[a] == 100001) System.out.println(-1);  
            else System.out.println(dp[a]);  
        }  
    }  
}  

