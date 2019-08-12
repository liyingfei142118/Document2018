    //演示程序dp524.c
    //演示Base64的编码和解码
    #include  <stdio.h>
    #include  <string.h>
    #define   BUFFLEN   256
    #define   SIZE      64
    //Base64编码对照表
    const char const  *CharSet =
        { "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/" };
    //函数声明
    int Base64Encode(char * const dest, const unsigned char * src, int srcLen);
    int Base64Decode(unsigned char * const dest, const char * src);
    unsigned int Chr2Index(char ch);
    //主函数
    int main(int argc, char* argv[])
    {
        char  text[BUFFLEN] = {0};          //存放输入数据
        char  buff[BUFFLEN * 2];            //存放转换结果
        char  mode;                         //操作方式

        printf("Encode | Decode ? :");      //由用户选择操作方式
        scanf("%c", &mode);
        mode |= 0x20;
        if ( !(mode == 'e' || mode == 'd') )
            return 1;

        printf("Input text:");              //由用户输入数据（字符串）
        scanf("%s", text);

        if (mode == 'e')                    //编码处理
            Base64Encode(buff, (const unsigned char *)text, strlen(text));
        else
        {                                   //解码处理
            int len=Base64Decode((unsigned char*)buff, text);
            text[len] = '\0';               //为了显示输出，添加字符串结束符
        }

        printf("%s\n", buff);
        return 0;
    }
    /*===========================================================
    功    能：对指定数据进行Base64编码
    入口参数：char * const dest          编码结果缓冲区首地址
              const unsigned char * src	 待编码数据首地址
              int srcLen                 待编码数据的长度
    出口参数：int                        编码结果的字符串长度
    说    明：编码结果缓冲区大小至少是srcLen的三分之四倍加一
    ============================================================*/
    int Base64Encode(char * const dest, const unsigned char * src, int srcLen)
    {
        unsigned char  * ps = (unsigned char *)src;
        char           * pd = dest;
        int            i = 0;
        unsigned char  temp;
        //
        //依次编码（3个字节原始数据，转换成4个字符）
        while (i < srcLen)
        {
            switch (i % 3)
            {
            case 0:
                *pd++ = CharSet[*ps >> 2];
                temp = (*ps++ << 4) & 0x3f;
                break;
            case 1:
                *pd++ = CharSet[temp | (*ps >> 4)];
                temp = (*ps++ << 2) & 0x3f;
                break;
            case 2:
                *pd++ = CharSet[temp | (*ps >> 6)];
                *pd++ = CharSet[*ps++ & 0x3f];
                break;
            }
            i++;
        }
        //处理剩余的零头部分，用"="填补结果字符串不足
        if (srcLen % 3 != 0)
        {
            *pd++ = CharSet[temp];
            if (srcLen % 3 == 1)
                *pd++ = '=';
            *pd++ = '=';
        }
        *pd = 0;                    //添加结果字符串的结束标志
        return (pd - dest);         //返回结果字符串的长度
    }
    /*========================================================
    功    能：对指定字符串进行Base64解码
    入口参数：unsigned char * const dest  结果数据缓冲区首地址
              const char * src	          待解码字符串首地址
    出口参数：int                         结果数据长度
    说    明：解码结果缓冲区大小至少是待解码长度的四分之三倍
    ========================================================*/
    int Base64Decode(unsigned char * const dest, const char * src)
    {
        char          * ps = (char *)src;
        unsigned char * pd = dest;
        int           i = 0;
        unsigned char ch, temp;
        int srcLen = strlen(src);
        //依次解码（4个字符，转换为3字节数据）
        while (i < srcLen)
        {
            if (*ps == '=')	        //是否遇到结束字符？
                break;
            ch = Chr2Index(*ps++);  //由字符得对应索引值
            
            switch (i % 4)
            {
            case 0:
                temp = ch << 2;
                break;
            case 1:
                *pd++ = temp | (ch >> 4);
                temp = ch << 4;
                break;
            case 2:
                *pd++ = temp | (ch >> 2);
                temp = ch << 6;
                break;
            case 3:
                *pd++ = temp | ch;
                break;
            }
            i++;
        }
        return (pd - dest);         //返回结果数据的字节数
    }
    /*==========================================================
    功    能：查找Base64编码表，获得指定字符的索引值
    入口参数：char ch       指定字符
    出口参数：unsigned int  索引值（序号）
    说    明：0到63为正常序号，64表示无效字符（非Base64编码表符号）
    ===========================================================*/
    unsigned int Chr2Index(char ch)
    {
        int i;
        for (i = 0; i < SIZE; i++)
        {
            if (ch == CharSet[i])
                break;
        }
        return i;
    }
