    ;演示程序dp96.asm
    ;演示任务内特权级变换的转移（示例六）
    %include  "DMC.H"               ;文件DMC.H含有宏的声明和符号常量等
    ;-----------------------------------------------------------
        section  text               ;段text
        bits     16                 ;16位段模式
    Head:                           ;工作程序特征信息
        HEADER   end_of_text, Begin, 2000H
    ;-----------------------------------------------------------
    GDTSeg:                                 ;任务全局描述符表GDT
    Dummy        DESCRIPTOR  0,0,0,0,0      ;哑描述符
    Normal       DESCRIPTOR  0FFFFH,0,0,ATDW,0
    Normal_Sel   equ   Normal - GDTSeg      ;规范段描述符的选择子
    InitGDT:                                ;GDT中待初始化的描述符
    ;工作任务TSS段的描述符(DPL=0)及其选择子
    DemoTSS    DESCRIPTOR  LenTSS-1,TSSeg,0,ATTSS32,0
    TSS_Sel    equ  DemoTSS - GDTSeg
    ;工作任务LDT段的描述符(DPL=0)及其选择子
    DemoLDT    DESCRIPTOR  LenLDT-1,LDTSeg,0,ATLDT,0
    LDT_Sel    equ   DemoLDT - GDTSeg
    ;临时代码段的描述符(DPL=0)及其选择子
    TempCode   DESCRIPTOR  0FFFFH,TCSeg,0,ATCE,0
    TCode_Sel  equ  TempCode - GDTSeg
    NumDescG   equ  ($ - InitGDT)/8 ;GDT中待初始化的描述符个数 
    ;视频存储段的描述符(DPL=3)及其选择子
    VideoMem   DESCRIPTOR  0FFFFH,8000H,0BH,ATDW+DPL3,0
    VMem_Sel   equ	 VideoMem - GDTSeg
    LenGDTSeg  equ   $ - GDTSeg
    ;-------------------------------
    LDTSeg:                         ;工作任务局部描述符表LDT
    ;工作任务的0级堆栈段描述符(32位段，DPL=0)及其选择子
    DemoStack0   DESCRIPTOR  LenStack0-1,Stack0Seg,0,ATDW+D32,0
    Stack0_Sel   equ  (DemoStack0 - LDTSeg) +TIL
    ;工作任务的1级堆栈段描述符(32位段，DPL=1)及其选择子
    DemoStack1   DESCRIPTOR  LenStack1-1,Stack1Seg,0,ATDW+D32+DPL1,0
    Stack1_Sel   equ  (DemoStack1 - LDTSeg) +TIL +RPL1
    ;工作任务的3级堆栈段描述符(DPL=3)及其选择子
    DemoStack3   DESCRIPTOR  LenStack3-1,Stack3Seg,0,ATDW+D32+DPL3,0
    Stack3_Sel   equ  (DemoStack3 - LDTSeg) +TIL +RPL3
    ;演示代码段描述符(32位段，DPL=3)及其选择子
    DemoCode     DESCRIPTOR  LenDCode-1,DCodeSeg,0,ATCE32+DPL3,0
    DCode_Sel    equ  (DemoCode - LDTSeg) +TIL +RPL3
    ;过渡代码段描述符(32位段，DPL=0)及其选择子
    InteCode     DESCRIPTOR  LenICode-1,ICodeSeg,0,ATCE32,0
    ICode_Sel    equ  (InteCode - LDTSeg) +TIL
    ;子程序代码段描述符(32位段，DPL=1)及其选择子
    SubCode      DESCRIPTOR  LenSCode-1,SCodeSeg,0,ATCER+D32+DPL1,0
    SCode_Sel1   equ  (SubCode - LDTSeg) +TIL +RPL1
    SCode_Sel3   equ  (SubCode - LDTSeg) +TIL +RPL3         ;//@1
    NumDescL     equ  ($ - LDTSeg) / 8      ;LDT中需要初始化的描述符个数
    ;指向过渡代码段内ICBegin点的调用门(DPL=2)
    PTGateA      GATE  ICBegin,ICode_Sel,0,ATCGAT32+DPL2,0
    PTGateA_Sel  equ   (PTGateA - LDTSeg) +TIL +RPL1        ;//@2
    ;指向过渡代码段内ICodeEnd点的调用门(DPL=3)
    PTGateB      GATE  ICodeEnd,ICode_Sel,0,ATCGAT32+DPL3,0  ;//@3
    PTGateB_Sel  equ   (PTGateB - LDTSeg) +TIL +RPL2         ;//@4
    ;指向显示子程序的调用门(DPL=3)
    PSubGate     GATE  SubBegin,SCode_Sel3,0,ATCGAT32+DPL3,0
    PSGate_Sel   equ   (PSubGate - LDTSeg) +TIL +RPL3
    LenLDT       equ   $ - LDTSeg          ;LDT的长度
    ;-----------------------------------------------------------
    TSSeg:                          ;示例任务的状态段TSS
        DW   0,0                    ;链接字段
        DD   LenStack0              ;0级堆栈指针
        DW   Stack0_Sel,0           ;初始化
        DD   LenStack1              ;1级堆栈指针
        DW   Stack1_Sel,0           ;初始化
        DD   0                      ;2级堆栈指针（未使用）
        DW   0,0                    ;未初始化（未使用）
        DD   0                      ;CR3
        DD   0                      ;EIP
        DD   0                      ;EFLAGS
        DD   0                      ;EAX
        DD   0                      ;ECX
        DD   0                      ;EDX
        DD   0                      ;EBX
        DD   0                      ;ESP
        DD   0                      ;EBP
        DD   0                      ;ESI
        DD   0                      ;EDI
        DW   0,0                    ;ES
        DW   0,0                    ;CS
        DW   0,0                    ;SS
        DW   0,0                    ;DS
        DW   0,0                    ;FS
        DW   0,0                    ;GS
        DW   LDT_Sel,0              ;LDT
        DW   0
        DW   $+2                    ;指向I/O许可位图
        DB   0FFH                   ;I/O许可位图结束标志
    LenTSS   equ   $  - TSSeg
    ;-------------------------------
    ;工作任务的0级堆栈段(32位段)
        align   16                  ;16字节对齐
    Stack0Seg:
	LenStack0   equ  512
        times   LenStack0   DB   0
    ;工作任务的1级堆栈段(32位段)
    Stack1Seg:
	LenStack1   equ  512
        times   LenStack1   DB   0
    ;工作任务的3级堆栈段(32位段)
    Stack3Seg:
	LenStack3   equ  512
        times   LenStack3   DB   0
    ;-------------------------------
    ;工作任务的子程序代码段(32位段，1级)
        align  16                   ;16字节对齐
        bits  32                    ;32位段模式
    SCodeSeg:
    Message    equ  $ - SCodeSeg
        DB     'CPL=',0
    ;---------
    ;子程序代码段(32位段，1级)
    ;显示主调程序的执行特权级
    SubBegin  equ  $  - SCodeSeg
        PUSH  EBP
        MOV   EBP, ESP
        MOV   AX, SCode_Sel1        ;子程序代码段是可读段
        MOV   DS, AX                ;采用RPL=1的选择子
        MOV   AX, VMem_Sel
        MOV   ES, AX                ;视频存储段基地址000B8000H
        MOV   EDI, 5*80*2           ;显示开始位置（第5行首）
        MOV   ESI, Message
        MOV   AH, 4EH               ;红底黄字
    .L1:LODSB
        OR    AL, AL                ;字符串以0结尾
        JZ    SHORT .L2
        STOSW                       ;显示字符
        JMP   SHORT .L1
    .L2:MOV   EAX, [EBP+8]          ;从堆栈中取得主调程序的CS //@*
        AND   AL, 3                 ;主调程序的CPL在CS的RPL字段
        ADD   AL, '0'
        MOV   AH, 4EH               ;红底黄字
        STOSW                       ;显示之
        POP   EBP
        RETF                        ;段间返回//@5
    LenSCode   equ   $ - SCodeSeg
    ;-------------------------------
    ;工作任务的演示代码段(32位段，3级)
        align  16                   ;16字节对齐
        bits   32                   ;32位段模式
    DCodeSeg:
    DCBegin   equ   $  -  DCodeSeg
        OR    EAX, EAX              ;装装样子，可省略
        CALL  PSGate_Sel:345678H    ;显示当前特权级(变换到1级)//@6
    DCLab:
        OR    EAX, EAX              ;装装样子，可省略
        CALL  PTGateB_Sel:0         ;转到过渡代码段(变换到0级)//@7
    LenDCode  equ  $ - DCodeSeg
    ;-------------------------------
    ;工作任务的过渡代码段(32位段，0级)
        align  16                   ;16字节对齐
        bits   32                   ;32位段模式
    ICodeSeg:
    ICBegin   equ  $ - ICodeSeg
        MOV   AX, Stack0_Sel
        MOV   SS, AX                ;建立0级堆栈
        MOV   ESP, LenStack0
        ;
        PUSH  DWORD  Stack3_Sel     ;压入3级堆栈指针//@8
        PUSH  DWORD  LenStack3
        ;
        PUSH  DWORD  DCode_Sel      ;压入演示代码入口点（选择子）
        PUSH  DWORD  DCBegin        ;偏移//@9
        ;
        RETF                        ;转3级的演示代码段//@A
        ;
    ICodeEnd  equ  $ - ICodeSeg     ;转临时代码段
        OR    EAX, EAX              ;装装样子，可以省略
        JMP   TCode_Sel:PM_Entry2
    LenICode  equ   $ - ICodeSeg
    ;-------------------------------
    ;临时代码段(16位段，0级)
        align  16                   ;16字节对齐
        bits   16                   ;16位段模式
    TCSeg:
    PM_Entry1   equ  $ - TCSeg
        MOV   AX, TSS_Sel
        LTR   AX                    ;装载TR  //@B
        ;
        MOV   BX, LDT_Sel
        LLDT  BX                    ;装载LDTR
        ;
        JMP   PTGateA_Sel:9999H     ;通过调用门转过渡段
    ;---------
    PM_Entry2  equ  $ - TCSeg       ;准备切换回实方式
        MOV   AX, Normal_Sel
        MOV   DS, AX
        MOV   ES, AX                ;把规范段描述符
        MOV   FS, AX                ;装入各数据段寄存器
        MOV   GS, AX
        MOV   SS, AX
        MOV   EAX, CR0              ;准备返回实方式
        AND   AX, 0FFFEH
        MOV   CR0, EAX
    ToReal:                         ;真正回到实方式
        JMP   0:Real
    LenTCode  equ  $ - TCSeg
    ;===========================================================
    ;实方式的数据
    VGDTR     PDESC  LenGDTSeg-1,0   ;GDT伪描述符
    VarESP    DD     0               ;暂存实方式的堆栈指针
    VarSS     DW     0
    ;-------------------------------
    ;实方式的代码
        bits  16
    Begin:
        CLD
        MOV   AX, CS
        MOV   DS, AX
        MOV   [ToReal+3], AX        ;重定位
        MOV   [VarESP], ESP         ;保存实方式下堆栈指针
        MOV   [VarSS], SS
        MOV   SI, InitGDT
        MOV   CX, NumDescG
        CALL  InitDescBA            ;设置GDT中的待初始化描述符的基地址
        MOV   SI, LDTSeg
        MOV   CX, NumDescL
        CALL  InitDescBA            ;设置LDT中的 待初始化描述符的基地址
        MOV   SI, VGDTR
        MOV   BX, GDTSeg
        CALL  InitPeDesc            ;初始化用于GDT的伪描述符
        ;
        LGDT  [VGDTR]               ;装载GDTR
        CLI
        MOV   EAX, CR0              ;准备切换到保护方式
        OR    EAX, 1
        MOV   CR0, EAX
        JMP   TCode_Sel:PM_Entry1   ;进入保护方式下的临时代码段
        ;---------------------------
    Real:                           ;回到实方式
        MOV   AX, CS
        MOV   DS, AX
        LSS   ESP, [VarESP]         ;恢复实方式下的堆栈指针
        STI                         ;开中断
        RETF                        ;返回加载器
    ;------------------------------
    %include   "PROC.ASM"           ;包含初始化阶段的相关子程序
    end_of_text:                    ;源代码到此为止
