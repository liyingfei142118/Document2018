    //演示程序dp511.c
    #include  <stdio.h>
    int   cf58(int *pit);
    int   cf59(int  **ppt, int i);
    void  cf510(int  matrix[][5], int  line[],  int i);
    int  main( )
    {
        int  data[3][5]={ {1,  2,  3,  4,  5  },
                          {11, 12, 13, 14, 15 },
                          {101,102,103,104,105} };
        int  *p[3] = { data[0], data[1], data[2] };
        int  row[5];
        int  i;
        printf("%d\n", cf58(data[0]));  //调用cf58
        printf("%d\n", cf59(p,2));      //调用cf59
        cf510(data, row, 0);            //调用cf510
        for (i=0; i<5; i++)
            printf("%-4d", row[i]);
        printf("\n");
        return  0;
    }
