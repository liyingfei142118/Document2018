    //示例函数cf315
    int  cf315(int  ch)
    {
        if ( ch >= 'A' && ch <= 'Z' )
            ch += 0x20;     //小写字母与对应大写字母ASCII码相差32
        return  ch;
    }
