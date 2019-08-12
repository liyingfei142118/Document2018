        ;演示程序dp64.asm
        segment   code              ;声明段code开始
        org    100H                 ;现在以100H作为段内偏移
        JMP    begin                ;跳转到begin处
    keyval     db    0              ;
    keytab     db    "DdHhOoQq"     ;有效字符串
    KEYLEN     equ   $ - keytab     ;符号常量（有效字符串长度）
    prompt     db    "select(DHOQ): $"
    newline    db    0DH, 0AH, 24H
    ;
    entrytab   dw    SUBDD, SUBHH, SUBQQ, SUBQQ    ;子程序入口地址表
    ;
    begin:
        MOV    AX, CS
        MOV    DS, AX               ;数据段同代码段
        MOV    ES, AX               ;附加段同代码段
        ;
        MOV    DX, prompt
        MOV    AH, 9
        INT    21H                  ;显示提示信息
        ;
        MOV    AH, 1
        INT    21H                  ;接受用户按键
        MOV    [keyval], AL         ;保存到变量keyval
        ;
        MOV    DX, newline
        MOV    AH, 9
        INT    21H                  ;输出回车换行
        ;
        MOV    AL, [keyval]         ;取出刚才保存的字符
        MOV    CX, KEYLEN           ;有效字符个数
        MOV    DI, keytab           ;准备利用字符串扫描指令
        CLD
        REPNZ  SCASB                ;判断用户输入字符是否有效
        JNZ    over                 ;用户输入无效的字母，转结束
        ;
        MOV    BX, KEYLEN - 1       ;准备计算字母在有效字符串中的索引
        SUB    BX, CX               ;BX为字母在有效字符串中的索引
        AND    BX, 0FEH             ;(0,1)=0 | (2,3)=2 | (4,5)=4 | (6,7)=6
        CALL   [BX + entrytab]      ;间接调用对应的子程序
        ;
    over:
        MOV    AH, 4CH
        INT    21H                  ;结束程序，返回操作系统
    ;-------------------------------
    SUBDD:                          ;显示一条信息
        MOV   DX, messageDD
        MOV   AH, 9
        INT   21H
        RET
    messageDD  db    "This is subroutine DD",0DH,0AH,24H
    ;-------------------------------
    SUBHH:                          ;显示一条信息
        MOV   DX, messageHH
        MOV   AH, 9
        INT   21H
        RET
    messageHH  db    "This is subroutine HH",0DH,0AH,24H
    ;-------------------------------
    SUBQQ:                          ;以八进制数形式，显示当前位置的偏移
        MOV    AX, $                ;取得当前位置的偏移值
        PUSH   BX                   ;保存寄存器BX
        MOV    BX, messageQQ        ;BX=显示信息串首地址（偏移）
        MOV    DX, AX
        XOR    AL, AL
        ROL    DX, 1                ;单独处理最高位
        ADC    AL, '0'              ;转换为对应的ASCII码
        MOV    [BX], AL             ;保存到显示信息串首
        INC    BX
        MOV    CX, 5                ;准备循环5次（3位*5=15位）
    .NEXT:
        ROL    DX, 3                ;1个八进制位，对应3个二进制位
        MOV    AL, DL
        AND    AL, 07H
        ADD    AL, '0'              ;转对应ASCII码
        MOV    [BX], AL             ;依次保存到显示信息串中
        INC    BX
        LOOP   .NEXT                ;循环5次
        ;
        MOV    DX, messageQQ        ;输出信息串首地址
        MOV    AH, 9
        INT    21H                  ;显示信息串
        POP    BX                   ;恢复寄存器BX
        RET
    messageQQ  db    "XXXXXXQ",0DH,0AH,24H
    ;===============================
