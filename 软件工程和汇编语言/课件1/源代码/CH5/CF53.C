    unsigned  cf53(unsigned  int  parx) //示例函数cf53
    {
        unsigned  char  ch1, ch2;       //字符型局部变量
        unsigned  sum;                  //整型局部变量
        ch1 = parx >> 24;               //得到参数的最高8位
        ch2 = parx & 0xff;              //得到参数的最低8位
        sum = ch1+ch2;
        return  sum;
    }
