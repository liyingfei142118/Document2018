    //演示程序dp21
    #include  <stdio.h>
    int  main(  )
    {
        int  varx = 0x11223344, vary = 0;
        //嵌入汇编
        _asm  {
            MOV   EAX, varx             //把变量varx的值送到寄存器EAX
            MOV   AX, 5566H             //把十六进制值5566H送到寄存器AX
            MOV   AL, 77H               //把十六进制值77H送到寄存器AL
            MOV   vary, EAX             //把寄存器EAX的值送到变量vary
        }
        printf("vary=%08XH\n",vary);    //显示为vary=11225577H
        return  0;
    }
