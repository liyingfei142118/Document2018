    //演示程序dp26
    #include  <stdio.h>
    int  main( )
    {
        unsigned  char  vch1=188, vch2=172, vch3=233;  //3个字节变量
        unsigned  int   sum=0;                         //无符号整型变量
        ;//嵌入汇编
        _asm  {
            SUB   EDX, EDX          //使EDX为0，用DX存放累加和
            ADD   DL, vch1          //加第1个字节
            ADC   DH, 0             //高8位相加（保持形式一致）
            ADD   DL, vch2          //加第2个字节
            ADC   DH, 0             //高8位相加（考虑可能出现的进位）
            ADD   DL, vch3          //加第3个字节
            ADC   DH, 0             //高8位相加（考虑可能出现的进位）
            MOV   sum, EDX          //把结果送到变量sum
        }
        printf("sum=%u\n",sum);     //显示为sum=593
        return  0;
    }
