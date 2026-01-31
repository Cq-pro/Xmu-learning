#include <stdio.h>
#include <stdlib.h>

union
{
    int i; unsigned int ui; float f;
    short s; unsigned short us;
    char c; unsigned char uc;

}t;

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

void main ()
{
    t. i=0x8753AAD3;//直接通过机器码赋值，联合体中所有变量共享该机器码
    out_4byte (&t. i) ;// 输出i的机器码和真值，&表示引用变量的内存地址
    printf(" = %d \n", t.i);// C77FFFFF = -947912705
    out_4byte (&t. ui) ;// 输出ui 的机器码和真值
    printf(" = %u \n",t.ui);// C77EEEFE = 3347054591
    out_4byte (&t. f) ;// 输出王的机器码和真值
    printf (" = %f\n", t. f) ;// C77FFFFF = -65535. 996094
    out_2byte (&t. s) ;// 输出s的机器码和真值
    printf(" = %d \n", t.s);//FETE =-1 整数采用补码表示
    out_2byte (&t. us) ;//输出us 的机器码和真值
    printf(" = %u \n", t.us);// FFEE = 65535
    out_1byte(&t.c);// 输出c的机器码和真值
    printf (" = %d\n", t.c) ;// EF =-1
    out_1byte(&t.uc);// 输出uc 的机器码和真值
    printf(" = %d\n", t.uc);// EE = 255
}
