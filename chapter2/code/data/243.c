// #define M
// #define K
// int arith(int x, int y) {
//     int result = 0;
//     result = x*M + y/N;
//     return result;
// }
//
// int optarith(int x, int y) {
//     int t = x;
//     x <<= 5;
//     x -= t;
//     if (y < 0) y += 7;
//     y >>= 3;
//     return x+y;
// }
#include <stdio.h>

int main() {
    int x = 3;
    printf("%d", x<<1);
}
