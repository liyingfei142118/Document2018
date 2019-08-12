    //Ê¾Àýº¯Êýcf59
    int  cf59(int  **ppt, int i)
    {
        int s = 0;
        s += *( *ppt+i );           //ppt[0][i]
        s += *( *(ppt+i) );         //ppt[i][0]
        return  s;
    }
