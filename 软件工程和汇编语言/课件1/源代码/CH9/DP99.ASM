    ;演示程序dp99.asm
    ;演示异常的处理（示例九）
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
    ;临时代码段描述符及其选择子
    TempCode   DESCRIPTOR  0FFFFH,TCodeSeg,0,ATCE,0
    TCode_Sel  equ  TempCode - GDTSeg
    ;工作任务的TSS段描述符及其选择子
    DemoTSS	   DESCRIPTOR  LenDemoTSS-1,DemoTSSeg,0,ATTSS32,0
    DTSS_Sel equ  DemoTSS - GDTSeg
    ;工作任务的LDT段描述符及其选择子
    DemoLDT    DESCRIPTOR  LenDLDT-1,DemoLDTSeg,0,ATLDT,0
    DLDT_Sel   equ  DemoLDT - GDTSeg
    ;工作任务的代码段（32位段）描述符及其选择子
    DemoCode   DESCRIPTOR  LenDCode-1,DCodeSeg,0,ATCE+D32,0
    DCode_Sel  equ  DemoCode - GDTSeg
    ;工作任务的缓冲数据段描述符及其选择子
    XBUFFER    DESCRIPTOR  LenBuffer-1,BufferSeg,0,ATDW,0
    XBuff_Sel  equ  XBUFFER - GDTSeg
    ;键盘任务的TSS段描述符及其选择子
    KeyTSS     DESCRIPTOR  LenKeyTSS-1,KeyTSSeg,0,ATTSS32,0
    KTSS_Sel   equ  KeyTSS - GDTSeg
    ;键盘任务的LDT段描述符及其选择子
    KeyLDT     DESCRIPTOR  LenKLDT-1,KeyLDTSeg,0,ATLDT,0
    KLDT_Sel   equ  KeyLDT  - GDTSeg
    ;显示服务处理程序代码段（32位段）描述符及其选择子
    EchoCode   DESCRIPTOR	LenECode-1,ECodeSeg,0,ATCE+D32,0
    ECode_Sel  equ  EchoCode  - GDTSeg
    ;子程序代码段（32位段）描述符及其选择子
    SubCode    DESCRIPTOR	LenSCode-1,SCodeSeg,0,ATCE+D32,0
    SCode_Sel  equ  SubCode - GDTSeg
    ;异常处理程序代码段甲的描述符
    EXCEPTAA   DESCRIPTOR   LenExCSegAA-1,ExCodeSegAA,0,ATCE+D32,0
    ExAA_Sel   equ   EXCEPTAA - GDTSeg
    ;异常处理程序代码段乙的描述符
    EXCEPTBB   DESCRIPTOR   LenExCSegBB-1,ExCodeSegBB,0,ATCE+D32,0
    ExBB_Sel   equ   EXCEPTBB - GDTSeg
    NumDescG   equ   ($ - InitGDT) / 8     ;GDT中待初始化的描述符个数
    ;视频存储段的描述符（基地址为B8000H）及其选择子
    VideoMem   DESCRIPTOR  0FFFFH,8000H,0BH,ATDW,0
    VMem_Sel   equ   VideoMem - GDTSeg
    LenGDT     equ   $ - GDTSeg
    ;-----------------------------------------------------------
        align  16
    IDTSeg:                         ;中断描述符表IDT
    ;第00H号陷阱门（通向除法出错故障处理程序）
    INT00   GATE  DIVBegin,ExAA_Sel,0,ATTGAT32,0
    ;从01--03H的3个陷阱门
        times  3  dw  OtherBegin,ExBB_Sel,ATTGAT32<<8,0
    ;第04H号陷阱门（通向溢出陷阱处理程序）
    INT04   GATE  OFBegin,ExAA_Sel,0,ATTGAT32,0
    ;从05--0AH的6个陷阱门
        times  6  dw  OtherBegin,ExBB_Sel,ATTGAT32<<8,0
    ;第0BH号陷阱门（通向段不存在故障处理程序）
    INT0B   GATE  SNPBegin,ExAA_Sel,0,ATTGAT32,0
    ;第0CH号陷阱门（通向堆栈段故障处理程序）
    INT0C   GATE  SSEBegin,ExBB_Sel,0,ATTGAT32,0
    ;第0DH号陷阱门（通向通用故障处理程序）
    INT0D   GATE  GPBegin,ExBB_Sel,0,ATTGAT32,0
    ;从0E--EDH的240个陷阱门
        times  240  dw  OtherBegin,ExBB_Sel,ATTGAT32<<8,0
    ;第FEH号陷阱门（通向显示程序）
    INTFE   GATE  EchoBegin,ECode_Sel,0,ATTGAT32,0
    ;第FFH号任务门（通向键盘中断处理任务）
    INTFF   GATE  0,KTSS_Sel,0,ATTASKGAT,0
    LenIDT  equ   $ - IDTSeg
    ;-------------------------------
        align 16                    ;16字节对齐
        bits  32                    ;32位段模式
    ;异常处理程序的代码段甲
    ExCodeSegAA:
    DIVBegin  equ  $ - ExCodeSegAA  ;除法出错故障处理程序入口点
        MOV   ESI, MESS0            ;提示信息
        MOV   EDI, 0                ;显示的起始位置
        INT   0FEH                  ;显示提示信息
        SHR   AX, 1                 ;处理模拟的除法错误
        IRETD                       ;返回
    ;--------
    OFBegin   equ $ - ExCodeSegAA   ;溢出陷阱处理程序入口点
        MOV   ESI, MESS4            ;提示信息
        MOV   EDI, 0                ;显示的起始位置
        INT   0FEH                  ;显示提示信息
        IRETD                       ;返回
    ;--------
    SNPBegin  equ  $ - ExCodeSegAA  ;段不存在故障处理程序入口点
        MOV   ESI, MESSB
        MOV   EDI, 0
        INT   0FEH                  ;显示提示信息
        ;
        POP   EAX                   ;弹出出错代码
        CALL  SCode_Sel:SUBBegin    ;显示出错代码
        ;
        POP   EAX                   ;先弹出返回地址
        ADD   EAX, 2                ;再根据引起段不存故障指令的长度//@1
        PUSH  EAX                   ;调整返回地址
        IRETD
    LenExCSegAA  equ  $ - ExCodeSegAA
    ;-------------------------------
        align 16                    ;16字节对齐
        bits  32                    ;32位段模式
    ;异常处理程序的代码段乙
    ExCodeSegBB:
    SSEBegin  equ  $ - ExCodeSegBB  ;堆栈段故障处理程序入口点
        MOV   ESI, MESSC
        MOV   EDI,0
        INT   0FEH                  ;显示提示信息
        POP   EAX                   ;弹出出错代码
        CALL  SCode_Sel:SUBBegin    ;显示出错代码
        POP   EAX                   ;先取得返回地址
        ADD   EAX, 3                ;跳过引起堆栈段故障的指令//@2
        PUSH  EAX                   ;把调整后的返回地址压入堆栈
        IRETD
    ;--------
    GPBegin   equ  $ - ExCodeSegBB  ;通用保护故障处理程序入口点
        PUSH  EBP
        MOV   EBP, ESP
        PUSH  EAX                   ;保护部分现场
        PUSH  ESI
        PUSH  EDI
        ;
        MOV   ESI, MESSD            ;提示信息
        MOV   EDI, 0                ;显示提示信息的位置
        INT   0FEH                  ;显示出现故障的提示信息
        ;
        MOV   EAX, [EBP+4]          ;从堆栈中取故障的出错代码//@3
        CALL  SCode_Sel:SUBBegin    ;调用例程，显示出错代码
        ;
        POP   EDI
        POP   ESI                   ;恢复部分现场
        POP   EAX
        ADD   DWORD [EBP+8], 2      ;简单地调整返回地址//@4
        POP   EBP
        ADD   ESP, 4                ;废除堆栈中的出错代码
        IRETD
    ;--------
    OtherBegin  equ  $ -ExCodeSegBB ;其他中断/异常处理程序入口点
        MOV   ESI, MESSOTHER        ;提示信息首地址偏移
        MOV   EDI, 0
        INT   0FEH                  ;显示提示信息
        JMP   $                     ;进入无限循环
    LenExCSegBB   equ  $ - ExCodeSegBB
    ;-------------------------------
        align 16                    ;16字节对齐
        bits  32                    ;32位段模式
    ;显示出错代码子程序的代码段
    SCodeSeg:
    SUBBegin  equ  $ - SCodeSeg
        PUSH  EAX                   ;AX含出错代码
        PUSH  ECX
        PUSH  EDX                   ;保护部分现场
        PUSH  ESI
        PUSH  EDI
        MOV   ESI, ERRCODE
        MOV   DX, AX
        MOV   ECX, 4
    .S1:ROL   DX, 4	                ;把16位出错代码
        MOV   AL, DL                ;转成4位十六进制数的ASCII码
        AND   AL, 0FH               ;并保存
        ADD   AL, 30H
        CMP   AL, '9'
        JBE	  .S2
        ADD   AL, 7
    .S2:MOV   [ESI], AL
        INC   ESI
        LOOP  .S1
        ;
        MOV   ESI, ERRMESS
        MOV   EDI, 2*80             ;在第2行首开始
        INT   0FEH                  ;调用自带的服务功能，显示出错代码
        POP   EDI
        POP   ESI
        POP   EDX                   ;恢复部分现场
        POP   ECX
        POP   EAX
        RETF
    LenSCode  equ  $ - SCodeSeg
    ;-------------------------------
        align 16                    ;16字节对齐
        bits  32                    ;32位段模式
    ;实现显示功能的服务程序（陷阱处理程序形式）的代码段
    ECodeSeg:
    EchoBegin   equ  $ - ECodeSeg	
    ;DS:ESI指向显示信息串，ES:EDI指向显示缓冲区
        PUSHAD                      ;保护现场
        CLD
        MOV   AH, 4EH               ;红底黄字
        MOV   AL, 20H               ;空格
        MOV   ECX, 80*2             ;每行80个字符
        PUSH  EDI
        REP   STOSW                 ;显示空格（清空指定行及下一行）
        POP   EDI
    .E1:LODSB
        OR   AL, AL
        JZ   .E2
        STOSW                       ;显示指定信息
        JMP  SHORT .E1
    .E2:POPAD                       ;恢复现场
        IRETD                       ;返回
    LenECode  equ  $ - ECodeSeg
    ;-----------------------------------------------------------
        align 16                    ;16字节对齐
    ;键盘任务的局部描述符表LDT
    KeyLDTSeg:
    ;键盘任务的代码段描述符及其选择子
    KeyCode     DESCRIPTOR	0FFFFH,KCodeSeg,0,ATCE,0
    KCode_Sel   equ  (KeyCode - KeyLDTSeg) +TIL
    ;键盘任务的堆栈段描述符及其选择子
    KeyStack    DESCRIPTOR  LenKStack-1,KStackSeg,0,ATDW,0
    KStack_Sel  equ  (KeyStack - KeyLDTSeg) +TIL
    NumDescKL   equ  ($ - KeyLDTSeg) / 8     ;键盘任务LDT中描述符个数
    LenKLDT     equ  $ - KeyLDTSeg
    ;-------------------------------
        align 16                    ;16字节对齐
    ;键盘任务的TSS段
    KeyTSSeg:
        DW   0,0                    ;链接字
        DD   0                      ;0级堆栈指针
        DW   0,0
        DD   0                      ;1级堆栈指针
        DW   0,0
        DD   0                      ;2级堆栈指针
        DW   0,0
        DD   0                      ;CR3
        DW   KeyBegin, 0            ;EIP（入口点偏移）
        DD   0                      ;EFLAGS
        DD   01234h                 ;EAX
        DD   05678h                 ;ECX
        DD   0                      ;EDX
        DD   0                      ;EBX
        DW   LenKStack, 0           ;ESP（进入时的堆栈顶偏移）
        DD   0                      ;EBP
        DD   0                      ;ESI
        DD   0                      ;EDI
        DW   Normal_Sel, 0          ;ES
        DW   KCode_Sel, 0           ;CS
        DW   KStack_Sel, 0          ;SS
        DW   VMem_Sel, 0            ;DS
        DW   Normal_Sel, 0          ;FS
        DW   Normal_Sel, 0          ;GS
        DW   KLDT_Sel, 0            ;LDT
        DW   0                      ;TSS的特别属性字
        DW   $+2 -  KeyTSSeg        ;指向I/O许可位图区的指针
        DB   0FFH                   ;I/O许可位图结束字节
    LenKeyTSS   equ   $ - KeyTSSeg
    ;-----------------------------------------------------------
    ;键盘任务的堆栈段（16位段）
        align 16                    ;16字节对齐
    KStackSeg:
    LenKStack   equ  512
            times  LenKStack  db  0
    ;-----------------------------------------------------------
    ;键盘任务代码段（16位段）
        align 16                    ;16字节对齐
        bits  16                    ;16位段模式
    KCodeSeg:
    KeyBegin   equ  $ - KCodeSeg
        PUSH  DS
        PUSH  ES
        PUSH  FS
        PUSH  GS
        MOV   AX, Normal_Sel
        MOV   SS, AX                ;准备回到实方式
        MOV   EAX, CR0
        AND   EAX, 0FFFFFFFEH
        MOV   CR0, EAX              ;回到实方式
    ToReal2:                        ;真正回到实方式
        JMP   0:GetKey1             ;需要重定位
    GetKey1:                        ;现在是实方式
        MOV   AX, CS
        MOV   DS, AX
        MOV   EBP, ESP              ;恢复实方式部分现场
        MOV   SS, [SSVar]           ;LSS   SP, [SPVar]
        MOV   SP, [SPVar]           ;恢复实方式下的堆栈指针
        LIDT  [NORVIDTR]            ;恢复实方式下的中断向量表
        STI
        ;
    GetKey2:                        ;调用BIOS功能，显示提示信息
        MOV   SI, Prompt
        MOV   AH, 14                ;TTY方式显示
        MOV   BH, 0                 ;0页
    .L1:LODSB
        OR    AL, AL                ;字符串以0结尾
        JZ    GetKey3
        INT   10H                   ;调用BIOS，显示字符
        JMP   SHORT  .L1
    GetKey3:                        ;调用BIOS功能，接受键盘输入
        MOV   AH, 0
        INT   16H                   ;调用BIOS，取得键盘输入
        CMP   AL, '0'               ;只有[0,4,B,C,D]有效
        JZ    GetKey4
        CMP   AL, '4'               ;只有[0,4,B,C,D]有效
        JZ    GetKey4
        AND   AL, 11011111B         ;字母小写转大写
        CMP   AL, 'B'
        JB    GetKey3
        CMP   AL, 'D'               ;只有[0,4,B,C,D]有效
        JA    GetKey3
    GetKey4:
        MOV   AH, 14
        INT   10H                   ;显示所按字符
    GetKey5:
        MOV   [KeyVar], AL          ;保存到交换缓冲数据段
        ;
        MOV   AL, 0DH
        INT   10H                   ;形成回车换行的效果
        MOV   AL, 0AH
        INT   10H
    GetKey6:
        CLI                         ;准备再次进入保护方式
        LIDT  [VIDTR]
        MOV   EAX, CR0
        OR    EAX, 1
        MOV   CR0, EAX              ;再次进入保护方式
        JMP   KCode_Sel:GetKeyV
        ;
    GetKeyV   equ  $ - KCodeSeg
        MOV   AX, KStack_Sel        ;又到了保护方式
        MOV   SS, AX
        MOV   ESP, EBP
        POP   GS
        POP   FS
        POP   ES
        POP   DS
        IRETD                       ;键盘任务结束，返回
        JMP   KeyBegin              ;下次进入任务时的入口点//@5
    LenKCode   equ  $ - KCodeSeg
    ;-------------------------------
    ;交换缓冲区数据段
        align 16                    ;16字节对齐
    BufferSeg:
    KeyASCII  equ  $ - BufferSeg
    KeyVar     db   0
    Buffer    equ  $ - BufferSeg
        times   128  db  0
    LenBuffer   equ  $ - BufferSeg
    ;-------------------------------
    ;工作任务的局部描述符表段
        align 16                    ;16字节对齐
    DemoLDTSeg:
    ;工作任务的堆栈段描述符及其选择子
    DemoStack  DESCRIPTOR   LenDStack-1,DStackSeg,0,ATDW+D32,0
    DStack_Sel equ   (DemoStack - DemoLDTSeg) +TIL
    ;工作任务的数据段描述符及其选择子
    DEMODATA   DESCRIPTOR   LenDData-1,DDataSeg,0,ATDW,0
    DData_Sel  equ   (DEMODATA - DemoLDTSeg) +TIL
    ;为模拟段不存在故障而安排的数据段描述符
    TESTNPS    DESCRIPTOR   0FFFFH,0,0,ATDW-80H,0     ;//@N
    TNPS_Sel   equ  (TESTNPS - DemoLDTSeg) +TIL
    ;该LDT中需要初始化基地址的描述符个数
    DemoLDNUM  equ   ($ - DemoLDTSeg)/ 8
    LenDLDT    equ   $ - DemoLDTSeg
    ;-----------------------------------------------------------
    ;工作任务的TSS段
        align 16                    ;16字节对齐
    DemoTSSeg:
    DemoTaskSS   TASKSS
        db   0FFH
    LenDemoTSS   equ  $ - DemoTSSeg
    ;-------------------------------
    ;工作任务的堆栈段
        align 16                    ;16字节对齐
    DStackSeg:
    LenDStack   equ  1024
        times  LenDStack  db   0
    ;-------------------------------
    ;工作任务的数据段
    DDataSeg:
    MESS0   equ  $ - DDataSeg
        DB  'Divide Error Exception (#DE)',0
    MESS4   equ  $ - DDataSeg
        DB  'Overflow Exception (#OF)',0
    MESSB   equ  $ - DDataSeg
        DB  'Segment Not Present (#NP)',0
    MESSC   equ  $ - DDataSeg
        DB  'Stack Fault Exception (#SS)',0
    MESSD   equ  $ - DDataSeg
        DB  'General Protection Exception (#GP)',0
    MESSOTHER   equ  $ - DDataSeg
        DB  'Other Execption',0
    ERRMESS equ  $ - DDataSeg
        DB  'Error Code = '
    ERRCODE equ  $ - DDataSeg
        DB  '0000H',0
    LenDData  equ  $ - DDataSeg
    ;-------------------------------
    ;工作任务代码段（演示代码段）
        align 16                    ;16字节对齐
        bits  32                    ;32位段模式
    DCodeSeg:
    DemoBegin   equ  $ - DCodeSeg
        MOV   AX, DLDT_Sel
        LLDT  AX                    ;装载LDTR
        MOV   AX, DStack_Sel
        MOV   SS, AX                ;置堆栈指针
        MOV   ESP, LenDStack
        ;使得TR指向工作任务的TSS
        MOV   AX, DTSS_Sel
        LTR   AX
        ;装载其他数据段寄存器
        MOV   AX, DData_Sel
        MOV   DS, AX                ;工作任务数据段
        MOV   AX, VMem_Sel
        MOV   ES, AX                ;视频存储区
        MOV   AX, XBuff_Sel
        MOV   FS, AX                ;数据交换缓冲区段
        MOV   AX, XBuff_Sel
        MOV   GS, AX                ;数据交换缓冲区段
        ;接收需要模拟的异常的类型号（由字符表示）
        INT   0FFH
        ;根据接收到的字符，分别故意引起相应的异常（模拟之）
        MOV   AL, [FS:KeyASCII]
        CMP   AL, '0'
        JNZ   Demo4
    Exception0:                     ;模拟除法出错故障
        MOV   AX, 1000
        MOV   CL, 2                 ;商太大，将引起除出错异常
        DIV   CL                    ;本指令长2字节//@6
        JMP   OVER
    Demo4:
        CMP   AL, '4'
        JNZ   Demo11
    Exception4:                     ;模拟溢出陷阱
        MOV   AL, 100
        ADD   AL, 50                ;单字节有符号数最大127，使得OF=1
        INTO                        ;因OF=1，将引起异常//@7
        JMP		OVER
    Demo11:
        CMP   AL, 'B'
        JNZ   Demo12
    Exception11:                    ;模拟段不存在故障
        MOV   AX, TNPS_Sel          ;段选择子指示描述符的P位=0
        MOV   GS, AX                ;引起段不存在故障（指令长2字节）
        JMP   OVER                  ;//@8
    Demo12:
        CMP   AL, 'C'
        JNZ   Demo13
    Exception12:                    ;模拟堆栈出错故障
        MOV   EBX, ESP
        MOV   AL, [SS:EBX]          ;超出堆栈边界（指令长3字节）//@9
        JMP   OVER
    Demo13:
    Exception13:                    ;模拟通用保护故障
        MOV   AX, DTSS_Sel          ;这是指示TSS描述符的选择子
        MOV   GS, AX                ;把TSS作为数据段（指令长2字节）
    ;------
    OVER:                           ;转临时代码段
        JMP   TCode_Sel:PM_Entry2
    LenDCode   equ  $ - DCodeSeg
    ;-------------------------------
    ;保护方式下的临时代码段
        align 16                    ;16字节对齐
        bits  16                    ;16位段模式
    TCodeSeg:
    PM_Entry1  equ  $ - TCodeSeg
        JMP   DCode_Sel:DemoBegin   ;转演示程序
        ;
    PM_Entry2  equ  $ - TCodeSeg
        MOV   AX, Normal_Sel        ;准备切换回实方式
        MOV   DS, AX
        MOV   ES, AX
        MOV   FS, AX                ;加载规范描述符
        MOV   GS, AX
        MOV   SS, AX
        MOV   EAX, CR0
        AND   EAX, 0FFFFFFFEH
        MOV   CR0, EAX              ;返回实方式
    ToReal:                         ;真正进入实方式
        JMP   0:Real                ;需要重定位
    ;===============================
    ;实方式下的数据段
    RDataSeg:
    VGDTR     PDESC  LenGDT-1,0      ;GDT伪描述符
    VIDTR     PDESC  LenIDT-1,0      ;IDT伪描述符
    NORVIDTR  PDESC  3FFH,0          ;用于保存原IDTR值
    SPVar     DW     0               ;暂存实方式的堆栈指针
    SSVar     DW     0
    Prompt    DB     "Strike a key [0,4,B,C,D]:",0   ;提示信息
    ;-------------------------------
    ;实方式下的代码段
        bits   16
    Begin:
        CLD
        MOV   AX, CS
        MOV   DS, AX
        MOV   [ToReal+3], AX        ;重定位（调整返回指令中的段值）
        MOV   [ToReal2+3], AX       ;重定位（调整另一处返回指令中的段值）
        ;
        MOV   SI, InitGDT
        MOV   CX, NumDescG
        CALL  InitDescBA            ;按位移，设置GDT中的描述符基地址
        MOV   SI, VGDTR
        MOV   BX, GDTSeg
        CALL  InitPeDesc            ;初始化用于GDTR的伪描述符
        MOV   SI, VIDTR
        MOV   BX, IDTSeg
        CALL  InitPeDesc            ;初始化用于IDTR的伪描述符
        ;
        MOV   SI, DemoLDTSeg
        MOV   CX, DemoLDNUM
        CALL  InitDescBA            ;初始化工作任务LDT
        MOV   SI, KeyLDTSeg
        MOV   CX, NumDescKL
        CALL  InitDescBA            ;初始化键盘任务LDT
        ;
        MOV   AX, DLDT_Sel          ;初始化工作任务TSS
        MOV   [DemoTaskSS.TRLDT],AX ;把工作任务LDT的选择子填入TSS
        ;
        MOV   [SSVar], SS
        MOV   [SPVar], SP           ;保存堆栈指针
        SIDT  [NORVIDTR]            ;保存IDTR值
        ;
        LGDT  [VGDTR]               ;装载GDTR
        CLI
        LIDT  [VIDTR]               ;置IDTR
        MOV   EAX, CR0              ;准备切换到保护方式
        OR    EAX, 1
        MOV   CR0, EAX
		JMP   TCode_Sel:PM_Entry1   ;进入保护方式下的临时代码段
    ;-------------------
    Real:                           ;又回到实方式
        MOV   AX, CS
        MOV   DS, AX
        LSS   SP, [SPVar]           ;恢复实方式下的堆栈指针
        LIDT  [NORVIDTR]            ;恢复原IDTR
        STI                         ;开中断
        RETF                        ;结束演示，返回
    ;------------------------------
    %include   "PROC.ASM"           ;包含初始化阶段的相关子程序
    end_of_text:                    ;源代码到此为止
