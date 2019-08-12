    //演示程序dp338.c
    #include  <stdio.h>
    int  subr_addr;                     //用于存放子程序入口地址
    int  valu;                          //用于保存结果
    int  main( )
    {
        _asm  {
            LEA    EDX, SUBR2           //取得子程序二的入口地址
            MOV    subr_addr, EDX       //保存到存储单元
            ;
            LEA    EDX, SUBR1           //取得子程序一的入口地址
            XOR    EAX, EAX             //入口参数EAX=0
            CALL   EDX                  //调用子程序一（段内间接调用）
            ;
            CALL   subr_addr            //调用子程序二（段内间接调用）
            ;
            MOV   valu, EAX
        }
        printf("valu=%d\n",valu);       //显示为valu=28
        return  0;
        //
        _asm  {                         //嵌入汇编代码
        SUBR1:                          //示例子程序一
            ADD   EAX, 8
            RET                         //返回
            ;
        SUBR2:                         //示例子程序二
            ADD   EAX, 20
            RET                        //返回
        }
    }
