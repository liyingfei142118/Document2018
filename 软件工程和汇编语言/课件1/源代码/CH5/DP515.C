    //演示程序dp515.cpp
    #include  <iostream>
    using  namespace  std;
    int  main()
    {
        int  test_var = 1;
        int  &ref_var = test_var;
        int  *poi_var = &test_var;              //@1
        int  *poi_ref = &ref_var;               //@2
        //
        cout<< "poi_var = " << poi_var << endl; //显示poi_var = 0042FDDC
        cout<< "poi_ref = " << poi_ref << endl; //显示poi_var = 0042FDDC
        //
        test_var = 1;                              //@3
        cout<< "test_var = " << test_var << endl;  //@4显示test_var = 1
        ref_var = 2;                               //@5
        cout<< "test_var = " << test_var << endl;  //@6显示test_var = 2
        *poi_var = 3;                              //@7
        cout<< "test_var = " << test_var << endl;  //显示test_var = 3
        return 0;
    }
