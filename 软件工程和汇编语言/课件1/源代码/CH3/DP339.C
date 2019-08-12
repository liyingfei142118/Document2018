    //演示程序dp339.c
    #include  <stdio.h>
    int  max(int x, int y);             //声明函数原型
    int  min(int x, int y);             //声明函数原型
    //
    int  main()
    {
        int  (*pf)(int,int);            //定义指向函数的指针变量
        int  val1, val2;                //存放结果的变量

        pf = max;                       //使得pf指向函数max
        val1 = (*pf)(13,15);            //调用由pf指向的函数

        pf = min;                       //使得pf指向函数min
        val2 = (*pf)(23,25);            //调用由pf指向的函数

        printf("%d,%d\n",val1,val2);    //显示为15,23
        return  0;
    }
	////////////////////////////////////////////////////////
	//获取最大值
    int  max(int x, int y)
	{
		return  x >= y ? x:y;
	}
    //获取最小值
	int  min(int x, int y)
	{
		return  x <= y ? x:y;
	}
