    //示例函数cf319
    int  cf319(int x,  int operation)
    {
        int  y;
        //多路分支
        switch ( operation ) {
            case 1:
                y = 3*x;
                break;
            case 2:
                y = 5*x+6;
                break;
            case 4:
            case 5:
                y = x*x ;
                break;
            case 8:
                y = x*x+4*x;
                break;
            default:
                y = x ;
        }
        if ( y > 1000 )
            y = 1000;
        return  y;
    }
