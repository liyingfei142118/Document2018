    //演示程序dp318.c
    #include  <stdio.h>
        char  flag1='0', flag2='0', flag3='0';
        int   ptonext;                  //存放转移地址
    int  main( )
    {
        _asm  {
            LEA    EAX, STEP2           //取得第二步的开始地址
            MOV    ptonext, EAX         //保存到存储单元
            ;
            LEA    EDX, STEP1           //取得第一步的开始地址
            JMP    EDX                  //转移到第一步（段内间接转移）
            ;
        STEP2:
            MOV    flag2, 'B'
            JMP    STEP3                //转移到第三步（段内直接转移）
            ;
        STEP1:
            MOV   flag1, 'A'
            JMP   ptonext               //转移到第二步（段内间接转移）
            ;
        STEP3:
            MOV   flag3, 'C'
        }
        printf("%c,%c,%c\n",flag1,flag2,flag3); //显示为A,B,C
        return  0;
    }
