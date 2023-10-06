#include <stdio.h>

int bis(int x, int m) {
    return x | m;
}
int bic(int x, int m) {
    return x & ~m;
}
int bool_or(int x, int y) {
    int result = bis(x, y);
    return result;
}
int bool_xor(int x, int y) {
    int result = bis(bic(x, y), bic(y, x));
    return result;
}
int bool_eq(int x, int y) {
    int result = !(x^y);
    return result;
}

void main() {
    printf("=== 2.11 ===\n");
    int x = 0x87654321;
    printf("%x\n", x & 0xFF);
    printf("%x\n", ~x ^ 0xFF);
    printf("%x\n", x | 0xFF);

    printf("=== 2.12 ===\n");
    printf("%x\n", bool_or(1, 1));
    printf("%x\n", bool_xor(1, 1));

    printf("=== 2.15 ===\n");
    printf("%x\n", bool_eq(0x87654321, 0x87654321));
    printf("%x\n", bool_eq(14, 13));
}
