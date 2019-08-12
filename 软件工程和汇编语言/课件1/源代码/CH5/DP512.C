    //演示程序dp512.c
    #include  <stdio.h>
    struct  STUDENT                     //声明结构体类型STUDENT
    {
        int   num;                      //整型（4字节）
        char  name[14];                 //字符型数组（16字节）
        int   score;                    //整型（4字节）
        char  grade;                    //字符型（4字节）
    };
    char  cf513(struct  STUDENT  stux); //声明函数原型
    char  cf514(struct  STUDENT  *pp);  //声明函数原型
    //                                  //定义全局结构体变量zhang
    struct  STUDENT  zhang = {103,"ZHANG",88,'3'};
    //
    int  main()
    {
        struct  STUDENT  stu;           //定义结构体变量
        char  g1, g2;                   //定义字符型变量
        stu = zhang;                    //结构体变量赋值
        stu.num = 108;                  //结构体成员赋值
        stu.name[2] = 'E';              //结构体成员的元素赋值
        printf("%s=%d\n", stu.name, stu.num);
        g1 = cf513(stu);                //实参是结构体变量
 		g2 = cf514(&stu);               //实参是结构体变量的地址
        printf("g1=%c,g2=%c\n", g1, g2);
        return  0;
    }
