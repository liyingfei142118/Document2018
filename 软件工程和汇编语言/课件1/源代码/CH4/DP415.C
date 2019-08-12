    //演示程序dp415.c
    #include  <stdio.h>
    char buffer[] = { 3, -5, 12, 8, 6, -8, -9, 7, 0 };
    int  main()
    {
        int   pcount, mcount;
        _asm  {
            XOR   ECX, ECX          ;计数器清0
            LEA   ESI, buffer       ;ESI指向缓冲区首
        NEXT:
            LODSB                   ;取字节数据
            CMP   AL, 0             ;比较，会影响各状态标志
            JZ    SHORT  OVER       ;如果结束，则跳转
            ;
            SETG  DL                ;正数时DL=1，否则DL=0
            SETL  DH                ;负数时DH=1，否则DH=0
            ;
            ADD   CL, DL            ;统计正数
            ADD   CH, DH            ;统计负数
            JMP   NEXT              ;继续
        OVER:
            XOR   EAX, EAX          ;准备保存统计结果
            MOV   AL, CL
            MOV   pcount, EAX       ;保存正数之个数
            MOV   AL, CH
            MOV   mcount, EAX       ;保存负数之个数
        }
        printf("pcount=%d,mcount=%d\n", pcount, mcount);
        return  0;
    }
