        ;示例代码片段dp611
        ;仅仅用于说明目标文件和机器码
        segment   text
        org   100H              ;设起始偏移100H
        MOV   AX, CS
        MOV   DS, AX
        ;
        bits  16                ;声明16位段模式
        MOV   AL, 1             ;B0 01
        MOV   AX, 1             ;B8 01 00
        MOV   EAX, 1            ;66 B8 01 00 00 00
        MOV   SI, wvar          ;BE 51 01
        MOV   EBX, wvar         ;66 BB 51 01 00 00
        MOV   AL, [SI]          ;8A 04
        MOV   AX, [SI]          ;8B 04
        MOV   EAX, [SI]         ;66 8B 04
        MOV   AL, [EBX]         ;67 8A 03
        MOV   AX, [EBX]         ;67 8B 03
        MOV   EAX, [EBX]        ;67 66 8B 03
	    ;
        bits  32                ;声明32位段模式
        MOV   AL, 1             ;B0 01
        MOV   AX, 1             ;66 B8 01 00  //@
        MOV   EAX, 1            ;B8 01 00 00 00
        MOV   SI, wvar          ;66 BE 51 01
        MOV   EBX, wvar         ;BB 51 01 00 00
        MOV   AL, [SI]          ;67 8A 04
        MOV   AX, [SI]          ;67 66 8B 04
        MOV   EAX, [SI]         ;67 8B 04
        MOV   AL, [EBX]         ;8A 03
        MOV   AX, [EBX]         ;66 8B 03
        MOV   EAX, [EBX]        ;8B 03
	    ;
        bits  16                ;声明16位段模式
        JMP   $                 ;E9 FD FF
    wvar      dw   1234H        ;34 12
              dw   5678H        ;78 56
