    ;演示程序dp97.asm
    ;演示任务的切换（示例七）
    %include  "DMC.H"               ;文件DMC.H含有宏的声明和符号常量等
    ;-----------------------------------------------------------
        section  text               ;段text
        bits     16                 ;16位段模式
    Head:                           ;工作程序特征信息
        HEADER   end_of_text, Begin, 2000H
    ;-----------------------------------------------------------
    GDTSeg:                         ;工作任务的全局描述符表GDT
    Dummy      DESCRIPTOR  0,0,0,0,0    ;哑描述符
    Normal     DESCRIPTOR  0FFFFH,0,0,ATDW,0
    Normal_Sel equ   Normal - GDTSeg    ;规范段描述符的选择子
    InitGDT:                            ;GDT中待初始化的描述符
    ;工作任务TSS段的描述符(DPL=0)及其选择子(RPL=0)
    DemoTSS    DESCRIPTOR  LenDTSS-1,DTSSeg,0,ATTSS32,0
    DTSS_Sel   equ  DemoTSS - GDTSeg                        ;//@1
    ;工作任务LDT段的描述符(DPL=0)及其选择子(RPL=0)
    DemoLDT    DESCRIPTOR  LenDLDT-1,DLDTSeg,0,ATLDT,0
    DLDT_Sel   equ  DemoLDT - GDTSeg
    ;子程序代码段描述符(DPL=0)及其选择子(RPL=3)
    SubCode    DESCRIPTOR  LenSCode-1,SCodeSeg,0,ATCE+D32,0 ;//@2
    SCode_Sel3 equ  (SubCode - GDTSeg) +RPL3
    ;临时任务的任务状态段描述符(DPL=2)及其选择子(RPL=0)
    TempTSS    DESCRIPTOR  LenTTSS-1,TTSSeg,0,ATTSS32+DPL2,0
    TTSS_Sel   equ  TempTSS - GDTSeg
    ;临时代码段的描述符(DPL=0)及其选择子(RPL=0)
    TempCode   DESCRIPTOR  0FFFFH,TCSeg,0,ATCE,0
    TCode_Sel  equ  TempCode - GDTSeg
    NumDescG   equ  ($ - InitGDT)/8 ;GDT中待初始化的描述符个数 
    ;视频存储段的描述符(DPL=3)及其选择子(RPL=0)
    VideoMem   DESCRIPTOR  0FFFFH,8000H,0BH,ATDW+DPL3,0
    VMem_Sel   equ	VideoMem - GDTSeg
    LenGDT     equ  $ - GDTSeg
    ;-----------------------------------------------------------
        align  16                   ;16字节对齐
    ;工作任务的状态段TSS（为了便于预置方式初始化，没有采用宏）
    DTSSeg:
        DW   0, 0                   ;链接字段
        DD   LenStack0              ;0级堆栈指针
        DW   Stack0_Sel, 0          ;初始化
        DD   0                      ;1级堆栈指针（未使用）
        DW   0, 0                   ;未初始化（未使用）
        DD   LenStack2              ;2级堆栈指针
        DW   Stack2_Sel, 0          ;初始化
        DD   0                      ;CR3
        DD   DBegin                 ;EIP工作任务的入口点  //@3
        DD   0                      ;EFLAGS
        DD   0                      ;EAX
        DD   0                      ;ECX
        DD   0                      ;EDX
        DD   0                      ;EBX
        DD   LenStack2              ;ESP工作任务的堆栈指针
        DD   0                      ;EBP
        DD   0                      ;ESI
        DD   80                     ;EDI（显示位置，首行中间）
        DW   VMem_Sel, 0			;ES视频存储段
        DW   DCode_Sel, 0           ;CS工作任务的代码段  //@4
        DW   Stack2_Sel, 0          ;SS工作任务的堆栈段选择子
        DW   DData_Sel, 0           ;DS工作任务的数据段
        DW   ALDT_Sel, 0            ;FS别名段（对应临时任务LDT）
        DW   ATTSS_Sel, 0           ;GS别名段（对应临时任务TSS）
        DW   DLDT_Sel, 0            ;LDTR工作任务的LDT段
        DW   0
        DW   $+2 - DTSSeg           ;指向I/O许可位图
        DB   0FFH                   ;I/O许可位图结束标志
    LenDTSS  equ   $  - DTSSeg
    ;-------------------------------
        align  16                   ;16字节对齐
    DLDTSeg:                        ;工作任务的局部描述符表LDT
    ;工作任务的0级堆栈段描述符(DPL=0)及其选择子(RPL=0)
    DemoStack0   DESCRIPTOR  LenStack0-1,Stack0Seg,0,ATDW+D32,0
    Stack0_Sel   equ  (DemoStack0 - DLDTSeg) +TIL
    ;工作任务的2级堆栈段描述符(DPL=2)及其选择子(RPL=2)
    DemoStack2   DESCRIPTOR  LenStack2-1,Stack2Seg,0,ATDW+D32+DPL2,0
    Stack2_Sel   equ  (DemoStack2 - DLDTSeg) +TIL +RPL2
    ;工作任务的代码段描述符(32位段，DPL=2)及其选择子(RPL=2)
    DemoCode     DESCRIPTOR  LenDCode-1,DCodeSeg,0,ATCE+D32+DPL2,0  ;//@5
    DCode_Sel    equ  (DemoCode - DLDTSeg) +TIL +RPL2               ;//@6
    ;工作任务的数据段描述符(32位段，DPL=3)及其选择子(RPL=0)
    DemoData     DESCRIPTOR  LenDData-1,DDataSeg,0,ATDW+D32+DPL3,0
    DData_Sel    equ  (DemoData - DLDTSeg) +TIL
    ;把LDT别名作为普通数据段的描述符(DPL=2)及其选择子(RPL=0)
    ALDT         DESCRIPTOR  LenDLDT-1,DLDTSeg,0,ATDW+DPL2,0
    ALDT_Sel     equ  (ALDT - DLDTSeg) +TIL
    ;把TempTSS别名作为普通数据段的描述符(DPL=2)及其选择子(RPL=0)
    ATTSS        DESCRIPTOR  LenTTSS-1,TTSSeg,0,ATDW+DPL2,0
    ATTSS_Sel    equ  (ATTSS - DLDTSeg) +TIL
    NumDescL     equ  ($ - DLDTSeg)/8   ;LDT中待初始化描述符个数
    ;指向子程序的调用门(DPL=3)及其描述符(RPL=2)
    PSubGate     GATE  SubBegin,SCode_Sel3,0,ATCGAT32+DPL3,0        ;//@7
    PSGate_Sel   equ   (PSubGate - DLDTSeg) +TIL +RPL2              ;//@8
    ;指向临时任务TempTSS的任务门(DPL=3)及其选择子(RPL=0)
    PTTGate      GATE  0,TTSS_Sel,0,ATTASKGAT+DPL3,0                ;//@9
    PTTGate_Sel  equ   (PTTGate - DLDTSeg) +TIL
    LenDLDT      equ   $ - DLDTSeg         ;LDT的长度
    ;-------------------------------
        align  16                   ;16字节对齐
    ;工作任务的0级堆栈段(32位段)
    Stack0Seg:
	LenStack0   equ  512
        times   LenStack0   DB   0
    ;工作任务的2级堆栈段(32位段)
    Stack2Seg:
	LenStack2   equ  512
        times   LenStack2   DB   0
    ;-------------------------------
    ;工作任务的数据段(32位段)
    DDataSeg:
    Message    equ  $ - DDataSeg
        DB     'EIP= ',0
    LenDData   equ  $ - DDataSeg
    ;-------------------------------
    ;工作任务的子程序段(32位段)
        align  16                   ;16字节对齐
        bits   32                   ;32位段模式
    SCodeSeg:
    SubBegin  equ  $  - SCodeSeg
    SubR:
    ;在显示指定的字符串后，以十六进制数形式显示32位二进制值
    ;通过堆栈传递参数（第1个是要显示的值，第2个是提示信息首地址）
        PUSH  EBP
        MOV   EBP, ESP
        PUSHAD                      ;保护现场
        ;从堆栈(0级)中取提示信息串的起始地址偏移
        MOV   ESI, [EBP+12]         ;从堆栈取得第2个参数
        MOV   AH, 17H               ;蓝底白字
        JMP   SHORT  .L2
    .L1:STOSW                       ;显示提示信息
    .L2:LODSB
        OR    AL, AL                ;提示信息以0结尾
        JNZ   .L1
        ;从堆栈(0级)中取显示值
        MOV   EDX, [EBP+16]         ;从堆栈取得第1个参数
        MOV   ECX, 8                ;32个2进制位 = 8个16进制位
    .L3:ROL   EDX, 4
        MOV   AL, DL
        CALL  HTOASC                ;转成ASCII码
        STOSW                       ;填写到视频存储区（显示）
        LOOP  .L3
        POPAD                       ;恢复现场
        POP   EBP
        RETF  8                     ;段间返回，并废除堆栈中的参数  //@A
		;
    HTOASC:                         ;转成对应ASCII码
        AND   AL, 0FH
        ADD   AL, '0'
        CMP   AL, '9'
        JBE   SHORT .L1
        ADD   AL,7
    .L1:RET                         ;段内返回
    LenSCode   equ   $ - SCodeSeg
    ;-------------------------------
    ;工作任务的代码段（32位段，2级）
    DCodeSeg:
        align  16                   ;16字节对齐
        bits   32                   ;32位段模式
        or    eax, eax              ;仅仅占位，装装样子，可以省略 
    DBegin   equ  $ - DCodeSeg
        ;把要复制的参数个数置入调用门
        MOV   BYTE [FS:PSubGate.DCOUNT - DLDTSeg], 2                    ;//@B
        ;向堆栈(2级)中压入参数
        PUSH  DWORD  [GS:TempTask.TREIP - TempTask] ;数据(临时任务挂起点)//@C
        PUSH  DWORD  Message                        ;提示信息首地址      //@D
    ToSub:
        CALL  PSGate_Sel:0          ;通过调用门调用工作子程序            //@E
        ;把指向规范数据段描述符的选择子填入临时任务TSS
        PUSH  GS
        POP   DS
        MOV   AX, Normal_Sel
        MOV	  [TempTask.TRDS - TTSSeg], AX
        MOV	  [TempTask.TRES - TTSSeg], AX
        MOV	  [TempTask.TRFS - TTSSeg], AX
        MOV   [TempTask.TRGS - TTSSeg], AX
        MOV   [TempTask.TRSS - TTSSeg], AX
     ToTempT:
        JMP   PTTGate_Sel:0         ;通过任务门切换到临时任务            //@F
    LenDCode  equ  $ - DCodeSeg 
    ;-------------------------------
    ;临时任务的任务状态段TSS
        align  16                   ;16字节对齐
    TTSSeg:
    TempTask  TASKSS                ;为节省篇幅，采用宏
              DB   0FFH
    LenTTSS   equ  $ - TTSSeg
    ;-------------------------------
    ;临时任务的临时代码段(16位段，0级)
        align  16                   ;16字节对齐
        bits   16                   ;16位段模式
    TCSeg:
    PM_Entry1   equ  $ - TCSeg
        MOV   AX, TTSS_Sel          ;临时任务TSS
        LTR   AX                    ;装载任务寄存器TR  //@G
        ;
        JMP   DTSS_Sel:0            ;直接切换到工作任务
        ;
    PM_Entry2:                      ;准备切换回实方式
        or    eax, eax              ;仅仅占位，装装样子，可以省略 
        CLTS                        ;清任务切换标志
        ;
        MOV   EAX, CR0              ;准备返回实方式
        AND   AX, 0FFFEH
        MOV   CR0, EAX
    ToReal:                         ;真正进入实方式
        JMP   0:Real
    LenTCode  equ  $ - TCSeg
    ;=========================================
        align 16
    ;实方式的数据
    VGDTR     PDESC  LenGDT-1,0     ;GDT伪描述符
    VarESP    DD     0              ;暂存实方式的堆栈指针
    VarSS     DW     0
    ;-------------------------------
    ;实方式的代码
        bits  16                    ;16位段模式
    Begin:
        CLD
        MOV   AX, CS
        MOV   DS, AX
        MOV   [ToReal+3], AX        ;重定位
        MOV   [VarESP], ESP         ;保存实方式下堆栈指针
        MOV   [VarSS], SS
        MOV   SI, InitGDT
        MOV   CX, NumDescG
        CALL  InitDescBA            ;设置GDT中待初始化描述符的基地址
        MOV   SI, DLDTSeg
        MOV   CX, NumDescL
        CALL  InitDescBA            ;设置LDT中待初始化描述符的基地址
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
