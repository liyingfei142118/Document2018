        ;演示程序dp66.asm
        ;在汇编后，使用链接器，生成EXE类型的可执行程序
        section   codeA             ;开始段codeA
    ..start:                        ;执行起点（由标号..start指定）
        MOV   AX, data              ;取得data段的段值
        MOV   DS, AX                ;设置DS
        MOV   DL, [flagch]
        MOV   AH, 2
        INT   21H                   ;显示标记字符A
        ;
        JMP   codeB:step2           ;段间转移到codeB段的step2处//@1
        ;
    step4:
        MOV   DL, [flagch]
        MOV   AH, 2
        INT   21H                   ;显示标记字符A
        ;
        MOV   AH, 4CH
        INT   21H                   ;结束程序，返回操作系统
    ;-------------------------
    section   data   align=16       ;开始段data
    flagch   db     "ABC"
    ;-------------------------
    section   codeC  align=16       ;开始段codeC
    step3:
        MOV   DL, [flagch +2]
        MOV   AH, 2
        INT   21H                   ;显示标记字符C
        ;
        JMP   FAR  step4            ;段间转移到codeA段的step4处//@2
    ;-------------------------------
    section   codeB  align=16       ;开始段codeB
    step2:
        MOV   DL, [flagch +1]
        MOV   AH, 2
        INT   21H                   ;显示标记字符C
        ;
        JMP   codeC:step3           ;段间转移到codeC段的step3处//@3
    ;===============================
