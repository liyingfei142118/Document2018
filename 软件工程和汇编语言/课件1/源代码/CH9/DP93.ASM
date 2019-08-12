    ;演示程序dp93.asm
    ;演示局部描述符表LDT的使用（示例三）
    %include  "DMC.H"               ;文件DMC.H含有宏的声明和符号常量等
    ;-----------------------------------------------------------
        section  text               ;段text
        bits     16                 ;16位段模式
    Head:                           ;工作程序特征信息
        HEADER   end_of_text, Begin, 2000H
    ;-----------------------------------------------------------
    GDTSeg:                         ;全局描述符表GDT
    Dummy      DESCRIPTOR  0,0,0,0,0
    Normal     DESCRIPTOR  0FFFFH,0,0,ATDW,0
    Normal_Sel equ   Normal - GDTSeg
    InitGDT:                        ;GDT中待初始化描述符起点
    ;局部描述符表LDT段的描述符及其选择子
    LDTable    DESCRIPTOR  LenLDT-1,LDTSeg,0,ATLDT,0
    LDT_Sel    equ   LDTable - GDTSeg
    ;16位代码段T的描述符及其选择子
    CodeT      DESCRIPTOR  0FFFFH,CodeTSeg,0,ATCER,0
    CodeT_Sel  equ   CodeT - GDTSeg
    NumDescG   equ  ($ - InitGDT)/8 ;GDT中需初始化的描述符个数
    LenGDT     equ   $ - GDTSeg
    ;-----------------------------------------------------------
        align  16                   ;16字节对齐
    LDTSeg:                         ;局部描述符表LDT
    ;32位代码段D的描述符及其选择子
    CodeD      DESCRIPTOR  LenCodeD-1,CodeDSeg,0,ATCE32,0
    CodeD_Sel  equ  (CodeD - LDTSeg) +TIL
    ;32位代码段P的描述符及其选择子
    CodeP      DESCRIPTOR  LenCodeP-1,CodePSeg,0,ATCE32,0
    CodeP_Sel  equ	(CodeP - LDTSeg) +TIL
    ;LDT别名段（作为数据段）的描述符及其选择子
    ALDT       DESCRIPTOR  LenLDT-1,LDTSeg,0,ATDR,0
    ALDT_Sel   equ	(ALDT - LDTSeg) +TIL
    ;数据缓冲区段的描述符及其选择子
    DBuff      DESCRIPTOR  LenDBuff-1,DBSeg,0,ATDW,0
    DBuff_Sel  equ  (DBuff - LDTSeg) +TIL
    ;堆栈段的描述符及其选择子
    StackS     DESCRIPTOR  BoStack-1,StackSeg,0,ATDW32,0
    Stack_Sel  equ  (StackS - LDTSeg) +TIL
    NumDescL   equ  ($ - LDTSeg)/8  ;LDT中需初始化的描述符个数
    ;视频存储区段的描述符及其选择子
    VideoMem   DESCRIPTOR  0FFFFH,0,0,0F00H+ATDW,0
    VMem_Sel   equ	(VideoMem - LDTSeg) +TIL
    LenLDT     equ  $ - LDTSeg      ;LDT的长度
    ;-----------------------------------------------------------
    ;数据缓冲区段（用于存放显示输出信息）
        align  16                   ;16字节对齐
    DBSeg:                          ;缓冲区起始位置
    Message    equ  $ - DBSeg       ;段内偏移
               db   'Attributes='
    Buffer     equ  $ - DBSeg       ;段内偏移//@1
               db   '0000H',0
    LenDBuff   equ  $ - DBSeg
    ;-----------------------------------------------------------
    ;工作任务的堆栈段
        align  16                   ;16字节对齐
    StackSeg:                       ;堆栈顶位置
               times  256  dd  0
    BoStack    equ    $ - StackSeg  ;堆栈底部的段内偏移//@2
    ;-----------------------------------------------------------
    ;工作任务的代码段P（32位段）（包含远过程DM和B，还有近过程H）
        align  16                   ;16字节对齐
        bits   32                   ;32位段模式
    CodePSeg:                       ;代码段P的起始位置
    ;子程序DM（远过程）
    ;功    能：显示输出字符串
    ;入口参数：FS:ESI 指向字符串（以0结尾）
	;          ES:EDX 指向显示起始位置
    DispMess  equ  $ - CodePSeg     ;子程序DM的段内偏移
        MOV   AX, VMem_Sel
        MOV   ES, AX                ;ES用于视频存储区段
        MOV   EDI, 0B8000H          ;视频存储区的起始
        ADD   EDI, EDX              ;实际起始显示位置//@3
        MOV   AH, 47H               ;红底白字
    .L1:MOV   AL, [FS:ESI]          ;取字符
        INC   ESI
        OR    AL, AL                ;字符串以0结尾
        JZ    .L2
        MOV   [ES:EDI], AX          ;填视频存储区（显示）
        ADD   EDI, 2
        JMP   SHORT  .L1
    .L2:RETF                        ;远返回（段间返回）
    ;-------------------------------
    ;子程序B（远过程）
    ;功    能：16位二进制值转换成对应十六进制数ASCII串
    ;入口参数：DX 含二进制值
	;          FS:ESI 指向缓冲区首
    BTHStr    equ   $ - CodePSeg    ;子程序B的段内偏移//@4
        MOV   ECX, 4                ;16位二进制对应4位十六进制
    NextH: 
        ROL   DX, 4                 ;循环左移4位
        MOV   AL, DL
        CALL  HTASCII               ;转换成ASCII码
        MOV   [FS:ESI], AL          ;依次保存
        INC   ESI
        LOOP  NextH
        RETF                        ;远返回//@5
    ;-------------------------------
    ;子程序H（近过程）
    ;功    能：把一位十六进制数转换成对应字符的ASCII码
    ;入口参数：AL低4位含十六进制数
    ;出口参数：AL含对应字符的ASCII码
    HTASCII:                        ;子程序H的入口
        AND   AL, 0FH
        ADD   AL, 30H
        CMP   AL, 39H
        JBE   $+4
        ADD   AL, 7
        RET                         ;近返回
    LenCodeP  equ  $ - CodePSeg     ;代码段P的长度
    ;-----------------------------------------------------------
    ;工作任务的演示代码段D（32位段）
        align  16                   ;16字节对齐
        bits   32                   ;32位段模式
    CodeDSeg:                       ;代码段D的起始位置
    CD_Entry   equ  $ - CodeDSeg    ;入口点的段内偏移
        MOV   AX, ALDT_Sel          ;把LDT作为数据的别名段的
        MOV   GS, AX                ;描述符选择子装入GS
        MOV   EBX, CodeP.ATTRI - LDTSeg  ;代码段P描述符中属性域的偏移//@6
        MOV   DX, [GS:EBX]          ;第1次取得代码段P的属性值
        ;
        MOV   AX, DBuff_Sel
        MOV   FS, AX                ;把数据缓冲区段描述符选择子装入FS
        MOV   ESI, Buffer           ;指向缓冲区首
        ;
        CALL  CodeP_Sel:BTHStr      ;二进制值转对应十六进制数ASCII码串
        ;        
        MOV   ESI, Message          ;指向待显示字符串首
        MOV   EDX, 5*160            ;显示位置（第5行首）
        CALL  CodeP_Sel:DispMess    ;显示属性值信息
        ;
        MOV   DX, [GS:EBX]          ;第2次取得代码段P的属性值
        MOV   ESI, Buffer           ;指向缓冲区首
        CALL  CodeP_Sel:BTHStr      ;二进制值转对应十六进制数ASCII码串
        ;        
        MOV   ESI, Message          ;指向待显示字符串首
        MOV   EDX, 6*160            ;显示位置（第6行首）
        CALL  CodeP_Sel:DispMess    ;显示属性值信息
        ;
    L3: JMP   CodeT_Sel:CT_Entry2   ;跳转到代码段K
    LenCodeD  equ   $ - CodeDSeg
    ;-----------------------------------------------------------
    ;临时代码段T
        align  16                   ;16字节对齐
        bits   16                   ;32位段模式
    CodeTSeg:                       ;代码段T的起始位置
    CT_Entry1  equ  $ - CodeTSeg    ;入口1的段内偏移
        MOV   AX, LDT_Sel
        LLDT  AX                    ;装载LDTR寄存器//@7
        ;
        MOV   AX, Stack_Sel
        MOV   SS, AX                ;建立工作任务自己的堆栈
        MOV   ESP, BoStack
        ;
        JMP   CodeD_Sel:CD_Entry    ;跳转到演示代码段D
        ;---------------------------
    CT_Entry2  equ  $ - CodeTSeg    ;入口2的段内偏移
        MOV   AX, Normal_Sel        ;准备返回实方式
        MOV   DS, AX                ;把规范段描述符装入段寄存器
        MOV   ES, AX
        MOV   FS, AX
        MOV   GS, AX
        MOV   SS, AX
        MOV   EAX, CR0              ;准备切换回实方式
        AND   EAX, 0FFFFFFFEH
        MOV   CR0, EAX
        ;真正进入实方式，到达Real处
        JMP   FAR  [CS:(ToReal - CodeTSeg)]
        ;---------------------------
    ToReal:                         ;返回到实方式的地址
        dw    Real                  ;偏移部分，16位方式，偏移仅16位
        dw    0                     ;段值部分，需要重新定位
    LenCodeT  equ   $ - CodeTSeg
    ;===========================================================
    ;实方式下的数据和代码
        align  16                   ;16字节对齐
        bits   16                   ;32位段模式
    VGDTR     PDESC  LenGDT-1,0     ;GDT伪描述符
    VarESP    DD     0              ;暂存实方式的堆栈指针
    VarSS     DW     0
    ToCodeT   DW     CT_Entry1      ;代码段T入口点Entry1偏移
              DW     CodeT_Sel      ;代码段T选择子
    ;-------------------------------
    Begin:                          ;实方式的代码
        CLD
        MOV   AX, CS
        MOV   DS, AX
        MOV   [ToReal+2], AX        ;重定位，设置段值//@8
        MOV   [VarESP], ESP         ;保存实方式下堆栈指针
        MOV   [VarSS], SS
        ;
        MOV   SI, InitGDT           ;指向需要初始化的首个描述符
        MOV   CX, NumDescG          ;需要初始化的描述符个数
        CALL  InitDescBA            ;初始化GDT表中的部分描述符
        ;
        MOV   SI, LDTSeg            ;指向LDT中需要初始化的首个描述符
        MOV   CX, NumDescL          ;个数
        CALL  InitDescBA            ;初始化LDT表中的部分描述符
        ;
        MOV   SI, VGDTR             ;指向伪描述符
        MOV   BX, GDTSeg            ;指向GDT表
        CALL  InitPeDesc            ;初始化伪描述符
        ;
        LGDT  [VGDTR]               ;装载GDTR
        CLI
        MOV   EAX, CR0              ;准备切换到保护方式
        OR    EAX, 1
        MOV   CR0, EAX
        ;
        JMP   FAR  [ToCodeT]        ;进入保护方式下的代码段T
        ;---------------------------
    Real:                           ;回到实方式
        MOV   AX, CS
        MOV   DS, AX
        LSS   ESP, [VarESP]         ;恢复实方式下的堆栈指针
        STI                         ;开中断
        RETF                        ;返回
    ;-------------------------------
    %include   "PROC.ASM"           ;包含初始化阶段的相关子程序
    end_of_text:                    ;源程序到此为止
