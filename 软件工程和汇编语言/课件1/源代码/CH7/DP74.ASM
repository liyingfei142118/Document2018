    ;演示程序（模拟主引导记录）dp74.asm
        section   text
        bits   16                   ;16位段模式
    Begin:                          ;启动点
        MOV   BH, 0                 ;指定显示页0
        MOV   DH, 5                 ;光标行号（5行）
        MOV   DL, 8                 ;光标列号（8列）
        MOV   AH, 2                 ;2号功能设置光标位置
        INT   10H                   ;定位光标到指定位置
        ;
        CLD                         ;字符串操作方向
        MOV   AX, CS
        MOV   DS, AX                ;数据段与代码段一致
        MOV   SI, hello             ;指向字符串首（代码段的相对地址）
        ADD   SI, 7C00H             ;指向字符串首（内存中的固定地址）//@1
    Lab1:
        LODSB                       ;取一个字符
        OR    AL, AL                ;判断结束标记
        JZ    Lab2                  ;是，跳转结束
        MOV   AH, 14
        INT   10H                   ;TTY方式显示字符
        JMP   SHORT Lab1            ;继续
    Lab2:
    Over:
        JMP   Over                  ;进入无限循环
        ;
    hello     db    "Hello,world", 0
        ;
        times  510 - ($-$$)  db  0  ;填充0，直到满510字节
        db    55h, 0aah             ;最后2字节，共计512字节
