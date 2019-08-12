    ;演示程序dp95.asm
    ;演示任务内特权级不变的转移（示例五）
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
    InitGDT:                                ;GDT中待初始化的描述符起点
    ;任务的临时代码段的描述符及其选择子
    TempCode     DESCRIPTOR  0FFFFH,TCodeSeg,0,ATCE,0
    TCode_Sel    equ   TempCode - GDTSeg
    ;任务的演示代码段描述符（32位段）及其选择子
    DemoCode     DESCRIPTOR  LenDCode-1,DCodeSeg,0,ATCER+D32,0
    DCode_Sel    equ   DemoCode - GDTSeg
    ;任务的子程序代码段描述符（32位段）及其选择子
    SubCode      DESCRIPTOR  LenSCode-1,SCodeSeg,0,ATCE+D32,0
    SCode_Sel    equ   SubCode - GDTSeg
    ;任务的堆栈段描述符（32位段）及其选择子
    DemoStack    DESCRIPTOR  LenStack-1,StackSeg,0,ATDW+D32,0
    Stack_Sel    equ   DemoStack - GDTSeg
    ;任务的数据段描述符及其选择子
    DemoData     DESCRIPTOR  LenData-1,DataSeg,0,ATDR+DPL2,0    ;//@1
    Data_Sel     equ   DemoData - GDTSeg +RPL1                  ;//@2
    NumDescG     equ   ($ - InitGDT) / 8    ;GDT中待初始化的描述符个数 
    ;视频存储段的描述符（DPL=3）及其选择子
    VideoMem     DESCRIPTOR  0FFFFH,8000H,0BH,ATDW+DPL3,0
    VMem_Sel     equ   VideoMem - GDTSeg +RPL2
    LenGDTSeg    equ   $ - GDTSeg
    ;-------------------------------
    ;任务的0级堆栈段（32位段）
        align   16                  ;16字节对齐
    StackSeg:
	LenStack    equ  512
        times   LenStack   DB   0
    ;-------------------------------
    ;任务的子程序代码段（32位段）
        align  16                   ;16字节对齐
        bits   32                   ;32位段模式
    SCodeSeg:
    ;显示返回地址的偏移部分
    SubBegin  equ  $  - SCodeSeg
        PUSH  EBP
        MOV   EBP, ESP
        MOV   AX, VMem_Sel
        MOV   ES, AX                ;视频存储段基地址000B8000H
        MOV   EDI, [EBP+16]         ;取得参数（屏幕位置）//@3
        MOV   EDX, [EBP+12]         ;取得参数（显示值）//@4
        MOV   AH, 4EH               ;显示颜色（红底黄字）
        MOV   ECX, 8                ;8个十六进制位
    .L1:ROL   EDX, 4
        MOV   AL, DL
        AND   AL, 0FH               ;取得4个二进制位
        ADD   AL, 30H               ;转对应十六进制数ASCII码
        CMP   AL, 39H
        JBE   SHORT .L2
        ADD   AL, 7
    .L2:STOSW                       ;显示字符
        LOOP  .L1
        POP   EBP
        RETF                        ;段间返回
    LenSCode   equ   $ - SCodeSeg
    ;-------------------------------
    ;任务的数据段（DPL=2）
        align   16                  ;16字节对齐
    DataSeg:
    PtoSubR    equ  $ - DataSeg
               DD   SubBegin        ;//@5
               DW   SCode_Sel       ;//@6
    PtoTCode   equ  $ - DataSeg
               DD   PM_Entry2
               DW   TCode_Sel
	LenData    equ  $ - DataSeg
    ;-------------------------------
    ;任务的演示代码段（32位段）
        align  16                   ;16字节对齐
        bits   32                   ;32位段模式
    DCodeSeg:
    DemoBegin equ   $  -  DCodeSeg
        MOV   AX, CS
        MOV   DS, AX
        ;
        MOV   EAX, 5*80*2           ;显示位置（第5行首）
        PUSH  EAX                   ;压入堆栈//@7
        MOV   EAX, 12345678H        ;假设的显示值
        PUSH  EAX                   ;压入堆栈//@8
        CALL  SCode_Sel:SubBegin    ;直接方式，调用子程序
        ADD   EBP, 8
        ;
        MOV   AX, Data_Sel
        MOV   GS, AX                ;用于数据段//@9
        ;
        PUSH  DWORD  6*80*2         ;显示开始位置（第6行首）
        PUSH  DWORD  87654321H      ;假设的显示值
        CALL  FAR  [GS:PtoSubR]     ;间接方式，调用子程序
        ADD   EBP, 8
        ;
        JMP   FAR  [GS:PtoTCode]    ;间接方式，转入临时代码段
    LenDCode  equ  $ - DCodeSeg
    ;-------------------------------
    ;任务的临时代码段（16位段）
        align  16                   ;16字节对齐
        bits   16                   ;16位段模式
    TCodeSeg:
    PM_Entry1   equ  $ - TCodeSeg
        MOV   AX, Stack_Sel         ;可省略
        MOV   SS, AX
        MOV   ESP, LenStack
        JMP   DCode_Sel:DemoBegin   ;直接方式，转入演示代码段
    ;---------
    PM_Entry2  equ  $ - TCodeSeg    ;准备切换回实方式
        MOV   AX, Normal_Sel
        MOV   DS, AX
        MOV   ES, AX                ;把规范段描述符
        MOV   GS, AX
        MOV   SS, AX
        MOV   EAX, CR0              ;准备返回实方式
        AND   AX, 0FFFEH
        MOV   CR0, EAX
    ToReal:                         ;真正回到实方式
        JMP   0:Real
    LenTCode  equ  $ - TCodeSeg
    ;=========================================
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
        MOV   SI, VGDTR
        MOV   BX, GDTSeg
        CALL  InitPeDesc            ;初始化用于GDT的伪描述符
        ;
        LGDT  [VGDTR]               ;装载GDTR
        CLI
        MOV   EAX, CR0              ;准备切换到保护方式
        OR    AX, 1
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
