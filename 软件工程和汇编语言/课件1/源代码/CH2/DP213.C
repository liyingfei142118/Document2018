    //演示程序dp213
    #include  <stdio.h>
    int  arri[] = {23, 56, 78, 82, 77, 35, 22, 18, 44, 67};
    int  main( )
    {
        int  sum;                   //用于存放累加和
        //嵌入汇编
        _asm  {
            MOV   EAX, 0            //用于存放累加和
            MOV   ESI, 0            //作为数组的下标（索引）
            MOV   ECX, 10           //作为计数器
            LEA   EBX, arri         //得到数组首元素的有效地址
        NEXT:
            ADD   EAX, [EBX+ESI*4]  //累加某个元素值（由索引确定）
            INC   ESI               //调整下标
            DEC   ECX               //计数器减1（该指令会影响状态标志）
            JNZ   NEXT              //当ECX不为0，则从NEXT处继续执行
            ;
            MOV   sum, EAX          //保存累加和
        }
        printf("sum=%d\n", sum);    //显示为sum=502
        return  0;
    }
