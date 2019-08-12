    //演示程序dp39
    #include  <stdio.h>
    int  main()
    {
        int  quotient, remainder;       //为了输出结果，安排两个变量
        _asm {
            MOV   AX ,-601
            MOV   BL,10
            IDIV  BL                    //除数是BL，被除数是AX
            MOV   BL,AH                 //先临时保存余数
            ;
            CBW                         //商在AL，符号扩展到AX
            CWDE                        //AX符号扩展到EAX
            MOV   quotient, EAX
            ;
            MOV   AL,BL                 //余数送到AL
            CBW                         //AL符号扩展到AX
            CWDE                        //AX符号扩展到EAX
            MOV   remainder, EAX
        }
        printf("quotient= %d\n", quotient);     //显示为-60
        printf("remainder= %d\n", remainder);   //显示为-1
        printf("\n");
        //
        _asm {
            MOV   AX ,-601
            CWD                         //AX符号扩展到DX
            MOV   BX,3
            IDIV  BX                    //除数是BX，被除数是DX:AX
            ;
            CWDE                        //商在AX，符号扩展到EAX
            MOV   quotient,EAX
            ;
            MOV   AX,DX                 //余数DX送到AX
            CWDE                        //符号扩展到EAX
            MOV   remainder,EAX
        }
        printf("quotient= %d\n", quotient);     //显示为-200
        printf("remainder= %d\n", remainder);   //显示为-1
        return  0;
    }
