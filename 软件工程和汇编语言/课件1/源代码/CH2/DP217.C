    //演示程序dp217
    #include  <stdio.h>
    int   buff[8];              //全局数组，存放从堆栈中取出的各寄存器之值
    int  main( )
    {
        _asm  {                 //嵌入汇编
            PUSH  EBP           //先保存EBP！！
            ;
            MOV   EAX, 0        //给各通用寄存器赋一个特定的值
            MOV   EBX, 1
            MOV   ECX, 2
            MOV   EDX, 3
            ;                   //决不能随意改变ESP！！
            MOV   EBP, 5
            MOV   ESI, 6
            MOV   EDI, 7
            ;
            PUSHAD              //把8个通用寄存器之值全部推到堆栈
            ;
            MOV   EBP, ESP      //使得EBP也指向堆栈顶
            LEA   EBX, buff     //把数组buff首元素的有效地址送到EBX
            MOV   ECX, 0        //设置计数器（下标）初值
        NEXT:
            MOV   EAX, [EBP+ECX*4]      //依次从堆栈中取
            MOV   [EBX+ECX*4], EAX      //依次保存到数组buff
            INC   ECX           //计数器加1
            CMP   ECX, 8        //是否满8
            JNZ   NEXT          //没有满8个，继续处理下一个
            ;
            POPAD               //恢复8个通用寄存器
            POP   EBP           //恢复开始保存的EBP
        }
        //依次显示数组buff各元素之值，从中观察PUAHAD指令压栈的效果
        int  i;
        for  (i=0; i<8; i++)
            printf("buff[%d]=%u\n", i, buff[i]);
        return  0;
    }
