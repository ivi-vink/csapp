#include <stdio.h>

int div16(int x) {
    // my inefficient method that just checks the sign bit: int sign_bit = (unsigned) (x & 1<<31) >> 31;
    int bias = (x >> 31) & 0xF;
    return (x + bias)>>4;
}

void main() {
    int result = div16(-17);
    printf("%d\n", result);
    result = div16(17);
    printf("%d\n", result);
}
