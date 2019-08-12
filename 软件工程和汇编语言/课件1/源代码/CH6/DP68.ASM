        ;演示程序dp68.asm
        ;在汇编后，使用链接器，生成EXE类型的可执行程序
        section   codeA  align=16   ;开始段codeA
    ..start:                        ;启动点
        MOV   AX, CS
        MOV   DS, AX                ;使得当前数据段同代码段
        ;
        MOV   AX, codeC             ;取得codeC段的段值
        CALL  FAR  [ptsubr]         ;间接调用远过程，显示上述段值
        ;
        MOV   DL, 0DH               ;形成回车和换行
        CALL  codeC:PutChar         ;直接调用远过程
        MOV   DL, 0AH
        CALL  codeC:PutChar         ;直接调用远过程
        ;
        MOV   SI, ptsubr            ;指向ptsubr双字存储单元
        MOV   AX, codeB             ;取得codeB段的段值
        CALL  FAR  [SI]             ;间接调用远过程，显示上述段值
        ;
        MOV   AH, 4CH
        INT   21H                   ;结束程序，返回操作系统
    ;
    ptsubr   dw   echo4             ;子程序echo4的段内偏移
             dw   codeB             ;子程序echo4所在段的段值
    ;
    section   codeB  align=16       ;开始段codeB
    ToASCII:                        ;把DL的低4位转换成
        AND   DL, 0FH               ;一位十六进制数的ASCII码
        ADD   DL, '0'
        CMP   DL, '9'
        JBE   lab
        ADD   DL, 7
    lab:RET                         ;段内返回
    ;
    echo4:                          ;采用4位十六进制数形式
        MOV   CX, 4                 ;显示AX中的16位值
        MOV   BX, AX
    next:
        ROL   BX, 4
        MOV   DL, BL
        CALL  ToASCII
        CALL  codeC:PutChar         ;调用远过程，显示一位十六进制数
        LOOP  next
        MOV   DL, 'H'
        CALL  codeC:PutChar         ;调用远过程,显示字符H
        RETF                        ;段间返回
    ;
        section  codeC  align=16    ;开始段codeC
    PutChar:                        ;显示DL中的字符
        MOV   AH, 2
        INT   21H
        RETF                        ;段间返回
    ;===============================
