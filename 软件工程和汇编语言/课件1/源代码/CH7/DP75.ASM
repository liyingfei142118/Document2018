    ;演示程序（模拟主引导记录）dp75.asm
        section   text
        bits   16                   ;16位段模式
        org    7C00H                ;被装入到起点为07C00H的内存区域
    Begin:
        MOV   AL, 0                 ;指定显示页0
        MOV   AH, 5
        INT   10H                   ;指定显示页//@1
        ;
        CLD
        MOV   AX, CS
        MOV   DS, AX                ;数据段与代码段一致
        MOV   SI, hello             ;指向字符串首
        ;
        MOV   AX, 0B800H            ;显示存储区段值
        MOV   ES, AX                ;送到ES
        MOV   DI, (80*5+8)*2        ;开始显示坐标：5行8列
        ;
        MOV   AH, 47H               ;属性（红底白字）
    Lab1:
        LODSB                       ;取一个字符
        OR    AL, AL                ;判断结束标记
        JZ    Lab2                  ;是，跳转结束
        STOSW                       ;填到显示存储区
        JMP   Lab1                  ;继续
    Lab2:
    Over:
        JMP   Over                  ;进入无限循环
        ;
    hello     db    "Hello,world", 0
        ;
        times  510 - ($-$$)  db  0  ;填充0，直到满510字节
        db    55h, 0AAh             ;最后2字节，共计512字节
