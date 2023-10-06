#include <stdio.h>
#include <limits.h>

// with limits.h
int uadd_ok(unsigned x, unsigned y) {
    printf("x: %u, y: %u\n", x, y);
    return x <= (UINT_MAX - y);
}

// without limits.h
int uadd_ok_without(unsigned x, unsigned y) {
    unsigned sum = x + y;
    return sum >= x;
}

void main() {
    printf("%u\n", UINT_MAX);
    printf("%d\n", uadd_ok(10, 20));
    printf("%d", uadd_ok(UINT_MAX / 2, UINT_MAX / 2));
}
