    //ÑÝÊ¾³ÌÐòdp13
    #include  <stdio.h>
    char  buff[] = { 3, 2, 1, 0, 130 };     // 130=0x82
    int  a, b;
    int  main( )
    {
        char  *p = buff;
        //
        a = *( int* ) p;                   //L1
        b = *( int* ) ( p+1 );             //L2
        //
        printf( "a = %x, b=%x\n", a, b );  //L3
        printf( "a = %d, b=%d\n", a, b );  //L4
        return  0;
    }
