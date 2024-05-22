#include <stdio.h>

long shift_left4_rightn(long x, long n) {
    x <<= 4;
    x >>= n;
    return x;
}

int main() {
    printf("%d", shift_left4_rightn(15, 5));
}
