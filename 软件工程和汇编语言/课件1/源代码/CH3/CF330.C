    //示例函数cf330
    void  _fastcall  cf330(unsigned  m, char *buffer)
    {
        int  i;
        char  val;
        for (i=1; i<=8; i++)                     //循环8次
        {
            val = ( m >> (32 - i * 4) ) & 0x0f;  //先向右移，再截取4位
            val += '0';                          //转成对应ASCII码
            if ( val > '9') val += 7;
            *buffer++ = val;                     //依次保存
        }
        *buffer = '\0';                          //ASCII码串结束标记
        return ;
    }
