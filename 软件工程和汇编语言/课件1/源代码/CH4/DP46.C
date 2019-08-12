    //演示程序dp46.c
    #include  <stdio.h>
    int  main()
    {
        char  string[100];          //用于存放字符串
        int  len;                   //用于存放字符串长度
        printf("Input string:");    //由用户输入一个字符串
        scanf("%s", string);
        //嵌入汇编代码
        _asm  {
            LEA   EAX, string       //使得EDI指向字符串
            PUSH  EAX
            CALL  STRLEN
            POP   ECX
            MOV   len, EAX
        }
        printf("length=%d\n", len);
        return  0;
        //
        __asm  {
        ;子程序名：STRLEN
        ;功    能：测量字符串长度
        ;入口参数：堆栈传递字符串起始地址偏移
        ;出口参数：EAX= 字符串长度（不包括结束标记）
        ;说    明：设字符串以空（值0）为结束标记
        ;          影响寄存器EAX和ECX
        STRLEN:
            PUSH   EBP
            MOV    EBP, ESP         ;建立堆栈框架
            PUSH   EDI              ;保护寄存器
            MOV    EDI, [EBP+8]     ;取得入口参数
            ;
            XOR    AL, AL           ;AL= 0（字符串结束标记值）
            MOV    ECX, -1          ;假设字符串足够长（0FFFFFFFFH）
            REPNZ  SCASB            ;寻找字符串结束标记
            NOT    ECX
            DEC    ECX              ;至此ECX含字符串长度
                                    ;ECX初值0FFFFFFFFH，所以要减1
            MOV    EAX, ECX         ;准备返回参数
            POP    EDI              ;恢复寄存器
            POP    EBP              ;撤销堆栈框架
            RET
        }
    }
