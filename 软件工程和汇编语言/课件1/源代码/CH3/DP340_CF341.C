    //演示程序dp340.c
    //编译选项:使速度最大化,禁用内联函数扩展,使用标准Windows库
    #include  <stdio.h>
    //示例函数cf341
    int  _stdcall  cf341(int x, int y)
    {
        return  (2 * x + 5 * y + 100);
    }
    //
    int  main( )
    {
        int  val;
        val = cf341(23, 456);
        printf("val=%d\n", val);
        return  0;
    }
