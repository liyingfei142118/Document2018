        ;演示程序dp62.asm
        ;汇编后，使用链接器生成EXE类型的可执行程序
        segment   code              ;定义段code
    ..start:                        ;启动标号
        MOV   AX, stack
        MOV   SS, AX                ;设置堆栈段寄存器
        MOV   SP, stacktop          ;设置堆栈顶
        ;
        MOV   AX, data
        MOV   DS, AX                ;设置数据段寄存器
        ;
        MOV   DX, prompt
        CALL  PrintStr              ;显示提示信息
        ;
        MOV   AH, 1
        INT   21H                   ;接受用户按键
        ;
        MOV   BL, AL                ;临时保存所按键
        ;
        MOV   DX, newline
        CALL  PrintStr              ;形成回车换行
        ;
        MOV   AL, BL                ;恢复
        SHR   AL, 4
        CALL  ToASCII               ;把高4位转对应ASCII码
        MOV   [result], AL          ;保存
        MOV   AL, BL
        CALL  ToASCII               ;把低4位转对应ASCII码
        MOV   [result+1], AL        ;保存
        ;
        MOV   DX, result
        CALL  PrintStr              ;显示结果信息
        ;
        MOV   AH, 4CH
        INT   21H                   ;返回操作系统
        ;
    ;显示输出指定的字符串
    PrintStr:                       ;子程序入口
        PUSH  BX                    ;保护寄存器BX
        MOV   BX, DX
    LAB1:
        MOV   DL, [BX]              ;取出待显示字符
        INC   BX                    ;指向下一个
        CMP   DL, '$'               ;结束符吗？
        JZ    LAB2                  ;遇到结束符，结束
        MOV   AH, 2
        INT   21H                   ;显示该字符
        JMP   LAB1                  ;继续
    LAB2:
        POP   BX                    ;恢复寄存器BX
        RET
    ;
    ;把低4位转成对应十六进制数ASCII码
    ToASCII:                        ;子程序入口
        AND   AL, 0FH
        ADD   AL, '0'
        CMP   AL, '9'
        JBE   LAB3
        ADD   AL, 7
    LAB3:
        RET
    ;-------------------------------
    ;
        segment    data             ;定义段data
    prompt    db   "Press a key: ",'$'
    newline   db   0DH,0AH,'$'
    result    db   0,0              ;存放十六进制数ASCII码
              db   'H',0DH,0AH,'$'  ;结果字符串后半部分
    ;-------------------------------
    ;
        segment    stack  stack     ;定义堆栈段
        resb   1024                 ;安排1024字节作为堆栈
    stacktop:
    ;===============================
