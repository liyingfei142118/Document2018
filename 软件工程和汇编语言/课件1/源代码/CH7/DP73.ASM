    ;演示程序dp73.asm
    %define  Space      20H         ;空格符
    %define  Enter      0DH         ;回车符
    %define  Newline    0AH         ;换行符
    %define  Backspace  08H         ;退格
    %define  Bell       07H         ;响铃
    %define  Lenofbuf   16          ;缓冲区长度
    ;
        SECTION  TEXT
        BITS  16
        ORG   100H                  ;COM型程序100H开始
    Begin:                          ;起点
        PUSH  CS
        POP   DS                    ;DS=CS
        MOV   DX, buffer            ;DX=缓冲区首地址
        CALL  GetDStr               ;获取一个数字串
        ;
        MOV   AL, Enter             ;形成回车换行效果
        CALL  PutChar
        MOV   AL, Newline
        CALL  PutChar
        ;
        MOV   DX, buffer + 1        ;DX=字符串首地址
        CALL  PutDStr               ;显示一个字符串
        ;
        mov   ah, 4ch
        int   21h                   ;结束程序
        ;
    buffer:                         ;缓冲区
        db    Lenofbuf              ;缓冲区的字符串容量
        resb  Lenofbuf              ;存放字符串
    ;-------------------------------
    ;子程序名：GetDStr
    ;功    能：接受一个由十进制数字符组成的字符串
    ;入口参数：DS:DX=缓冲区首地址
    ;说    明：（1）缓冲区第一个字节是其字符串容量
    ;          （2）返回的字符串以回车符（0DH）结尾
    GetDStr:
        PUSH  SI
        MOV   SI, DX
        MOV   CL, [SI]              ;取得缓冲区的字符串容量
        CMP   Cl, 1                 ;如小于1，直接返回
        JB    .Lab6
        ;
        INC   SI                    ;指向字符串的首地址
        XOR   CH, CH                ;CH作为字符串中的字符计数器，清零
    .Lab1:
        CALL  GetChar               ;读取一个字符
        OR    AL, AL                ;如为功能键，直接丢弃//@1
        JZ    SHORT  .Lab1
        CMP   AL, Enter             ;如为回车键，表示输入字符串结束
        JZ    SHORT  .Lab5          ;转输入结束
        CMP   AL,  Backspace        ;如为退格键
        JZ    SHORT  .Lab4          ;转退格处理
        CMP   AL, Space             ;如为其他不可显示字符，丢弃//@2
        JB    SHORT  .Lab1
        ;
        cmp   al, '0'
        jb    short  .Lab1          ;小于数字符，丢弃
        cmp   al, '9'
        ja    short  .Lab1          ;大于数字符，丢弃
        ;
        CMP   Cl, 1                 ;字符串中的空间是否有余？
        JA    SHORT  .Lab3          ;是，转存入字符串处理
    .Lab2:
        MOV   AL, Bell
        CALL  PutChar               ;响铃提醒
        JMP   SHORT  .Lab1          ;继续接受字符
        ;
    .Lab3:
        CALL  PutChar               ;显示字符
        MOV   [SI], AL              ;保存到字符串
        INC   SI                    ;调整字符串中的存放位置
        INC   CH                    ;调整字符串中的字符计数
        DEC   CL                    ;调整字符串中的空间计数
        JMP   SHORT  .Lab1          ;继续接受字符
        ;
    .Lab4:                          ;退格处理
        CMP   CH, 0                 ;字符串中是否有字符？
        JBE   .Lab2                 ;没有，响铃提醒
        CALL  PutChar               ;光标回退
        MOV   AL, Space
        CALL  PutChar               ;用空格擦除字符
        MOV   AL, Backspace
        CALL  PutChar               ;再次光标回退
        DEC   SI                    ;调整字符串中的存放位置
        DEC   CH                    ;调整字符串中的字符计数
        INC   CL                    ;调整字符串中的空间计数
        JMP   SHORT  .Lab1          ;继续接受字符
        ;
    .Lab5:
        MOV    [SI], AL             ;保存最后的回车符
    .Lab6:
        POP   SI
        RET
    ;-------------------------------
    ;子程序名：PutDStr
    ;功    能：显示一个以回车符（0DH）结尾的字符串
    ;入口参数：DS:DX=字符串首地址
    PutDStr:
        PUSH  SI
        MOV   SI, DX
    .Lab1:
        LODSB                       ;取一个字符
        CALL  PutChar               ;显示字符
        CMP   AL, Enter             ;是回车符吗？
        JNZ   .Lab1                 ;否，继续
        MOV   AL, Newline
        CALL  PutChar               ;产生换行
        POP   SI
        RET
    ;-------------------------------
    PutChar:                        ;显示输出一个字符
        MOV   BH, 0
        MOV   AH, 14
        INT   10H
        RET
    ;-------------------------------
    GetChar:                        ;由键盘输入一个字符
        MOV   AH, 0
        INT   16H
        RET
