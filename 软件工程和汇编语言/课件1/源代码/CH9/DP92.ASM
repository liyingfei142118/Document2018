    ;演示程序dp92.asm
    ;演示32位代码段和16位代码段之间的切换（示例二）
    %include  "DMC.H"               ;文件DMC.H含有宏的声明和符号常量等
    ;-----------------------------------------------------------
    ;                               ;常量声明
    COUNT   EQU   16                ;16个字节
    COLOR   EQU   47H               ;显示属性（红底白色）
        section  text               ;段text
        bits     16                 ;16位段模式
    Head:                           ;工作程序特征信息
        HEADER   end_of_text, Begin, 2000H
    ;-----------------------------------------------------------
    GDTSeg:                                 ;全局描述符表GDT
    Dummy      DESCRIPTOR  0,0,0,0,0        ;哑描述符
    Normal     DESCRIPTOR  0FFFFH,0,0,ATDW,0
    Normal_Sel equ   Normal - GDTSeg        ;规范段描述符的选择子
    STACKS     DESCRIPTOR  0FFFFH,0,0,ATDWA,0
    StackS_Sel equ   STACKS - GDTSeg        ;堆栈段描述符的选择子
    CODE16     DESCRIPTOR  0FFFFH,Code16Seg,0,ATCE,0
    Code16_Sel equ   CODE16 - GDTSeg        ;16位代码段描述的选择子
    CODE32     DESCRIPTOR  LenCode32-1,Code32Seg,0,ATCE32,0
    Code32_Sel equ   CODE32 - GDTSeg        ;32位代码段描述的选择子
    DATAS      DESCRIPTOR  COUNT-1,0FFF0H,0FFH,ATDR,0FFH ;
    DataS_Sel  equ   DATAS - GDTSeg         ;源数据段描述符的选择子
    VIDEOMEM   DESCRIPTOR  7FFH,8000H,0BH,ATDW,0
    VMem_Sel   equ   VIDEOMEM - GDTSeg      ;目标数据段描述符的选择子
    LenGDT     equ   $ - GDTSeg             ;GDT表长
    ;-----------------------------------------------------------
    ;演示用的32位的代码段
        align  16                   ;16字节对齐
        bits   32                   ;通知汇编器采用32位段模式//@0
    Code32Seg:
    Code32_Entry  equ  $ - Code32Seg  ;//@1
        MOV   AX, StackS_Sel
        MOV   SS, AX                ;装载堆栈段寄存器SS
        MOV   AX, DataS_Sel
        MOV   DS, AX                ;装载数据段
        MOV   AX, VMem_Sel
        MOV   ES, AX                ;装载视频存储区段
        ;
        MOV   ESI, 0                ;设置指针和计数器//@2
        MOV   EDI, 10*80*2          ;显示位置从第10行首开始
        MOV   ECX, COUNT            ;字节数
        CLD
    .Next:
        LODSB                       ;取一字节
        PUSH  AX
        CALL  TOASCII               ;低4位转换成ASCII
        MOV   AH, COLOR             ;显示颜色
        SHL   EAX, 16               ;保存到EAX高16位
        POP   AX
        SHR   AL, 4
        CALL  TOASCII               ;高4位转换成ASCII
        MOV   AH, COLOR             ;显示颜色
        STOSD                       ;直接写屏方式显示2个字符
        MOV   AL, 20H
        STOSW                       ;显示空格
        LOOP  .Next
        ;切换到16位的代码段
        JMP   Code16_Sel:Code16_Entry
    ;-------------------------------
    TOASCII:                        ;转十六进制数的ASCII码
        AND   AL, 0FH
        ADD   AL, 30H
        CMP   AL, 39H
        JBE   .LA
        ADD   AL, 7
    .LA:RET
    LenCode32   equ   $ - Code32Seg ;32位代码段的长度
    ;-----------------------------------------------------------
    ;演示用的16位的代码段
        align  16                   ;16字节对齐
        bits   16                   ;通知汇编器采用16位段模式
    Code16Seg:
    Code16_Entry  equ  $ - Code16Seg  ;//@3
        XOR   SI, SI                ;设置指针和计数器//@4
        MOV   DI, 12*80*2           ;显示位置在第12行首
        MOV   AH, COLOR             ;显示颜色
        MOV   CX, COUNT             ;字节数
    .Next:
        LODSB                       ;取得指定区域内容
        STOSW                       ;直接作为ASCII码显示
        LOOP  .Next
        ;
        MOV   AX, Normal_Sel        ;//@5
        MOV   DS, AX                ;把Normal段选择子装入DS和ES
        MOV   ES, AX
        ;
        MOV   EAX, CR0              ;切换到实方式
        AND   EAX, 0FFFFFFFEH
        MOV   CR0, EAX
    ToReal:                         ;真正进入实方式
        JMP   0:Real                ;需要重定位段值部分
    ;===========================================================
    ;实方式下的数据和代码
        align  16                   ;16字节对齐
        bits   16                   ;16位段模式
    VGDTR      PDESC  LenGDT-1, 0   ;伪描述符
    VARSS      DW     0             ;用于保存SS的变量
    ;-------------------------------
    Begin:
        MOV   AX, CS
        MOV   DS, AX
        MOV   [ToReal+3], AX        ;形成正确的段间转移指令（重定位）
        ;初始化GDT中的部分描述符
        MOV   BX, 16
        MOV   AX, CS                
        MUL   BX                    ;DX:AX=目标代码所占区域的起始地址
        ADD   AX, [CODE32.BASEL]    ;//@6
        ADC   DX, 0                 ;DX:AX=32位代码段的基地址
        MOV   [CODE32.BASEL], AX
        MOV   [CODE32.BASEM], DL    ;设置32位代码段描述符中的基地址
        MOV   [CODE32.BASEH], DH
        ;
        MOV   AX, CS                
        MUL   BX                    ;DX:AX=目标代码所占区域的起始地址
        ADD   AX, [CODE16.BASEL]    ;//@7
        ADC   DX, 0                 ;DX:AX=16位代码段的基地址
        MOV   [CODE16.BASEL], AX
        MOV   [CODE16.BASEM], DL    ;设置16位代码段描述符中的基地址
        MOV   [CODE16.BASEH], DH
        ;
        MOV   AX, SS
        MUL   BX                    ;DX:AX=当前堆栈段的基地址
        MOV   [STACKS.BASEL], AX    ;//@8
        MOV   [STACKS.BASEM], DL    ;设置堆栈段描述符中的基地址
        MOV   [STACKS.BASEH], DH
        MOV   [VARSS], SS           ;保存实方式下的堆栈段SS//@9
        ;初始化用于GDTR的伪描述符
        MOV   AX, CS                
        MUL   BX                    ;DX:AX=目标代码所占区域的起始地址
        ADD   AX, GDTSeg
        ADC   DX, 0                 ;DX:AX=GDT所在段的基地址
        MOV   [VGDTR.BASE], AX
        MOV   [VGDTR.BASE+2], DX    ;填写到用于GDTR的伪描述符
        ;
        LGDT  [VGDTR]               ;加载GDTR
        CLI                         ;关中断
        CALL  EnableA20             ;打开地址线A20
        ;
        MOV   EAX, CR0              ;切换到保护方式
        OR    EAX, 1
        MOV   CR0, EAX              ;使得CR0中的PE=1
        ;                           ;真正进入保护方式
        JMP   Code32_Sel:Code32_Entry
        ;---------------------------
    Real:                           ;现在回到了实方式
        MOV   AX, CS
        MOV   DS, AX
        MOV   SS, [VARSS]           ;恢复实方式下的SS//@10
        ;
        CALL  DisableA20            ;关闭地址线A20
        STI                         ;开中断
        ;
        RETF                        ;返回到加载器
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
    end_of_text:                    ;源程序到此为止
