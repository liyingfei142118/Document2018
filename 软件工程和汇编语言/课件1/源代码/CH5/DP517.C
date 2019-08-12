    //演示程dp517.cpp
    #include  <iostream>
    using  namespace  std;
    int  tfc(int  i)                //参数整型
    {
        cout << "int" << i << endl;
        return 0;
    }
    //
    void  tfc(char  ch)             //参数字符型
    {
        cout << "char" << ch << endl;
        return;
    }
    //
    int  main( )
    {
        tfc(2);                     //显示int2
        tfc('A');                   //显示charA
        tfc('A'+'B');               //显示int131
        return  0;
    }
