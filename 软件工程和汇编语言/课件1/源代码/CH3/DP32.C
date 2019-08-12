    //演示程序dp32
    #include  <stdio.h>
    char  string[] = "abcde";
    int  main()
    {
        _asm  {                     //嵌入汇编代码
            LEA   ESI, string       //ESI指向string首
            MOV   AX, [ESI]
            CALL  TUPPER            //调用子程序tupper
            MOV   [ESI], AX
            MOV   AX, [ESI+2]
            CALL  TUPPER            //调用子程序tupper
            MOV   [ESI+2], AX
            MOV   AL, [ESI+4]
            CALL  UPPER             //调用子程序upper
            MOV   [ESI+4], AL
        }
        printf("%s\n", string);     //显示为ABCDE
        return  0;
        //嵌入汇编代码形式的子程序
        __asm  {                    //嵌入汇编代码
        UPPER:                      //子程序入口标号
            CMP   AL, 'a'
            JB	  UPPER2
            CMP   AL, 'z'
            JA    UPPER2
            SUB   AL, 20H           //小写转大写
        UPPER2:
            RET                     //返回
        //
        TUPPER:                     //子程序入口标号
            CALL  UPPER             //调用子程序
            XCHG  AH, AL
            CALL  UPPER             //调用子程序
            XCHG  AH, AL
            RET                     //返回
        }
    }
