    //示例函数cf55
    //一个字符型参数，返回一个整型值
    int  cf55(char  parc)
    {    
        unsigned  char  cvar = 18;      //无符号字符型变量
        cvar = cf54(cvar, parc);        //调用函数cf54
        cvar = cvar - 31 ;
        return  cvar;
    }
