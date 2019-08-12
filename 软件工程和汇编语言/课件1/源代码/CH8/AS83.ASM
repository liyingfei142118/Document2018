    ;示例程序as83.asm
    ;
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
    ;-------------------------------
    ;子程序名（入口标号）：set_time2
    ;功能：设置RTC时间值（采用BCD码表示）
    ;入口参数:CH=小时值；CL=分值；DH=秒值
    ;出口参数:CF=0，设置成功；CF=1，设置失败
    set_time2:
        PUSH  CX
        MOV   CX, 25000             ;安排查询次数
    UIP:
        MOV   AL, 10
        OUT   70H, AL
        IN    AL, 71H               ;读取寄存器A
        TEST  AL, 80H               ;测试是否正在更新
        LOOPNZ  UIP                 ;正在更新且查询次数未满，则继续查询
        POP   CX
        STC                         ;准备出口参数（先假设失败）
        JNZ   .Over                 ;确实失败，则转
        CALL  Set_TV                ;具体设置时间值
        CLC                         ;准备出口参数
    .Over:
        RET
