    ;演示程序dp612.asm
    ;宏GetChar：利用系统功能调用，接受从键盘输入一个键
    %macro   GetChar   0
       MOV   AH, 1
       INT   21H
    %endmacro
    ;宏PutChar：利用系统功能调用，显示输出一个字符
    %macro   PutChar   1
        MOV   DL, %1
        MOV   AH, 2
        INT   21H
    %endmacro
    ;宏TOASC：把十六进制数转成对应字符的ASCII码
    %macro    TOASC   0
        AND   AL, 0FH 
        ADD   AL, '0'
        CMP   AL, '9'
        JBE   SHORT  $+4            ;跳过其后加7指令
        ADD   AL, 7
    %endmacro
    ;-------------------------------
        SECTION   TEXT              ;开始一个段TEXT
        BITS     16                 ;16位段
        ORG    100H                 ;起始偏移100H
    begin:
        GetChar                     ;接受一个键
        MOV   BH, AL                ;临时保存
        PutChar   0DH               ;形成回车
        PutChar   0AH               ;形成换行
        MOV   AL, BH
        SHR   AL, 4                 ;得到高4位
        TOASC                       ;把高4位转成对应ASCII码
        PutChar  AL                 ;显示之
        MOV   AL, BH
        TOASC                       ;把低4位转成对应ASCII码
        PutChar  AL                 ;显示之
        ;
        MOV   AH,4CH                ;结束返回操作系统
        INT   21H
