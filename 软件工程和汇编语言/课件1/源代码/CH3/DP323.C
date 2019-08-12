    //演示程序dp323.c
    #include  <stdio.h>
    int  main( )
    {
        char  string[100];              //用于存放字符串
        int  len;                       //用于存放字符串长度
        printf("Input string:");        //由用户输入一个字符串
        scanf("%s",string);
        //嵌入汇编代码
        _asm  {
            LEA   EDI, string           //使得EDI指向字符串
            XOR   ECX, ECX              //假设字符串"无限长"
            XOR   AL, AL                //使AL=0（字符串结束标记）
            DEC   EDI                   //为了简化循环，先减1
        LAB3:
            INC   EDI                   //指向待判断字符
            CMP   AL, [EDI]             //是否为结束标记
            LOOPNE   LAB3               //如果不是结束标记，继续循环
            ;
            NOT   ECX                   //据ECX，推得字符串长度
            MOV   len, ECX
        }
        printf("len=%d\n",len);         //显示输入字符串的长度
        return 0;
    }
