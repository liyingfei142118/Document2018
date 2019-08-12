    //示例函数cf328
    int  cf328(unsigned  arr[], int n)
    {
        int  i;                         //循环变量
        unsigned  value;                //用于判断特征值
        int  count = 0;                 //统计数据中1的个数
        for (i=0; i<n; i++)             //循环遍历数组中的每个数据
        {
            value = arr[i];
            if ( value <= 0xfffff )     //0xfffff是20位1的最小值
                continue;               //如不超过0xfffff，肯定不是特征数据
            count = 0;
            while ( value != 0 )        //统计1的个数
            {
                if ( value & 1 == 1 )   //测最低位是否为1
                    count++;
                value = value >> 1;     //向右移1位
            }
            if ( count > 20 )           //找到第一个，跳出循环
                break;
        }
        if ( count <= 20 )              //如没有找到特征数据，返回-1
            i = -1;
        return  i;
    }
