    //演示程序dp28
    #include  <stdio.h>
    int  var1 = 0x33333333, var2 = 0x44444444, var3 = 0x55555555;
    int  bufi[3] = {0x66666666, 0x77777777, 0x88888888};
    int  main()
    {
        _asm  {     //嵌入汇编代码
            MOV   var1, 9               //双字存储单元
            MOV   WORD  PTR var2, 9     //字存储单元
            MOV   BYTE  PTR var3, 9     //字节存储单元
        }
        printf("%08XH\n",var1);         //显示为00000009H
        printf("%08XH\n",var2);         //显示为44440009H
        printf("%08XH\n",var3);         //显示为55555509H
        ;
        _asm  {     //嵌入汇编代码
            LEA   EBX, bufi             //把bufi的有效地址送到EBX
            MOV   DWORD PTR [EBX], 5    //双字存储单元
            MOV   WORD  PTR [EBX+4], 5  //字存储单元
            MOV   BYTE  PTR [EBX+8], 5  //字节存储单元
        }
        printf("%08XH\n",bufi[0]);      //显示为00000005H
        printf("%08XH\n",bufi[1]);      //显示为77770005H
        printf("%08XH\n",bufi[2]);      //显示为88888805H
        return  0;
    }
