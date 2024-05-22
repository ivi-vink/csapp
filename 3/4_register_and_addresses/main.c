#include <stdio.h>

void decode1(long *xp, long *yp, long *zp) {
    long x = *xp;
    long y = *yp;
    long z = *zp;

    *yp = x;
    *zp = y;
    *xp = z;
}

long scale(long x, long y, long z) {
    long t = x + 4 * y + 12 * z;
    return t;
}

long scale3(long x, long y, long z) {
    long t = 10 * y + z + x * y;
    return t;
}

int main(void) {
    char c = 0xC0;
    int x = (int) c;
    printf("%d", x);
}
