    //演示程序dp25
    #include  <stdio.h>
    int  main(  )
    {
        unsigned  char  flag1, flag2, flag3;  //定义3个无符号字节变量
        ;//嵌入汇编_D
        _asm  {
            MOV   AH, 0
            SAHF                    //SF=0，ZF=0，PF=0，AF=0，CF=0
            LAHF                    //把标志寄存器低8位(02H)又回送到AH
            MOV   flag1, AH         //把AH的值保存到变量flag1
            ;
            MOV   DX, 7799H         //DX=7799H
            ADD   DL, DH            //DX=7710H，AF=1，CF=1
            LAHF                    //把标志寄存器低8位(13H)送到AH寄存器
            MOV   flag2, AH         //把AH的值保存到变量flag2
            ;
            SUB   DH, 84H           //DH=F310H，SF=1，CF=1
            CLC                     //CF=0
            LAHF                    //把标志寄存器低8位(86H)送到AH
            MOV   flag3, AH         //把AH的值保存到变量flag3
        }
        printf("flag1=%02XH\n", flag1);  //显示为flag1=02H
        printf("flag2=%02XH\n", flag2);  //显示为flag1=13H
        printf("flag3=%02XH\n", flag3);  //显示为flag1=86H
        return  0;
    }
