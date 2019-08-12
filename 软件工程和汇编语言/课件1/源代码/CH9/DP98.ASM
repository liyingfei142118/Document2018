    ;演示程序dp98.asm
    ;演示中断的处理（示例八）
    %include  "DMC.H"               ;文件DMC.H含有宏的声明和符号常量等
    ;                               ;相关符号常量声明
    EOICOM   equ    20H             ;外部中断处理结束命令
    ICREGP   equ    20H             ;中断控制寄存器端口
    IMREGP   equ    21H             ;中断屏蔽寄存器端口
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
    ;任务的临时代码段描述符及其选择子
    TempCode     DESCRIPTOR  0FFFFH,TCodeSeg,0,ATCE,0
    TCode_Sel    equ   TempCode - GDTSeg
    ;任务的演示代码段描述符（32位段）及其选择子
    DemoCode     DESCRIPTOR  LenDCode-1,DCodeSeg,0,ATCE+D32,0
    DCode_Sel    equ   DemoCode - GDTSeg
    ;任务的数据段描述符
    DemoData     DESCRIPTOR	 LenDData-1,DDataSeg,0,ATDW,0
    DData_Sel    equ   DemoData  -  GDTSeg
    ;任务的堆栈段描述符（32位段）及其选择子
    DemoStack    DESCRIPTOR  LenStack-1,StackSeg,0,ATDW+D32,0
    Stack_Sel    equ   DemoStack - GDTSeg
    ;第FEH号中断处理程序（显示程序）代码段描述符
    EchoCode     DESCRIPTOR	 LenECode-1,ECodeSeg,0,ATCE+D32,0
    ECode_Sel	 equ   EchoCode  -  GDTSeg
    ;第FEH号中断处理程序（显示程序）数据段描述符
    EchoData     DESCRIPTOR	 LenEData-1,EDataSeg,0,ATDW,0
    EData_Sel    equ   EchoData - GDTSeg
    ;第08H号中断处理程序代码段描述符
    TICode       DESCRIPTOR  LenTICode-1,TICodeSeg,0,ATCE+D32,0
    TICode_Sel   equ   TICode  -  GDTSeg
    ;第08H号中断处理程序数据段描述符
    TIData       DESCRIPTOR	 LenTIData-1,TIDataSeg,0,ATDW,0
    TIData_Sel   equ   TIData  -  GDTSeg
    ;处理其他中断或异常的特殊处理程序代码段描述符
    Other        DESCRIPTOR  LenOCode-1,OCodeSeg,0,ATCE+D32,0
    Other_Sel    equ   Other  -  GDTSeg
    ;GDT中的需要进行基地址初始化的描述符个数
    NumDescG     equ   ($ - InitGDT) / 8    ;GDT中待初始化的描述符个数 
    ;视频存储段的描述符及其选择子
    VideoMem     DESCRIPTOR  0FFFFH,8000H,0BH,ATDW,0
    VMem_Sel     equ   VideoMem - GDTSeg
    LenGDTSeg    equ   $ - GDTSeg
    ;-----------------------------------------------------------
        align   16                  ;16字节地址对齐
    IDTSeg:                         ;中断描述符表IDT
    ;第00--07H的8个陷阱门，指向其他中断/异常处理程序
        times   8   dw   OtherBegin, Other_Sel, ATTGAT32<<8, 0
    ;第08H号中断门，指向定时中断处理程序
    INT08:
        dw   TIBegin, TICode_Sel, ATIGAT32<<8, 0
    ;第09--FDH的245个陷阱门，指向其他中断/异常处理程序
        times   254-9  dw  OtherBegin, Other_Sel, ATTGAT32<<8, 0
    ;第FEH号陷阱门，指向作为软中断处理程序的显示程序
    INTFE   GATE   EchoBegin, ECode_Sel, 0, ATTGAT32, 0
    ;第FFH号陷阱门，指向其他中断/异常处理程序
    INTFF   GATE   OtherBegin, Other_Sel, 0, ATTGAT32, 0
    LenIDTSeg      equ $ - IDTSeg
    ;-------------------------------
    ;特殊中断或异常处理程序的代码段
        align 16                    ;16字节地址对齐
        bits  32                    ;32位代码段
    OCodeSeg:
    OtherBegin   equ   $ - OCodeSeg ;处理程序入口点
        MOV   AX, VMem_Sel
        MOV   ES, AX
        MOV   AH, 47H               ;红底白字
        MOV   AL, '!'
        MOV   [ES:0], AX            ;在屏幕左上角显示红底白色符号"!"
        JMP	  $                     ;无限循环
    LenOCode   equ  $ - OCodeSeg
    ;-------------------------------
    ;第08H号（定时）中断处理程序的数据段
        align 16                    ;16字节地址对齐
	TIDataSeg:
    COUNT   equ  $ - TIDataSeg
        DB	0                       ;计数器
    LenTIData    equ  $ - TIDataSeg
    ;-------------------------------
    ;第08H号（时钟）中断处理程序的代码段
        align 16                    ;16字节地址对齐
        bits  32                    ;32位代码段
    TICodeSeg:
    TIBegin   equ  $ - TICodeSeg    ;中断处理程序入口点
        PUSH  EAX                   ;保护现场
        PUSH  DS
        PUSH  FS
        PUSH  GS
        MOV   AX, TIData_Sel
        MOV   DS, AX                ;置中断处理程序数据段
        MOV   AX, EData_Sel
        MOV   FS, AX                ;置显示处理服务数据段
        MOV   AX, DData_Sel
        MOV   GS, AX                ;置任务数据段
        ;
        CMP   BYTE [COUNT], 0       ;判断计数器值
        JNZ   TI2                   ;计数非0表示未到一秒
        MOV   BYTE [COUNT], 18      ;每秒约18次
        INT   0FEH                  ;调用FEH号显示服务程序
        CMP   BYTE [FS:MESS], '0'   ;已经显示到符号'0'？
        JNZ   TI1
        MOV   BYTE [GS:FLAG], 1     ;当显示符号'0'时，置结束标记
    TI1:DEC   BYTE [FS:MESS]        ;调整显示信息（倒计时）
    TI2:DEC   BYTE [COUNT]          ;调整计数
        POP   GS
        POP   FS                    ;恢复现场
        POP   DS
        MOV   AL, EOICOM
        OUT   ICREGP, AL            ;通知中断控制器中断处理结束
        POP   EAX
        IRETD                       ;中断返回
    LenTICode   equ  $ - TICodeSeg
    ;-------------------------------
    ;第FEH号中断处理程序（显示程序）的数据段
        align 16                    ;16字节地址对齐
    EDataSeg:
    MESS   equ  $ - EDataSeg
        DB   '9', 47H               ;倒计数开始符号及显示颜色
    LenEData   equ  $ - EDataSeg
    ;-------------------------------
    ;第FEH号中断处理程序（显示程序）的代码段
        align 16                    ;16字节地址对齐
        bits  32                    ;32位代码段
    ECodeSeg:
    EchoBegin   equ  $ - ECodeSeg   ;处理程序入口处
        PUSH  AX
        PUSH  DS
        PUSH  ES
        MOV   AX,EData_Sel
        MOV   DS,AX                 ;置显示服务程序数据段
        MOV   AX,VMem_Sel
        MOV   ES,AX                 ;置视频存储区段
        MOV   AX, [MESS]            ;取显示字符和颜色
        MOV   [ES:40*2], AX         ;显示符号
        POP   ES
        POP   DS                    ;恢复现场
        POP   AX
        IRETD                       ;中断返回
    LenECode   equ  $ - ECodeSeg
    ;-------------------------------
    ;任务的堆栈段
        align 16                    ;16字节地址对齐
    StackSeg:
    LenStack   equ   1024
        times  LenStack   db  0
    ;-------------------------------
    ;任务的数据段
    DDataSeg:
    FLAG   equ   $  - DDataSeg
        DB   0                      ;工作标志
    LenDData   equ  $ - DDataSeg
    ;-------------------------------
    ;任务的代码段
        align 16                    ;16字节地址对齐
        bits  32                    ;32位代码段
    DCodeSeg:
    DemoBegin   equ  $ -DCodeSeg
        MOV   AX, Stack_Sel
        MOV   SS, AX                ;置堆栈
        MOV   ESP, LenStack
        MOV   AX, DData_Sel
        MOV   DS, AX                ;置数据段
        MOV   ES, AX
        MOV   FS, AX
        MOV   GS, AX
        ;
        MOV   AL, 11111110B         ;置中断屏蔽寄存器
        OUT   IMREGP, AL            ;仅开放定时中断
        STI                         ;开中断
    DemoConti:
        CMP   BYTE [FLAG], 0        ;判断工作标志
        JZ    DemoConti             ;为0继续，否则结束
        CLI                         ;关中断
    OVER:                           ;转回临时代码段，准备回实方式
        JMP   TCode_Sel:PM_Entry2
    LenDCode   equ  $ - DCodeSeg
    ;-------------------------------
    ;临时代码段
        align 16                    ;16字节地址对齐
        bits  16                    ;16位代码段
    TCodeSeg:
    PM_Entry1 equ  $ - TCodeSeg     ;转演示程序
        JMP   DCode_Sel:DemoBegin
    PM_Entry2 equ  $ - TCodeSeg     ;准备切换回实方式
        MOV   AX, Normal_Sel
        MOV   DS, AX
        MOV   ES, AX
        MOV   FS, AX
        MOV   GS, AX
        MOV   SS, AX
        MOV   EAX, CR0
        AND   EAX, 0FFFFFFFEH
        MOV   CR0, EAX              ;返回实方式
    ToReal:                         ;真正回到实方式
        JMP   0:Real
    ;===========================================================
    ;实方式下的数据段
        align 16                    ;16字节地址对齐
    RDataSEG:
    VGDTR     PDESC  LenGDTSeg-1,0  ;GDT伪描述符
    VIDTR     PDESC  LenIDTSeg-1,0  ;IDT伪描述符
    NORVIDTR  PDESC  3FFH,0         ;用于保存原IDTR值
    VarESP    DD     0              ;暂存堆栈指针
    VarSS     DW     0
    IMaskReg  DB     0              ;暂存中断屏蔽寄存器值
    ;-----------------------------------------------------------
    ;实方式下的代码段
        align 16                    ;16字节地址对齐
        bits  16                    ;16位代码段
    RCodeSEG:
    Begin:
        CLD
        MOV   AX, CS
        MOV   DS, AX
        MOV   [ToReal+3], AX        ;重定位
        MOV   [VarESP], ESP         ;保存实方式下堆栈指针
        MOV   [VarSS], SS
        ;
        MOV   SI, InitGDT
        MOV   CX, NumDescG
        CALL  InitDescBA            ;设置GDT中的待初始化描述符的基地址
        MOV   SI, VGDTR
        MOV   BX, GDTSeg
        CALL  InitPeDesc            ;初始化用于GDTR的伪描述符
        MOV   SI, VIDTR
        MOV   BX, IDTSeg
        CALL  InitPeDesc            ;初始化用于IDTR的伪描述符
        ;
        SIDT  [NORVIDTR]            ;保存IDTR值
        ;
        IN    AL, IMREGP
        MOV   [IMaskReg],AL         ;保存中断屏蔽字节
        ;
        LGDT  [VGDTR]               ;装载GDTR
        CLI
        LIDT  [VIDTR]               ;置IDTR
        MOV   EAX, CR0              ;准备切换到保护方式
        OR    EAX, 1
        MOV   CR0, EAX
        JMP   TCode_Sel:PM_Entry1   ;进入保护方式下的临时代码段
        ;---------------------------
    Real:                           ;又回到实方式
        MOV   AX, CS
        MOV   DS, AX
        LSS   ESP, [VarESP]         ;恢复实方式下的堆栈指针
        ;
        LIDT  [NORVIDTR]            ;恢复IDTR
        MOV   AL, [IMaskReg]        ;恢复中断屏蔽字节
        OUT   IMREGP, AL
        STI                         ;开中断
        RETF                        ;返回
    ;------------------------------
    %include   "PROC.ASM"           ;包含初始化阶段的相关子程序
    end_of_text:                    ;源代码到此为止
