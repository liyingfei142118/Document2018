    //演示程序dp27
    #include <stdio.h>
    int   vari = 0x12345678;        //定义整型变量。设有效地址为x
    char  buff[] = "ABCDE";         //定义字符数组。设首元素有效地址为y
    int  main(  )
    {
        int  dv1, dv2, dv3, dv4;    //定义4个整型变量
        //嵌入汇编
        _asm  {
            LEA   EBX, vari         //把变量vari的有效地址x送到EBX
            MOV   EAX, [EBX]        //把有效地址为x的双字(12345678H)送到EAX
            MOV   dv1, EAX
            MOV   EAX, [EBX+1]      //把有效地址为x+1的双字(41123456H)送到EAX
            MOV   dv2, EAX
            ;
            MOV   ECX, 2
            MOV   AX, [EBX+ECX]     //把有效地址为x+2的字(1234H)送到AX
            MOV   dv3, EAX
            ;
            MOV   AL, [EBX+ECX*2+3] //把有效地址为x+7的字节(44H)送到AL
            MOV   dv4, EAX
        }
        printf("dv1=%08XH\n",dv1);   //显示为dv1=12345678H
        printf("dv2=%08XH\n",dv2);   //显示为dv2=41123456H
        printf("dv3=%08XH\n",dv3);   //显示为dv3=41121234H
        printf("dv4=%08XH\n",dv4);   //显示为dv4=41121244H
        return  0;
    }
