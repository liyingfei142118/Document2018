    ;演示程序dp71.asm
    %define   L_SHIFT   00000010B
    %define   R_SHIFT   00000001B
    ;
        SECTION  TEXT
        BITS  16                        ;16位代码模式
        ORG   100H                      ;COM类型可执行程序
    START:
        MOV   AH, 2                     ;取变换键状态字节
        INT   16H
        TEST  AL, L_SHIFT + R_SHIFT     ;判是否按下SHIFT键
        JNZ   OVER                      ;已经按下SHIFT键，则转结束
        ;
        MOV   AH, 1                     ;判断是否有按键
        INT   16H
        JZ    START                     ;无，继续检查
        ;
        MOV   AH, 0                     ;取得所按键
        INT   16H
        ;
        MOV   BH, 0
        MOV   AH, 14                    ;TTY方式显示所按键
        INT   10H
        JMP   START                     ;继续
    OVER:
        mov   ah, 4cH                   ;调用DOS功能，结束程序
        int   21H
