    //演示程序dp413.C
    //处理16X16点阵
    #include  <stdio.h>
    void  pbmp_16X16(unsigned char bitmap[]);
    //原始16X16点阵信息
    unsigned char fonts[32] = { 0x00,0x00,0xc0,0x03,0xf0,0x0f,0xf8,0x1f,
                                0xf8,0x1f,0xfc,0x3f,0xfc,0x3f,0xfc,0x3f,
                                0xfc,0x3f,0xfc,0x3f,0xf8,0x1f,0xf8,0x1f,
                                0xf0,0x0f,0xc0,0x03,0x00,0x00,0x00,0x00  };
    unsigned  char  cycle[32]={0};              //准备存放目标点阵
    int main()
    {
        pbmp_16X16( fonts );               //显示原始点阵//
        printf("\n");
        //使得每一行仅剩可能存在的最右和最左的各一位为"1"的位
        _asm  {
            LEA   ESI, fonts -2            ;设置原始点阵区域首地址（减2）
            LEA   EDI, cycle -2            ;设置目标点阵区域首地址（减2）
            MOV   ECX, 16                  ;共计16行
        NEXT:
            BSF   AX, WORD PTR [ESI+ECX*2]  ;确定原始点阵行最右侧"1"位
            JZ    CONT                      ;如果整行没有"1"，跳转
            BTS   WORD PTR [EDI+ECX*2], AX  ;设置目标点阵对应的位为"1"
            BSR   AX, WORD PTR [ESI+ECX*2]  ;确定原始点阵行最左侧"1"位
            BTS   WORD PTR [EDI+ECX*2], AX  ;设置目标点阵对应的位为"1"
        CONT:
            LOOP  NEXT                      ;下一行
        }
        //
        pbmp_16X16( cycle );                //显示目标点阵
        return 0;
    }
    //显示输出16X16点阵（位值0或1，分别用字符"0"和"1"表示）
    void  pbmp_16X16(unsigned char bitmap[])
    {
        int  i, j;
        unsigned int lineb;
        unsigned char ch;
        for (i=0; i<16; i++)                //行为单位显示
        {	
            lineb = ( bitmap[i*2+1] << 8 ) + bitmap[i*2];
            for ( j=15; j>=0; j-- )         //显示一行之各列
            {
                ch = ( lineb & ( 1<<j ) ) ? 1 : 0;
                ch += '0';
                printf("%c", ch);
            }
            printf("\n");
        }
    }
