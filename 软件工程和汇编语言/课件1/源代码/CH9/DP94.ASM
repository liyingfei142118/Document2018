    ;演示程序dp94.asm
    ;演示分页存储管理机制的使用（示例四）
    ;                               ;常量声明
    PL         EQU      1           ;存在属性位P值
    RWR        EQU      0           ;R/W属性位值，读/执行
    RWW        EQU      2           ;R/W属性值，读/写/执行
    USS        EQU      0           ;U/S属性值，系统级
    USU        EQU      4           ;U/S属性值，用户级
    ;
    PDT_AD     EQU      200000H     ;页目录表所在物理页的地址
    PT0_AD     EQU      202000H     ;页表0所在物理页的地址
    PT1_AD     EQU      201000H     ;页表1所在物理页的地址
    ;
    PhVB_AD    EQU      0B8000H     ;视频存储区的物理地址
    LoVB_AD    EQU      0F0000H     ;视频存储区的逻辑地址（线性地址）
    MPVB_AD    EQU      301000H     ;线性地址0B8000H所映射的物理地址
    PhSC_AD    EQU      303000H     ;高端演示代码所在段的起始物理地址
    LoSC_AD    EQU      402000H     ;高端演示代码所在段的起始线性地址
    ;
    %include  "DMC.H"               ;文件DMC.H含有宏的声明和符号常量等
    ;-----------------------------------------------------------
        section  text               ;段text
        bits     16                 ;16位段模式
    Head:                           ;工作程序特征信息
        HEADER   end_of_text, Begin, 2000H
    ;-----------------------------------------------------------
    GDTSeg:                                 ;全局描述符表GDT
    Dummy      DESCRIPTOR  0,0,0,0,0
    Normal     DESCRIPTOR  0FFFFH,0,0,ATDW,0
    Normal_Sel equ   Normal - GDTSeg
    ;页目录表所在段描述符（保护方式下初始化时使用）
    PDTable    DESCRIPTOR  0FFFH,{PDT_AD & 0FFFFH},{PDT_AD>>16},ATDW,0
    PDT_Sel    equ   PDTable - GDTSeg
    ;页表0所在段描述符（保护方式下初始化时使用）
    PTable0    DESCRIPTOR  0FFFH,{PT0_AD & 0FFFFH},{PT0_AD>>16},ATDW,0
    PT0_Sel    equ   PTable0 - GDTSeg
    ;页表1所在段描述符（保护方式下初始化时使用）
    PTable1    DESCRIPTOR  0FFFH,{PT1_AD & 0FFFFH},{PT1_AD>>16},ATDW,0
    PT1_Sel    equ   PTable1 - GDTSeg
    ;逻辑上的视频存储区所在段描述符
    LVideoMem  DESCRIPTOR  3999,{LoVB_AD & 0FFFFH},{LoVB_AD>>16},ATDW,0
    LVMem_Sel  equ   LVideoMem - GDTSeg
    ;逻辑上的高端演示代码段描述符（32位代码段）
    LCode      DESCRIPTOR  LenHAC-1,{LoSC_AD & 0FFFFH},{LoSC_AD>>16},ATCE32,0
	LCode_Sel  equ   LCode - GDTSeg
    ;存放高端演示代码的数据段描述符（上传时的目标段）
    HACode     DESCRIPTOR  LenHAC-1,{PhSC_AD & 0FFFFH},{PhSC_AD>>16},ATDW,0
    HACode_Sel equ   HACode - GDTSeg
    InitGDT:                         ;以下是需要另行初始化的描述符
    ;临时代码段描述符（16位段）
    TempCode   DESCRIPTOR  0FFFFH,0,0,ATCER,0
    TCode_Sel  equ   TempCode - GDTSeg
    ;低端演示代码段描述符（32位段）
    DemoCode   DESCRIPTOR  0FFFFH,0,0,ATCE32,0
    DCode_Sel  equ  DemoCode - GDTSeg
    ;工作任务数据段描述符
    DemoData   DESCRIPTOR  0FFFFH,0,0,ATDW,0
    DData_Sel  equ   DemoData - GDTSeg
    ;工作任务堆栈段描述符（32位段）
    DemoStack  DESCRIPTOR  0FFFFH,0,0,ATDW32,0
    DStack_Sel equ   DemoStack - GDTSeg
    NumDescG   equ  ($ - InitGDT)/8     ;需要初始化的描述符个数
    LenGDT     equ   $ - GDTSeg         ;GDT表的长度
    ;-----------------------------------------------------------
        align  16                   ;16字节对齐
        bits  32                    ;32位段模式
    ;高端演示代码段（32位段）
    ;功能：在屏幕上显示提示信息
    ;为了充分演示，这部分代码会被上传到高端的物理地址（1M以上）区域
    HABegin:
    EchoEDX:                        ;十六进制数形式显示EDX之内容
        MOV   ECX, 8                ;采用直接写屏方式显示
    .L1:ROL   EDX, 4
        MOV   AL, DL
        AND   AL, 0FH
        ADD   AL, '0'
        CMP   AL, '9'
        JBE   .L2
        ADD   AL, 7
    .L2:STOSW
        LOOP  .L1
        RET
    ;-------------------------------
    HAStart:
    Rel_HAS   equ   $ - HABegin
        MOV   AX, PT0_Sel           ;//@1
        MOV   FS, AX                ;用于页表0所在段
        MOV   EBX, (LoVB_AD>>12)*4
        MOV   EDX, [FS:EBX]         ;取得对应逻辑视频存储区的PTE//@2
        ;
        MOV   AX, LVMem_Sel         ;//@3
        MOV   ES, AX                ;用于视频存储区
        MOV   EDI, 5*80*2           ;显示信息的屏幕位置(第5行)
        MOV   ESI, Message          ;指向待显示字符串
        MOV   AH, 17H               ;蓝底白字
    .L1:LODSB
        OR    AL, AL                ;字符串以0结尾
        JZ    .L2
        STOSW                       ;填写到视频存储区（显示）
        JMP   SHORT  .L1
    .L2:
        ADD   EDI, 4                ;间隔2个字符
        MOV   AH, 47H               ;红底白字
        CALL  EchoEDX               ;显示原先的PTE值
        ;
        MOV   EDX, [FS:EBX]         ;取得对应逻辑视频存储区的PTE//@4
        ADD   EDI, 4                ;间隔2个字符
        MOV   AH, 57H               ;粉底白字
        CALL  EchoEDX               ;显示现在的PTE值
        ;
        JMP   DCode_Sel:Demo3       ;跳转回低端演示代码段
    LenHAC   equ   $ - HABegin      ;高端演示代码段的长度
    ;-----------------------------------------------------------
        align  16                   ;16字节对齐
    ;工作任务数据段
    Message     DB		'PTE for LoVB:',0
    DemoDataLEN  equ  $
    ;------------------------------
        align  16                   ;16字节对齐
    ;工作任务堆栈段
    StackSeg:
	LenStack    equ  512
        times   LenStack    DB   0
    ;-----------------------------------------------------------
    ;低端演示代码段（32位段）
        bits   32                   ;采用32位段模式
    DemoBegin:                       
        MOV   AX, PDT_Sel           ;准备初始化页目录表
        MOV   ES, AX                ;用于页目录表所在段
        XOR   EDI, EDI
        MOV   ECX, 1024
        XOR   EAX, EAX
        REP   STOSD                 ;先把全部表项置成无效（P=0）
        ;                           ;再置PDT表项0和表项1
        MOV   DWORD [ES:0], PT0_AD | (USU+RWW+PL)
        MOV   DWORD [ES:4], PT1_AD | (USU+RWW+PL)
        ;
        MOV   AX, PT0_Sel           ;准备初始化页表0
        MOV   ES, AX                ;用于页表0所在段
        XOR   EDI, EDI
        MOV   ECX, 1024
        XOR   EAX, EAX              ;线性地址00000000H
        OR    EAX, USU+RWW+PL       ;映射相同地址的物理页
    .L1:STOSD
        ADD   EAX, 1000H
        LOOP  .L1                   ;首先全部置成直接映射
        MOV   EDI, (PhVB_AD>>12)*4  ;然后，特别设置2个表项
        MOV   DWORD [ES:EDI], MPVB_AD+USS+RWW+PL
        MOV   EDI, (LoVB_AD>>12)*4
        MOV   DWORD [ES:EDI], PhVB_AD+USU+RWR+PL   ;//@5
        ;
        MOV   AX, PT1_Sel           ;准备初始化页表1
        MOV   ES, AX                ;用于页表1所在段
        XOR   EDI, EDI
        MOV   ECX, 1024
        MOV   EAX, 400000H          ;线性地址00400000H
    .L2:STOSD
        ADD   EAX, 1000H
        LOOP  .L2                   ;首先全部置成无效
        ;                           ;然后，特别设置1个表项
        MOV   EDI, ((LoSC_AD >> 12) & 3FFH)*4
        MOV   DWORD [ES:EDI], PhSC_AD+USU+RWR+PL
        ;
        MOV   EAX, PDT_AD           ;页目录表物理地址
        MOV   CR3, EAX              ;设置页目录寄存器
        ;
        MOV   EAX, CR0              ;准备启用分页机制
        OR    EAX, 80000000H
        MOV   CR0, EAX              ;启用分页机制
        JMP   SHORT  PageE          ;刷新指令预取队列，真正启用分页
        ;---------------------------
    PageE:                          ;已启用分页
        MOV   AX, DStack_Sel        ;建立演示任务的堆栈
        MOV   SS, AX
        MOV   ESP, StackSeg + LenStack
        ;
        MOV   AX, DData_Sel         ;演示任务数据段
        MOV   DS, AX
        ;                           ;跳转到高端演示代码
        JMP   LCode_Sel:Rel_HAS     ;//@6
        ;---------------------------
    Demo3:
        MOV   EAX, CR0              ;准备关闭分页机制
        AND   EAX, 7FFFFFFFH        ;//@7
        MOV   CR0, EAX              ;关闭分页机制
        JMP   SHORT  PageD          ;真正关闭分页机制
        ;---------------------------
    PageD:                          ;已关闭分页
        MOV   AX, Normal_Sel        ;准备规范段选择子
        JMP   TCode_Sel:TC_Entry2   ;切换到临时代码段（16位段）
    DemoCodeLEN   equ   $           ;低端演示代码段的长度
    ;-----------------------------------------------------------
    ;临时过渡代码段
        align  16                   ;16字节对齐
        bits   16                   ;采用16位代码段模式
    TC_Entry:                       ;为启用分页机制做准备
        ;把高端演示代码部分上传到指定的高端内存区域
        MOV   AX, TCode_Sel         ;临时代码段具有可读属性
        MOV   DS, AX                ;用于源数据段
        MOV   AX, HACode_Sel        ;指向高端内存区域（1M以上）
        MOV   ES, AX                ;用于目标数据段//@8
        MOV   SI, HABegin           ;被复制代码起点在源段内的偏移
        MOV   DI, 0                 ;假设复制到目标段内起点的偏移是0
        MOV   CX, LenHAC            ;字节数
        REP   MOVSB                 ;上传
        ;
        JMP   DCode_Sel:DemoBegin   ;转到低端演示代码
        ;---------------------------
    TC_Entry2:                      ;准备切换到实方式
        MOV   DS, AX
        MOV   ES, AX                ;加载规范描述符选择子
        MOV   FS, AX
        MOV   EAX, CR0
        AND   EAX, 0FFFFFFFEH
        MOV   CR0, EAX              ;切换回实方式
    ToReal:                         ;清指令预取队列，真正进入实方式
        JMP   0:Real                ;将到达实方式的Real处（需重定位）
    ;===========================================================
        align  16                   ;16字节对齐
        bits   16                   ;采用16位代码段模式
    VGDTR    PDESC   LenGDT-1, 0    ;伪描述符
    VarESP     DD    0              ;用于保存ESP的变量
    VarSS      DW    0              ;用于保存SS的变量
    Begin:
        CLD
        MOV   AX, CS
        MOV   DS, AX
        MOV   [ToReal+3], AX        ;重定位
        MOV   [VarSS], SS           ;保存实方式下的堆栈
        MOV   [VarESP], ESP
        ;
        MOV   SI, InitGDT           ;指向需要初始化的首个描述符
        MOV   CX, NumDescG          ;需要初始化的描述符个数
        CALL  InitDescBA            ;初始化GDT表中的部分描述符
        MOV   SI, VGDTR             ;指向伪描述符
        MOV   BX, GDTSeg            ;指向GDT表
        CALL  InitPeDesc            ;初始化伪描述符
        ;
        LGDT  [VGDTR]               ;装载GDTR
        CLI
        CALL  EnableA20             ;打开地址线A20
        MOV   EAX, CR0              ;准备切换到保护方式
        OR    EAX, 1
        MOV   CR0, EAX
		JMP   TCode_Sel:TC_Entry    ;清指令预取队列，真正进入保护方式
        ;---------------------------
    Real:                           ;现在又回到实方式
        MOV   AX, CS
        MOV   DS, AX
        LSS   ESP, [VarESP]         ;恢复堆栈
        CALL  DisableA20            ;关闭地址线A20
        STI                         ;开中断
        RETF                        ;返回到加载器
    ;------------------------------
        %include   "proc.asm"       ;包含相关子程序
    end_of_text:                    ;源代码到此为止
