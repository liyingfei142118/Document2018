    //演示程序dp33
    //编译选项:使速度最大化,禁用内联函数扩展
    //其他编译选项与之前类似
    #include  <stdio.h>
    //示例函数cf34
    int  cf34(int x, int y)
    {
        return  (2 * x + 5 * y + 100);
    }
    /////////////////////////
    int  main( )
    {
        int  val;
        val = cf34(23, 456);
        printf("val=%d\n", val);
        return  0;
    }
