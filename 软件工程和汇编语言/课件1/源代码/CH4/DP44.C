    //演示程序dp44.c
    #include  <stdio.h>
    int  main()
    {
        char  string[] ="0123456789ABCDEFabcdef";
        char  varch= '%';               //用于保存其他方式输入的字符
        int  flag;                      //反映是否为十六进制数符号
        //
        _asm  {
            MOV   AL, varch             ;把要判断的字符送AL
            MOV   ECX, 22               ;合计22个十六进制数符号
            LEA   EDI, string
        NEXT:
            SCASB                       ;//@1
            LOOPNZ  NEXT                ;没有找遍且没有找到，继续找 //@2
            JNZ   NOT_FOUND             ;没有找到
        FOUND:                          ;找到，字符是十六进制数符号
            MOV   flag, 1
            JMP   SHORT  OVER
        NOT_FOUND:                      ;字符不是十六进制数符号
            MOV   flag, 0
        OVER:
        }
        printf("flag=%d\n", flag);      //显示为flag=0
        return  0;
    }
