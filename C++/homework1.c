#include <stdio.h>

int main() {
    int i = 1, j = -1;
    i=i&j;
    printf("i after AND operation: %d\n", i);
    i=i|j;
    printf("i after OR operation: %d\n", i);
    i=~i;
    printf("i after ~ operation: %d\n", i);
    return 0;
}
