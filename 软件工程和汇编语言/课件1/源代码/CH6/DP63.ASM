        ;演示程序dp63.asm
        ;汇编时可以忽略由NASM给出的警告信息
        segment   code              ;段code
        org    100H                 ;起始偏移100H
    begin:
        MOV    AX, CS               ;使得数据段与代码段相同
        MOV    DS, AX               ;DS = CS
        ;
        MOV   DX, mess1             ;DX = mess1的偏移
        CALL  EchoMess              ;显示输出提示信息mess1
        MOV   DX, buffer            ;DX = buffer的偏移
        CALL  GetHex                ;由键盘输入一个十六进制数
        MOV   [addrSeg], AX         ;保存，作为指定存储单元的段值
        CALL  NewLine               ;形成回车换行
        ;
        MOV   DX, mess2             ;DX = mess2的偏移
        CALL  EchoMess              ;显示输出提示信息mess2
        MOV   DX, buffer            ;DX = buffer的偏移
        CALL  GetHex                ;由键盘输入一个十六进制数
        MOV   [addrDisp], AX        ;保存，作为指定存储单元的偏移
        CALL  NewLine               ;形成回车换行
        ;
        MOV   ES, [addrSeg]         ;取出段值，送到ES
        MOV   BX, [addrDisp]        ;取出偏移，送到BX
        MOV   AL, [ES:BX]           ;取出指定存储单元之字节值
        CALL  EchoBin               ;按二进制形式显示
        ;
        MOV   AH, 4CH
        INT   21H                   ;结束程序，返回操作系统
    ;-------------------------------
    ;子程序名：GetHex
    ;功    能：接受由键盘输入的十六进制数，并转换成二进制值
    ;入口参数：DS:DX = 用于存放字符串缓存区的开始地址
    ;                  （首字节含有实际的缓冲区有效长度）
    ;出口参数：AX = 二进制值（由字符串转换所得）
    ;说    明：不考虑非法输入，实际输入字符数应是缓冲区字节数
    GetHex:
        PUSH  SI                    ;保护寄存器
        PUSH  BX
        MOV   SI, DX                ;SI = 缓冲区地址
        XOR   CX, CX                ;
        MOV   CL, [SI]              ;CX = 缓冲区长度
        LEA   BX, [SI+1]            ;BX = 存放字符的缓冲区首地址
    LL1@GetHex:                     ;==接受键盘输入的十六进制数字符串
        CALL  GetChar               ;取得一个字符
        MOV   [BX], AL              ;依次保存
        INC   BX
        LOOP  LL1@GetHex            ;继续
        ;                           ;==转换成数值
        MOV   CL, [SI]              ;CX = 缓冲区长度
        LEA   BX, [SI+1]            ;BX = 存放字符的缓冲区首地址
        XOR   DX, DX                ;DX = 0
    LL2@GetHex:
        MOV   AL, [BX]              ;依次取得一个字符
        INC   BX
        CALL  ToBin                 ;转换成字符对应的数值
        SHL   DX, 4                 ;准备合并
        OR    DL, AL                ;合并到一起
        LOOP  LL2@GetHex            ;继续
        MOV   AX, DX                ;AX = 返回值（转换结果）
        ;
        POP   BX                    ;恢复被保护寄存器
        POP   SI
        RET                         ;返回
    ;-------------------------------
    ;子程序名：ToBin
    ;功    能：把一位十六进制数字符转换成对应的二进制数值
    ;入口参数：AL = 十六进制数字符
    ;出口参数：AL = 对应二进制数值
    ;说    明：如非十六进制数字符，返回0
    ToBin:
        CMP   AL, '0'
        JB    LL2@ToBin
        CMP   AL, '9'
        JA    LL1@ToBin
        SUB   AL, '0'               ;把'0'-'9'的字符转成对应数值
        RET
   LL1@ToBin:     
        AND   AL, 11011111B         ;可能小写字母转成大写字母
        CMP   AL, 'A'
        JB    LL2@ToBin
        CMP   AL, 'F'
        JA    LL2@ToBin
        SUB   AL, 'A' - 10          ;把'A'-'F'的字符转成对应数值
        RET
    LL2@ToBin:
        MOV   AL, 0                 ;无效字符，缺省值
        RET
    ;-------------------------------
    ;子程序名：EchoBin
    ;功    能：二进制数形式显示8位二进制值
    ;入口参数：AL = 二进制数
    ;出口参数：无
    EchoBin:
        MOV   DH, AL
        MOV   CX, 8                 ;8位二进制，循环8次
    LL1@EchoBin:
        RCL   DH, 1                 ;依次移出一位到进位标志CF
        MOV   DL, '0'               ;假设是0
        ADC   DL, 0                 ;考虑实际值
        CALL  PutChar               ;显示一个字符
        LOOP  LL1@EchoBin           ;继续
        RET        
    ;-------------------------------
    ;子程序名：EchoMess
    ;功    能：显示字符串
    ;入口参数：DS:DX = 字符串首地址
    ;出口参数：无
    ;说    明：字符串以0作为结束标志
    EchoMess:
        PUSH  BX                    ; 保护寄存器BX
        MOV   BX, DX
    LL1@EchoMess:
        MOV   DL, [BX]              ;取出待显示字符
        INC   BX                    ;依次
        OR    DL, DL                ;是否结束符？
        JZ    LL2@EchoMess          ;是，转结束
        CALL  PutChar               ;否，显示之
        JMP   SHORT LL1@EchoMess    ;继续
    LL2@EchoMess:
        POP   BX                    ;恢复寄存器BX
        RET                         ;返回
    ;-------------------------------
    ;子程序名：NewLine
    ;功    能：显示输出回车换行
    ;出入参数：无
    NewLine:
        MOV   AH, 2                 ;2号系统功能
        MOV   DL, 0DH               ;回车符
        INT   21H                   ;显示输出回车
        MOV   DL, 0AH               ;换行符
        INT   21H                   ;显示输出换行
        RET                         ;返回
    ;-------------------------------
    ;子程序名：GetChar
    ;功    能：从键盘读一个键
    ;入口参数：无
    ;出口参数：AL = 所读键的ASCII码
    GetChar:
        MOV   AH,1
        INT   21H                   ;调用1号系统功能键盘输入
        RET
    ;-------------------------------
    ;子程序名：PutChar
    ;功    能：显示输出一个字符
    ;入口参数：DL = 显示输出字符ASCII码
    ;出口参数：无
    PutChar:
        MOV   AH,2
        INT   21H                   ;调用2号系统功能显示输出
        RET
    ;-------------------------------
    ;常量声明部分
    BUFFLEN    equ   4
    ;数据部分
    mess1      db    "Segment(xxxxH): ",0   ;提示字符串
    mess2      db    "Offset(xxxxH): ",0    ;提示字符串
    buffer     db    BUFFLEN                ;输入缓冲区长度
               resb  BUFFLEN                ;输入缓冲区
    addrSeg    dw    0                      ;存放指定的存储单元段值
    addrDisp   dw    0                      ;存放指定的存储单元偏移
    ;=======================================
