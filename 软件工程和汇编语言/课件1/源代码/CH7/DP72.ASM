    ;演示程序dp72.asm
        SECTION  TEXT
        BITS  16                    ;16位代码模式
        ORG   100H                  ;COM类型可执行程序
    Begin:
        PUSH  CS
        POP   DS                    ;DS=CS
        MOV   SI, Hello             ;SI=字符串首地址
        MOV   DL, [CurCol]          ;DL=光标列号
        MOV   AL, [SI]              ;取得待显示字符
    Lab1:
        MOV   DI, [Count]           ;行数（内循环的计数）
        MOV   DH, [CurLin]          ;DH=光标行号
        MOV   BL, [Color]           ;BL=显示属性初值
        ;
        MOV   BH, 0                 ;在第0页显示
        MOV   CX, 1                 ;显示1个字符
    Lab2:
        MOV   AH, 2
        INT   10H                   ;设置光标位置
        ;
        MOV   AH, 9
        INT   10H                   ;显示字符（AL）
        ;
        INC   DH                    ;调整光标的行
        INC   BL                    ;调整显示属性
        DEC   DI                    ;行数减1
        JNZ   Lab2                  ;不为0，继续下一行
        ;
        INC   DL                    ;调整光标的列
        INC   SI                    ;指向下一个待显示字符
        MOV   AL, [SI]              ;取得待显示字符
        OR    AL, AL                ;字符串结束标志？
        JNZ   Lab1                  ;否，继续显示
        ;
        MOV   DH, 19
        MOV   DL, 0
        MOV   AH, 2
        INT   10H                   ;重新设置光标到位置（19,0）
        ;
        mov   ah, 4ch               ;调用DOS功能，结束程序
        int   21h
    ;------------
    Hello   db    "Hello,world",0   ;显示信息
    CurLin  db    5                 ;起始光标行号
    CurCol  db    8                 ;起始光标列号
    Color   db    0x07              ;每行起始显示属性
    Count   dw    6                 ;行数
