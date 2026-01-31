/*第一行为n，表示测试数据组数。(n<30) 
每组测试的第一行是一个整数m，表示多重集S中元素的个数为m 
接下来的一行中给出m(m<100)个不大于10万的自然数 */
#include <stdio.h>

int main() {
    int i = 1, j = -1;

    __asm {
        mov  i, eax; 将 i 的值移动到 eax 寄存器
        and j, eax; 使用 j 的值和 eax 寄存器进行按位与运算
        mov  eax, i; 将 eax 寄存器的值移动回 i
    }

    printf("i after AND operation: %d\n", i);

    __asm {
        mov  i, eax; 将 i 的值移动到 eax 寄存器
        or j, eax; 使用 j 的值和 eax 寄存器进行按位或运算
        mov  eax, i; 将 eax 寄存器的值移动回 i
    }

    printf("i after OR operation: %d\n", i);

    return 0;
}


