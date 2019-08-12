        ;演示程序dp61.asm
        segment   text              ;命名段text
        org   100H                  ;段内偏移从100H开始计算
        ;
        MOV   AX, CS
        MOV   DS, AX                ;使数据段与代码段相同
        ;
        MOV   DX, hello             ;DX=信息hello的段内偏移
        MOV   AH, 9
        INT   21H                   ;显示hello开始的字符串（以$结尾）
        ;
        MOV   AH, 4CH
        INT   21H                   ;返回操作系统
        ;
    hello     db    "Hello,world", 0DH, 0AH, '$'  ;定义字符串信息
    ;===============================
