    ;源文件：PROC.ASM
    ;保护方式编程初始化阶段的子程序
    ;-------------------------------
    InitDescBA:
    ;根据存储段的当前位置的段值和偏移，设置描述符的32位基地址
    ;DS:SI指向首个描述符，CX含有待初始化描述符的个数
    .Next:
        MOV   AX, CS                ;当前代码段值
        MOV   DX, 16
        MUL   DX                    ;DX:AX=当前代码段的基地址
        ADD   AX, [SI+2]            ;加上描述符中预置的起始地址
        ADC   DX, 0                 ;DX:AX=对应存储段的32位基地址
        MOV   [SI+2], AX            ;填写段基地址（位0-15）
        MOV   [SI+4], DL            ;填写段基地址（位16-23）
        MOV   [SI+7], DH            ;填写段基地址（位24-31）
        ADD   SI, 8                 ;下一个描述符
        LOOP  .Next
        RET
    ;-------------------------------
    InitPeDesc:
    ;设置用于GDTR或者IDTR的伪描述符
    ;DS:SI指向伪描述符变量，BX指向对应的描述符表首
        MOV   AX, CS
        MOV   DX, 16
        MUL   DX                    ;DX:AX含当前代码段基地址
        ADD   AX, BX
        ADC   DX, 0                 ;DX:AX指向GDT伪描述符
        MOV   [SI+2], AX            ;填写到伪描述符变量
        MOV   [SI+4], DX
        RET  
    ;-------------------------------
    EnableA20:
    ;打开地址线A20
       PUSH  AX
       IN    AL, 92H
       OR    AL, 2
       OUT   92H, AL
       POP   AX
       RET
    ;-------------------------------
    DisableA20:
    ;关闭地址线A20
        PUSH  AX
        IN    AL, 92H
        AND   AL, ~2
        OUT   92H, AL
        POP   AX
        RET
