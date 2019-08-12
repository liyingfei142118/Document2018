    //Ê¾Àıº¯Êıcf317
    int  cf317(int  m)
    {
        m = m & 0x0f;
        m +=  0x30;
        if ( m > '9' )
            m +=  7;
        return  m;
    }
