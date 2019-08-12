    //Ê¾Àıº¯Êıcf312
    unsigned int  cf312(unsigned int x, unsigned int y)
    {
        int  z = 0;
        if ( ( x & 3 ) || ( ( x - 5 ) | ~y ) )
        {
            z = x ^ 255;
        }
        return  z;
    }
