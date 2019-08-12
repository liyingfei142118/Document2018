    //演示程序dp22
    #include  <stdio.h>
    int  main(  )
    {
        int  var1, var2, var3;        //定义3个变量
        ;//嵌入汇编
        _asm  {
            MOV   EDX, 11119950H
            INC   EDX
            MOV   var1, EDX           //把寄存器EDX的值保存到变量var1中
            MOV   CX, 8765H
            DEC   CX
            ADD   DX, CX
            MOV   var2, EDX           //把寄存器EDX的值保存到变量var2中
            SUB   DL, 76H
            MOV   var3, EDX           //把寄存器EDX的值保存到变量var3中
        }
        printf("EDX1=%08XH\n",var1);  //显示为EDX1=11119951H
        printf("EDX2=%08XH\n",var2);  //显示为EDX2=111120B5H
        printf("EDX3=%08XH\n",var3);  //显示为EDX3=1111203FH
        return  0;
    }
