    //演示程序dp412.c（处理8X8点阵）
    #include  <stdio.h>
    void  pbmp_8X8(unsigned char bitmap[]);
    unsigned char  bitmap_a[8] = {0x10,0x28,0x44,0x82,0xFE,0x82,0x82,0x82};
    unsigned char  bitmap_b[8];
    int main( )
    {
        pbmp_8X8( bitmap_a );           //显示原始点阵
        printf("\n");
        //调用顺时针旋转90度子程序
        _asm  {
            LEA   EAX, bitmap_b
            PUSH  EAX                   ;压入目标点阵首地址
            LEA   EAX, bitmap_a
            PUSH  EAX                   ;压入原始点阵首地址
            CALL  RIGHT90               ;调用子程序
            ADD   ESP, 8                ;平衡堆栈
        }
        ;
        pbmp_8X8( bitmap_b );           //显示目标点阵
        return  0;
        //
        //此处安排子程序as411代码
        //
    }
    //显示8X8点阵信息（用点号表示0，用星号表示1）
    void  pbmp_8X8(unsigned  char  bitmap[])
    {
        int  i, j;
        unsigned  int lineb;
        unsigned  char  ch;
        for ( i=0; i<8; i++ )           //逐行
        {
            lineb = bitmap[i];
            for ( j=7; j>=0; j-- )      //逐列
            {
                ch = '.';               //用点号表示0
                if ( lineb & ( 1<<j ) )
                    ch = '*';           //用星号表示1
                printf("%c", ch);
            }
            printf("\n");
        }
    }
