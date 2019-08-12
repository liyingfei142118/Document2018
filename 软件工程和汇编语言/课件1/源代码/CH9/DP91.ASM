    ;演示程序dp91.asm
    ;演示实方式和保护方式之间的切换（示例一）
    ;                               ;常量声明
    ATDW    EQU   0092H             ;存在的可读写数据段的属性值
    ATCE    EQU   0098H             ;存在的只执行代码段的属性值
    ;
    %macro    DESCRIPTOR   5        ;表示存储段描述符结构的宏
    .LIMIT    DW    %1              ;段界限(0--15)
    .BASEL    DW    %2              ;段基地址(0--15)
    .BASEM    DB    %3              ;段基地址(16-23)
    .ATTRI    DW    %4              ;段属性
    .BASEH    DB    %5              ;段基地址(24-31)
    %endmacro
    ;
    %macro    PDESC   2             ;表示GDTR伪描述符结构的宏
    .LIMIT    DW    %1              ;界限(16位)
    .BASE     DD    %2              ;基地址(32位)
    %endmacro
    ;-----------------------------------------------------------
        section  text               ;段text
        bits     16                 ;16位段模式
    ;
    ;工作程序特征信息
    Signature  db   "YANG"          ;签名信息
    Version    dw   1               ;格式版本
    Length     dw   end_of_text     ;工作程序长度
    Start      dw   Begin           ;工作程序入口点的偏移
    Zoneseg    dw   2000H           ;工作程序期望的内存区域起始段值
    Reserved   dd   0               ;保留
    ;-----------------------------------------------------------
    GDTSeg:                                 ;全局描述符表GDT
    Dummy      DESCRIPTOR  0,0,0,0,0        ;哑描述符
    CODE       DESCRIPTOR  0FFFFH,0,0,ATCE,0;代码段描述符
    Code_Sel   equ   CODE - GDTSeg          ;代码段描述的选择子
    DATAD      DESCRIPTOR  0FFFFH,0,0,ATDW,0;目标数据段描述符
    DataD_Sel  equ   DATAD - GDTSeg         ;目标数据段描述符的选择子
    DATAS      DESCRIPTOR  0FFFFH,0FFF0H,0FFH,ATDW,0FFH ;源数据段描述符
    DataS_Sel  equ   DATAS - GDTSeg         ;源数据段描述符的选择子
    LenGDT     equ   $ - GDTSeg             ;GDT表长度
    ;-----------------------------------------------------------
    LenBuff    equ   256                    ;缓冲区字节长度
    Buffer:
        times   LenBuff   db  39H           ;缓冲区
    ;------------------------------
    VGDTR      PDESC   LenGDT-1, 0          ;存放伪描述符的变量//@1
    ;-----------------------------------------------------------
    Begin:
        MOV   AX, CS
        MOV   DS, AX
        MOV   [ToReal+3], AX        ;重定位段间转移指令中的段值//@2
        ;初始化GDT中的部分描述符
        MOV   BX, 16
        MOV   AX, CS
        MUL   BX                    ;DX:AX=示例程序所占区域起始地址
        MOV   [CODE.BASEL], AX
        MOV   [CODE.BASEM], DL      ;设置代码段描述符中的基地址
        MOV   [CODE.BASEH], DH
        MOV   [DATAD.BASEL], AX
        MOV   [DATAD.BASEM], DL     ;设置目标数据段描述符中的基地址
        MOV   [DATAD.BASEH], DH
        ;初始化用于GDTR的伪描述符
        ADD   AX, GDTSeg            ;加上GDT表在段内的偏移//@3
        ADC   DX, 0                 ;DX:AX=GDT所在段的基地址
        MOV   [VGDTR.BASE], AX
        MOV   [VGDTR.BASE+2], DX    ;填写到用于GDTR的伪描述符变量
        ;加载GDTR
        LGDT  [VGDTR]               ;//@4
        ;其他准备工作
        CLI                         ;关中断
        CALL  EnableA20             ;打开地址线A20
        ;切换到保护方式
        MOV   EAX, CR0
        OR    EAX, 1
        MOV   CR0, EAX              ;使得CR0中的PE=1
        ;
        JMP   Code_Sel:PM_Entry     ;真正进入保护方式//@5
        ;---------------------------
    PM_Entry:                       ;现在开始在保护方式下
        CLD
        ;为传送数据设置源数据段和目标数据段的段寄存器
        MOV   AX, DataS_Sel
        MOV   DS, AX                ;加载源数据段描述符//@6
        MOV   AX, DataD_Sel
        MOV   ES, AX                ;加载目标数据段描述符//@7
        ;设置段内偏移并实施传送
        MOV   SI, 0
        MOV   DI, Buffer
        MOV   CX, 2                 ;8个字节=2个双字
        REP   MOVSD
        ;切换回实方式
        MOV   EAX, CR0
        AND   EAX, 0FFFFFFFEH
        MOV   CR0, EAX              ;清CR0中的PE位//@8
    ToReal:                         ;真正进入实方式
        JMP   0:Real                ;需要重定位//@9
        ;---------------------------
    Real:                           ;现在回到了实方式
        CALL  DisableA20            ;关闭地址线A20
        STI                         ;开中断
        MOV   AX, CS
        MOV   DS, AX
        MOV   SI, Buffer            ;指向数据缓冲区
        MOV   CX, 8                 ;8个字节数据
        CALL  ShowBuff              ;以十六进制数形式显示字节数据
        ;
        RETF                        ;结束，返回到加载器
    ;-----------------------------------------------------------
    EnableA20:                      ;打开地址线A20
       PUSH  AX
       IN    AL, 92H
       OR    AL, 2
       OUT   92H, AL
       POP   AX
       RET
    ;-------------------------------
    DisableA20:                     ;关闭地址线A20
        PUSH  AX
        IN    AL, 92H
        AND   AL, ~2
        OUT   92H, AL
        POP   AX
        RET
    ;-------------------------------
    ShowBuff:                       ;以十六进制数的形式显示数据
        CLD                         ;DS:SI=缓冲区首地址；CX=字节数
    .LA:LODSB
        PUSH  AX
        SHR   AL, 4
        CALL  TOASCII
        CALL  PutChar
        POP   AX
        CALL  TOASCII
        CALL  PutChar
        MOV   AL, ' '
        CALL  PutChar
        LOOP  .LA
        MOV   AL, 0DH
        CALL  PutChar
        MOV   AL, 0AH
        CALL  PutChar
        RET
    ;-------------------------------
    PutChar:                        ;显示字符
        MOV   BH, 0
        MOV   AH, 14
        INT   10H
        RET
    ;-------------------------------
    TOASCII:                        ;转十六进制数字符ASCII码
        AND   AL, 0FH
        ADD   AL, 30H
        CMP   AL, 39H
        JBE   .LA
        ADD   AL, 7
    .LA:RET
    end_of_text:                    ;源代码到此结束
