        ;示例程序dp69.asm
        ;仅仅用于说明目标文件
        section  code
    begin:
        MOV   AX, begin         ;把标号begin代表的偏移送到AX，AX=0000H
        MOV   AX, $             ;把当前偏移送到AX，AX=0003H
    lab1:
        MOV   AX,1234H          ;把1234H送到AX，AX=1234H
    lab2:
        JMP   short lab2        ;跳转到自己（构成无限循环）
        ;
    wvar1     dw   lab1, lab2   ;定义2个字变量，初值是lab1和lab2代表的偏移
    wvar2     dw   wvar1        ;定义1个字变量，初值是wvar1代表的偏移
