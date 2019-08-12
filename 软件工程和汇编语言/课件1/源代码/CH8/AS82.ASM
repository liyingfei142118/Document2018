    ;示例程序as82.asm
    ;子程序名（入口标号）：set_time1
    ;功能：设置RTC时间值（采用BCD码表示）
    ;入口参数:CH=小时值；CL=分值；DH=秒值
    set_time1:
    UIP:
        MOV   AL, 10                ;寄存器A地址（0AH）
        OUT   70H, AL               ;准备读取寄存器A
        IN    AL, 71H               ;读取寄存器A
        TEST  AL, 80H               ;测试是否正在更新
        JNZ   UIP                   ;正在更新中，则继续测试
    Set_TV:
        MOV   AL, 0                 ;秒单元地址
        OUT   70H, AL               ;准备设置秒单元
        MOV   AL, DH
        OUT   71H, AL               ;设置秒值
        ;
        MOV   AL, 2                 ;分单元地址
        OUT   70H, AL               ;准备设置分单元
        MOV   AL, CL
        OUT   71H, AL               ;设置分值
        ;
        MOV   AL, 4                 ;时单元地址
        OUT   70H, AL               ;准备设置时单元
        MOV   AL, CH
        OUT   71H, AL               ;设置时值
        RET
