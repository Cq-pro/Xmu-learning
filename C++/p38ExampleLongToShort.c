#include <stdio.h>
#include <stdlib.h>

void hex_out(char a)
{
    const char HEX[]="0123456789ABCDEF";
    printf("%c%c",HEX[(a&0xF0)>>4],HEX[a&0x0F]);
}

void out_1byte(char *addr)
{
    hex_out(*(addr +0));
}

void out_2byte (char *addr)
{
    //小端模式先输出高字节
    hex_out (* (addr +1));hex_out (* (addr +0));
}

void out_4byte (char *addr)// 用十六进制输出地址中的32位数据机器码
{
    // 小端模式先输出高字节
    hex_out (* (addr +3)); hex_out (* (addr +2)); hex_out (* (addr +1)); hex_out (* (addr +0));
}

int main ()
{
    int i=0xFADF1001;
    short s;
    unsigned short us;
    s=i ;
    us=i;
    out_4byte (&i) ;
    printf(" = i = %d \n",i);
    out_2byte (&s) ;
    printf (" = s = %d \n", s) ;
    out_2byte (&us) ;
    printf(" = us = %u \n", us) ;
}
