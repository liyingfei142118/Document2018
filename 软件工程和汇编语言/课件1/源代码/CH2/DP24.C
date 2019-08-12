    //演示程序dp24
    #include  <stdio.h>
    int  main(  )
    {
        int  varx, vary;                //定义变量
        int  varz;
        ;
        printf("input:varx,vary:");
        scanf("%d,%d",&varx, &vary);    //输入
        //嵌入汇编
        _asm {
            MOV    EDX, varx       ;把存储单元varx的值送到寄存器EDX
            ADD    EDX, vary       ;把存储单元vary的值加上EDX值送到EDX
            MOV    varz, EDX       ;把EDX的值送到存储单元varz中
        }
        printf("varz=%d\n", varz);      //输出
        return  0;
    }
