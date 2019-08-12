    //演示程序dp57.c
    #include  <stdio.h>
    int  main( )
    {
        int  dvar=3, *pi;
        char *fmts = "%d\n";
        pi = &dvar;
        printf(fmts, *pi);              //显示pi所指向变量的值
        printf(fmts, pi);               //显示pi自身的值
        return  0;
    }
