    //演示程序dp31
    //编译选项:使速度最大化,禁用内联函数扩展
    //编译选项:在静态库中使用MFC（项目属性页->配置属性->常规->MFC的使用）
    //其他编译选项与之前类似
    #include  <stdio.h>
    int  _fastcall  cf211(int x, int y)
    {
        return  (2 * x + 5 * y + 100);
    }
    /////////////////////
    int  main( )
    {
        int  val;
        val = cf211(23, 456);
        printf("val=%d\n", val);
        return  0;
    }
