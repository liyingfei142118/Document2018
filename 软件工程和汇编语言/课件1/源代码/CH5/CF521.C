    //示例函数cf521
    //功能：判断由参数给定的年份是否为闰年
    int  cf521(unsigned  int  year)
    {
        int  leap = 0;
        if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
            leap = 1;
        return  leap;
    }
