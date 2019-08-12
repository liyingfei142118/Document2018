    ;演示程序（引导程序）dp76.asm
    SDISP     EQU   7C00H           ;符号常量
        section   text
        bits   16                   ;16位段模式
    Begin:
        MOV   AX, CS
        MOV   SS, AX
        MOV   SP, SDISP             ;设置堆栈
        MOV   DS, AX                ;源数据段就是代码段
        MOV   SI, SDISP+Begin       ;指向源字符串首（绝对地址）
        PUSH  WORD  0060H
        POP   ES                    ;目标数据段的段值为0060H
        MOV   DI, 0                 ;目标段的偏移
        CLD                         ;字符串操作方向
        MOV   CX, 100H              ;256个字 = 512字节
        REP   MOVSW                 ;复制自身
        PUSH  ES                    ;压目标段值到堆栈
        PUSH  Begin2                ;压目标偏移到堆栈
        RETF                        ;段间转移到新的位置
        ;---------------------------
    Begin2:
        PUSH  CS
        POP   DS                    ;数据段同新的代码段
        ;
        mov   dx, mess1
        call  PutStr                ;显示操作提示信息
        call  GetChar               ;获得用户按键
        ;
        MOV   SI, DiskAP            ;指向磁盘地址包DAP
        MOV   DL, 80H               ;设虚拟硬盘是C盘
        MOV   AH, 42H               ;采用扩展的读功能
        INT   13H                   ;从硬盘读指定的数据（程序）到内存
        JC    Over                  ;如果读出错，则转
        ;
        MOV   AX, 0
        MOV   ES, AX
        MOV   AX, 0AA55H
        CMP   [ES:SDISP+01FEH], AX ;检查所读内容是否有标记//@2
        JNZ   Over                 ;没有，则转
        ;
        PUSH  WORD  0              ;把工作程序段值压入堆栈
        PUSH  WORD  SDISP + 0      ;把工作程序偏移压入堆栈
        RETF                       ;转工作程序执行
        ;
    Over:
        MOV   DX, mess2
        CALL  PutStr                ;显示出错提示信息
        JMP   $                     ;进入无限循环
    ;-------------------------------
    GetChar:                        ;获得用户按键
        MOV   AH, 0
        INT   16H
        RET
    ;-------------------------------
    PutStr:                         ;显示字符串（以0结尾）
        MOV   BH, 0
        MOV   SI, DX
    Lab1:
        LODSB                       ;取一个字符
        OR    AL, AL                ;判断结束标记
        JZ    Lab2                  ;是，跳转结束
        MOV   AH, 14
        INT   10H                   ;TTY方式显示字符
        JMP   Lab1                  ;继续
    Lab2:
        RET
    ;-------------------------------
    DiskAP:
        DB    10H                   ;DAP尺寸
        DB    0                     ;保留
        DW    1                     ;扇区数
        DW    SDISP                 ;缓冲区偏移
        DW    0000H                 ;缓冲区段值
        DD    123                   ;起始扇区LBA的低4字节（假设）
        DD    0                     ;起始扇区LBA的高4字节
    ;
    mess1     db    "Press any key......", 0
    mess2     db    "Error......", 0
        ;
        times  510 - ($-$$)  db  0  ;填充0，直到510字节
        db    55h, 0aah             ;最后2字节，共计512字节
