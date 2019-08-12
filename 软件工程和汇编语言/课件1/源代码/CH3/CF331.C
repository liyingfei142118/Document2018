    //示例函数cf331
    int  cf331(int arr[], int n, int * pp, int * pn)
    {
        int  i, pcount, ncount, zcount;
        pcount = ncount = zcount = 0;
        for (i=0; i<n; i++)             //循环，依次检查并统计
        {
            if ( arr[i] > 0 )
                pcount++;
            else if (arr[i] < 0 )
                ncount++;
            else 
                zcount++;
        }
        *pp = pcount;                   //送出正数的个数
        *pn = ncount;                   //送出负数的个数
        return  zcount;                 //返回0的个数
    }
