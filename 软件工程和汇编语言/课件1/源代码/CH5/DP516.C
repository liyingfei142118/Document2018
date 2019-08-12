    //ÑÝÊ¾³ÌÐòdp516.cpp
    #include  <iostream>
    using  namespace  std;
    void  tf1(int *p)
    {
        (*p)++;
        return;
    }
    //
    void  tf2(int &r)
    {
        r++;
        return;
    }
    //
    int  main()
    {
        int  test_var = 1;
        //
        tf1(&test_var);
        tf2(test_var);
        cout<< "test_var = " << test_var << endl;  //ÏÔÊ¾test_var = 3
        return  0;
    }
