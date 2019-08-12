    //演示程序dp216
    #include  <stdio.h>
    int  main( )
    {
        int  varsp1, varsp2, varsp3, varsp4, varsp5;  //用于存放ESP值
        int  varr1, varr2;                            //用于存放EBX值
        //嵌入汇编
        _asm {
            MOV   EAX, 12345678H    //初值
            MOV   varsp1, ESP       //保存演示之初的ESP（假设为0013FA74H）
            ;
            PUSH  EAX               //把EAX压入堆栈
            MOV  varsp2, ESP        //保存当前ESP（0013FA70H）
            ;
            PUSH  AX                //把AX压入堆栈
            MOV   varsp3, ESP       //保存当前ESP（0013FA6EH）
            ;
            POP   EBX               //从堆栈弹出双字到EBX
            MOV   varsp4, ESP       //保存当前ESP（0013FA72H）
            MOV   varr1, EBX
            ;
            POP   BX                //从堆栈弹出字到BX
            MOV   varsp5, ESP       //保存当前ESP（0013FA74H）
            MOV   varr2, EBX
        }
        printf("ESP1=%08XH\n",varsp1);  //显示为ESP1=0013FA74H
        printf("ESP2=%08XH\n",varsp2);  //显示为ESP2=0013FA70H
        printf("ESP3=%08XH\n",varsp3);  //显示为ESP3=0013FA6EH
        printf("ESP4=%08XH\n",varsp4);  //显示为ESP4=0013FA72H
        printf("ESP5=%08XH\n",varsp5);  //显示为ESP5=0013FA74H
        printf("EBX1=%08XH\n",varr1);   //显示为EBX1=56785678H
        printf("EBX2=%08XH\n",varr2);   //显示为EBX2=56781234H
        return  0;
    }
