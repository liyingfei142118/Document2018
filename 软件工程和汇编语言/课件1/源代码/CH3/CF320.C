    //Ê¾Àýº¯Êýcf320
    int  cf320(unsigned  int  n)
    {
        int  len = 0;
        do  {
            len++;
            n = n/10;
        } while (n != 0);
        return  len ;
    }
