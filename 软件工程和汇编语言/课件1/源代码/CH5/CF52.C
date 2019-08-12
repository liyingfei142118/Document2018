    int  cf52(int parx, int pary)  //示例函数cf52
    {
        int  varz;                 //整型局部变量
        varz = parx - pary;        //得到绝对值
        if ( varz < 0 )
            varz = - varz;
        return  varz;
    }
