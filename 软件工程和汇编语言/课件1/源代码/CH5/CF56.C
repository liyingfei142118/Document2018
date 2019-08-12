    //Ê¾Àıº¯Êıcf56
    int  cf56(int  para,  int  parb)
    {
        int m, n, x;
        m = n = 0;
        x =  ( para >= parb ) ?  ( m =  1 ) : ( n =  2   );
        x += ( para <= parb ) || ( m += 10  ,   n += 20  );
        x += ( para != parb ) && ( m += 100 ,   n += 200 );
        return  x + m + n;
    }
