    //ÑÝÊ¾³ÌÐòdp519.cpp
    #include<iostream>
    using  namespace  std;
    class  A1
    {
    public:
        virtual  void  vget() { cout<<"A1::vget"<<endl;  return; }
        void  get()  { cout<<"A1::get"<<endl;  return; }
    };
    //
    class  A2 : public A1
    {
    public:
        virtual  void  vget() { cout<<"A2::vget"<<endl;  return; }
        void  get()  { cout<<"A2::get"<<endl;  return; }
    };
    //
    void  cfd(A1  & a)
    {
        a.vget();
        a.get();
        return;
    }
    //
    int  main()
    {
        A1  a1;
        A2  a2;
        //
        cfd(a1);
        cfd(a2);
        return  0;
    }
