    //演示程序dp29
    #include  <stdio.h>
    char  chx, chy;                 //全局字符变量
    int  main( )
    {
        char  *p1, *p2;             //两字符型指针变量
        //嵌入汇编代码之一
        _asm {
            LEA   EAX, chx          //取变量chx的存储单元有效地址
            MOV   p1, EAX           //送到指针变量p1
            LEA   EAX, chy          //取变量chy的存储单元有效地址
            MOV   p2, EAX           //送到指针变量p2
        }
        printf("Input:");           //提示
        scanf("%c",p1);             //键盘输入一个字符
        //嵌入汇编代码之二
        _asm {
            MOV   ESI, p1           //取回变量chx的有效地址
            MOV   EDI, p2           //取回变量chy的有效地址
            MOV   AL, [ESI]         //取变量chx之值
            MOV   [EDI], AL         //送到变量chy中
        }
        printf("ASCII:%02XH\n",*p2);//十六进制形式显示对应ASCII码值
        return  0;
    }
