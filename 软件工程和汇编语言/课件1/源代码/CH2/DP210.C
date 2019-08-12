    //演示程序dp210
    #include <stdio.h>
    int     iarr[5] = {55, 87, -23, 89, 126};                //整型数组
    double  darr[5] = {9.8, 2.77, 3.1415926, 1.414, 1.73278};//双精度浮点数组
    int  main(  )
    {
        int     ival;                 //整型变量
        double  dval;                 //双精度浮点
        //嵌入汇编
        _asm  {
            LEA   EBX, iarr           //把整型数组首元素的有效地址送EBX
            MOV   ECX, 3
            MOV   EDX, [EBX+ECX*4]    //取出iarr的第3个元素
            MOV   ival, EDX
            ;
            LEA   ESI, darr           //把浮点数组首元素的有效地址送ESI
            LEA   EDI, dval           //把变量dval的有效地址送EDI
            MOV   ECX, 2
            MOV   EAX, [ESI+ECX*8]    //取darr的第2个元素的低双字
            MOV   EDX, [ESI+ECX*8+4]  //取darr的第2个元素的高双字
            MOV   [EDI], EAX          //保存低双字
            MOV   [EDI+4], EDX        //保存高双字
        }
        printf("iVAL=%d\n",ival);     //显示为iVAL=89
        printf("dVAL=%.8f\n",dval);   //显示为dVAL=3.14159260
        return  0;
    }
