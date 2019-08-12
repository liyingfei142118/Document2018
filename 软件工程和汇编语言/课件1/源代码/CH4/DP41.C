    //演示程序dp41.c
    #include  <stdio.h>
    int  main()
    {
        char  src_str[14]= "abcdefghijklm"; //源字符串
        char  temp[14];
        char  dst_str[14];                  //作为目的字符串
        //第一种方式
        _asm  {
            LEA   ESI, src_str          //取得源串起始地址
            LEA   EDI, temp             //取得目的串起始地址
            MOV   ECX, 14               //字符串长度
        LAB1:
            MOV   AL,[ESI]              //从源串取一个字节
            INC   ESI                   //调整指向源串的指针
            MOV   [EDI],AL              //复制到目的串
            INC   EDI                   //调整指向目的串的指针
            LOOP  LAB1                  //循环处理
        }
        //第二种方式
        _asm  {                         //使用串操作指令的方式
            LEA   ESI, src_str          //取得源串起始地址
            LEA   EDI, dst_str          //取得目的串起始地址
            MOV   ECX, 14               //字符串长度
        NEXT:
            LODSB                       //串装入指令  //@1
            STOSB                       //串存储指令  //@2
            LOOP  NEXT                  //循环处理
        }
        //
        printf("%s\n", temp);           //显示相同的字符串
        printf("%s\n", dst_str);        //显示相同的字符串
        return  0;
    }
