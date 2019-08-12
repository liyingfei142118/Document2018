    //ÑÝÊ¾³ÌÐòdp518.cpp
    #include  <iostream>
    using  namespace  std;
    class  test_class
    {
    public:
        void  cfm(int i, int j)
        {
            cout << "int" << i+j << endl;
            return;
        }
        //
        void  cfm(char  ch)
        {
            cout << "char" << ch << endl;
            return;
        }
    };
    //
    int main()
    {
        test_class  obj;
        obj.cfm(3, 4);
        obj.cfm('A');
        return  0;
    }
