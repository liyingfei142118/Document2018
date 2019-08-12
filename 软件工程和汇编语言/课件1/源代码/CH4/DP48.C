    //演示程序dp48.c
    #include  <stdio.h>
    void  echo_bit64(unsigned char *bit64);
    unsigned char  bitstr1[8] = { 0,0,0,0,0,0,0,0 };
    unsigned char  bitstr2[8] = { 0,0,0,0,0,0,0,0 };
    int  main( )
    {
        _asm  {   //嵌入汇编代码一
            LEA   EDX, bitstr1          ;取得位串1的基地址
            ;                           ;设置位串中的第17位
            MOV   EAX, 1
            MOV   ECX, 17
            SHL   EAX, CL
            OR    DWORD PTR [EDX], EAX
            ;                           ;设置位串中的第43位
            MOV   EAX,1
            MOV   ECX,43-32
            SHL   EAX,CL
            OR    DWORD PTR [EDX+4], EAX
        }
        echo_bit64( bitstr1 );          //显示为0000080000020000
        ;
        _asm  {   //嵌入汇编代码二
            LEA   EDX, bitstr2          ;取得位串2的基地址
            ;                           ;设置位串中的第17位
            MOV   ECX, 17
            BTS   DWORD PTR [EDX], ECX  ;位操作指令
            ;                           ;设置位串中的第43位
            MOV   ECX, 43 - 32
            BTS   DWORD PTR [EDX+4], ECX    ;位操作指令
        }
        echo_bit64( bitstr2 );          //显示为0000080000020000
        return 0;
    }
    //函数bit64功能是，以十六进制数的形式显示64位的位串
    void  echo_bit64(unsigned char *pc)
    {
        printf("%08x", *((unsigned int*)(pc+4)));
        printf("%08x\n", *((unsigned int*)pc));	
        return;
    }
