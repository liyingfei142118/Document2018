    ;文件名：DMC.H
    ;内  容：宏和部分符号常量的声明
    ;-------------------------------
    ;表示工作程序特征信息的宏
    %macro   HEADER   3
    .SIGNA   DB   "YANG"            ;签名信息
    .VERSI   DW   1                 ;格式版本
    .LENGT   DW   %1                ;工作程序长度
    .START   DW   %2                ;工作程序入口点的偏移
    .ZONES   DW   %3                ;工作程序期望的内存区域起始段值
    .RESER   DD   0                 ;保留
    %endmacro
    ;-------------------------------
    ;表示存储段描述符/系统段描述符结构的宏
    %macro   DESCRIPTOR   5
    .LIMIT   DW   %1                ;段界限(0--15)
    .BASEL   DW   %2                ;段基地址(0--15)
    .BASEM   DB   %3                ;段基地址(16-23)
    .ATTRI   DW   %4                ;段属性
    .BASEH   DB   %5                ;段基地址(24-31)
    %endmacro
    ;-------------------------------
    ;表示伪描述符结构的宏
    %macro   PDESC   2
    .LIMIT   DW   %1                ;16界限
    .BASE    DD   %2                ;基地址
    %endmacro
    ;-------------------------------
    ;存储段描述符类型值
    ATDR     EQU   0090H            ;存在的只读数据段
    ATDW     EQU   0092H            ;存在的可读写数据段
    ATDWA    EQU   0093H            ;存在的已访问可读写数据段
    ATDW32   EQU   4092H            ;存在的可读写32位数据段
    ATCE     EQU   0098H            ;存在的只执行16位代码段
    ATCER    EQU   009AH            ;存在的可执行可读16位代码段
    ATCE32   EQU   4098H            ;存在的只执行32位代码段
    ATCCO    EQU   009CH            ;存在的只执行一致代码段
    ATCCOR   EQU   009EH            ;存在的可执行可读一致代码段
    ;-------------------------------
    ;系统段描述符和门描述符类型值
    ATLDT       EQU   82H           ;局部描述符表段类型值
    ATTASKGAT   EQU   85H           ;任务门类型值
    ATTSS32     EQU   89H           ;386TSS类型值
    ATCGAT32    EQU   8CH           ;386调用门类型值
    ATIGAT32    EQU   8EH           ;386中断门类型值
    ATTGAT32    EQU   8FH           ;386陷阱门类型值
    ;-------------------------------
    ;描述符特权级DPL和请求特权级RPL值
    DPL1     EQU   20H              ;DPL=1
    DPL2     EQU   40H              ;DPL=2
    DPL3     EQU   60H              ;DPL=3
    RPL1     EQU   01H              ;RPL=1
    RPL2     EQU   02H              ;RPL=2
    RPL3     EQU   03H              ;RPL=3
    ;-------------------------------
    ;其他常量值
    D32   EQU   4000H               ;32位代码段标志
    TIL   EQU   04H                 ;TI=1（描述符表标志）
    ;-------------------------------
    ;表示门描述符结构的宏
    %macro     GATE   5
    .OFFSETL   DW   %1              ;32位偏移的低16位
    .SELECTOR  DW   %2              ;段选择子
    .DCOUNT    DB   %3              ;双字计数字段
    .GTYPE     DB   %4              ;类型（属性）
    .OFFSETH   DW   %5              ;32位偏移的高16位
    %endmacro
    ;-------------------------------
    ;表示任务状态段TSS结构的宏
    %macro    TASKSS  0             ;不带参数
    .TRLINK   DW      0, 0          ;链接字
    .TRESP0   DD      0             ;0级堆栈指针
    .TRSS0    DW      0, 0
    .TRESP1   DD      0             ;1级堆栈指针
    .TRSS1    DW      0, 0
    .TRESP2   DD      0             ;2级堆栈指针
    .TRSS2    DW      0, 0
    .TRCR3    DD      0             ;CR3
    .TREIP    DD      0             ;EIP
    .TREFLAG  DD      0             ;EFLAGS
    .TREAX    DD      0             ;EAX
    .TRECX    DD      0             ;ECX
    .TREDX    DD      0             ;EDX
    .TREBX    DD      0             ;EBX
    .TRESP    DD      0             ;ESP
    .TREBP    DD      0             ;EBP
    .TRESI    DD      0             ;ESI
    .TREDI    DD      0             ;EDI
    .TRES     DW      0, 0          ;ES
    .TRCS     DW      0, 0          ;CS
    .TRSS     DW      0, 0          ;SS
    .TRDS     DW      0, 0          ;DS
    .TRFS     DW      0, 0          ;FS
    .TRGS     DW      0, 0          ;GS
    .TRLDT    DW      0, 0          ;LDT
    .TRFLAG   DW      0             ;TSS的特别属性字
    .TRIOMAP  DW      $+2 - .TRLINK ;指向I/O许可位图区的指针
    %endmacro
    ;===============================
