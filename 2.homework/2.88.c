#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

/*
  format A
  s=1
  k=5, bias is 15
  n=3, fraction bits

  format B
  s=1
  k=4
  n=4

  convert A->B
  round towards +inf
 */

int C(double x, double y, double z) {
    return (x + y) + z == x + (y + z);
}

int D(double x, double y, double z) {
    return (x * y) * z == x * (y * z);
}

int main(void) {
    /* 2.90 */

    return 0;

    /* 2.89
       A. always true. double more precise so casting (float)(double) is the same as the original float.
       B. not always true, if (x-y) results in a rounding error and not (dx-dy).
       C. always true. no rounding error, the integer sums stay less than the smallest int that is not exactly representable as double.
       D. not always true. You can reach odd values greater than the smallest odd value that can be represented exactly. The trick is to get different rounding on both sides of the ==. (very interesting result about double and float overflows, rounding to nearest even that is greater than 2^(n+1)+1) (2^30 + 1, 2^24 + 1, 2^23 + 1, any odd value greater than 2^53 + 1 will be rounded to an even number that is greater than 2^53 + 1. The amount of rounding depends on how much powers of two greater than 53 are needed to represent the number.)
       E. not always true, 0 zero division is undefined. (No nan and inf since the original values are integers)
     */
    int x = random();
    int y = random();
    int z = random();
    double dx = (double) x;
    double dy = (double) y;
    double dz = (double) z;
    printf("x: %d, y: %d, z: %d\n", x, y, z);
    printf("%d\n", (float) x == (float) dx);
    printf("%d\n", C(1, 1<<31, 1<<31));
    printf("D: %d\n", D(INT_MAX, INT_MAX, INT_MAX));
    return 0;

    /* 2.88 in ora */
    return 0;
}
