    //演示程序dp324.c
    #include  <stdio.h>
    #define  COUNT  5                   //假设成绩项数
    int  main()
    {
        int  score[COUNT];              //用于存放由用户输入的成绩
        int  i, average;
        for  (i=0; i < COUNT; i++)  {   //由用户从键盘输入成绩
            printf("score[%d]=", i);
            scanf("%d", &score[i]);
        }
        //调用子程序计算成绩平均值
        _asm  {
            LEA    EAX, score
            PUSH   COUNT                //把数组长度压入堆栈
            PUSH   EAX                  //把数组起始地址压入堆栈
            CALL   AVER                 //调用子程序
            ADD    ESP, 8               //平衡堆栈
            MOV    average, EAX
        }
        //
        printf("average=%d\n",average); //显示所得平均值
        return 0;
        //子程序AVER
        _asm  {
        AVER:                           //子程序入口
            PUSH  EBP
            MOV   EBP, ESP              //建立堆栈框架
            MOV   ECX, [EBP+12]         //取得数组长度
            MOV   EDX, [EBP+8]          //取得数组起始地址
            XOR   EAX, EAX              //将EAX作为和sum
            XOR   EBX, EBX              //将EBX作为下标i
            JECXZ  OVER                 //如数组长度为0，不循环累加
        NEXT:
            ADD   EAX, [EDX+EBX*4]      //累加
            INC   EBX                   //调整下标i
            LOOP  NEXT                  //减计数方式控制循环
            ;
            CDQ                         //计算平均值
            IDIV  DWORD PTR [EBP+12]
        OVER:
            POP   EBP                   //撤销堆栈框架
            RET                         //返回
        }
    }
