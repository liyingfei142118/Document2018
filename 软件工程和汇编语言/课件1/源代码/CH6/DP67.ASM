        ;演示程序dp67.asm
        ;在汇编后，使用链接器，生成EXE类型的可执行程序
        section   data   align=16   ;开始段data
    ptnext2  dw    step2            ;标号step2的偏移
             dw    codeB            ;标号step2所在段的段值
    ptnext3  dw    step3            ;标号step3的偏移
             dw    codeA            ;标号step3所在段的段值
    flagch   db     "abc"           ;标记字符串
    ;
    ;-------------------------
        section   codeA  align=16   ;开始段codeA
    ..start:                        ;启动点（由标号..start给定）
        MOV   AX, data
        MOV   DS, AX                ;设置数据段的段值
        ;
        MOV   DL, [flagch]
        MOV   AH, 2
        INT   21H                   ;显示标记字符a
        ;
        JMP   FAR  [ptnext2]        ;段间转移到codeB段的step2处//@1
        ;
    step3:
        MOV   DL, [flagch]
        MOV   AH, 2
        INT   21H                   ;显示标记字符a
        ;
        MOV   AH, 4CH
        INT   21H                   ;结束程序，返回操作系统
        ;
    ;-------------------------
        section   codeB  align=16   ;开始段codeB
    step2:
        MOV   DL, [flagch +1]
        MOV   AH, 2
        INT   21H                   ;显示标记字符b
        ;
        MOV   BX, ptnext3           ;取得存放转移目标地址的存储单元的偏移
        JMP   FAR  [BX]             ;段间转移到codeA段的step3处//@2
    ;===============================
