        ;演示程序dp65.asm
        ;在汇编后，使用链接器，生成EXE类型的可执行程序
        section   code              ;声明段code
    ..start:                        ;由标号..start指定执行起点
        MOV   AX, data
        MOV   DS, AX                ;DS用于数据段
        MOV   DX, hello
        CALL  Print_str             ;显示提示信息
        MOV   AH, 4CH
        INT   21H                   ;结束程序，返回操作系统
    over:
        ;---------------------------
        section   data              ;声明段data
    hello  db   "Hello,world", 0DH, 0AH, 24H
        ;---------------------------
        section   code              ;恢复到段code
    Print_str:
        MOV    AH, 9
        INT    21H
        RET
