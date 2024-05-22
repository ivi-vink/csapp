#include <stdio.h>
#include <assert.h>
#include <limits.h>

/* To do this we can use the formulas we derived earlier.
   17 = 16 + 1
   = x<<4 + x<<0
*/
int mul_by_17(int x) {
    return (x<<4) + x;
}

int mul_by_minus_7(int x) {
    return - (x<<2) - (x<<1) - x;
}

int mul_by_60(int x) {
    return (x<<6) - (x<<2);
}

int mul_by_minus_112(int x) {
    return - (x<<7) + (x<<4);
}

/*
  Divide by power of 2. Assume 0 <= k < w - 1
  when x/k >= 0, rounding is already done towards 0.

  when x/k < 0, rounding is done to the next smallest integer. Instead we want to round to the next greatest integer.
  We can add a bias to the negative x that ensures the division by k rounds downwards, but that the result is one k greater when division has a remainder.

  The example from the book uses the ternary conditional operator:
  (x<0 ? x+(1<<k)-1 : x) >> k
*/
int divide_power2(int x, int k) {
    /* Get ones mask if msb is set */
    int msb = (x>>31);
    int bias = (1<<k)-1;
    /* Add bias if ones mask */
    x += msb & bias;
    return x >> k;
}

int mul3div4(int x) {
    /* Multiply by 3 */
    x += (x<<1);

    int k = 2;
    int msb = (x>>31);
    int bias = (1<<k)-1;
    /* Add bias if ones mask */
    x += msb & bias;
    return x >> k;
}

/*
  I kind of missed the fact that the remainder is always less than four, so the only part of a number that causes rounding errors are those less than four.
  So we could split up x into the bits that are four or greater, and bits that are less than four.
  Rounding is then only relevant for the bits less than four.

  My method uses the remainder. No idea if it is a true generic solution, but it looks consistent with integer arithmetic rules.
 */
int threefourths(int x) {
    int k = 2;
    int msb = (x>>31);
    int bias = (1<<k)-1;
    /* Add bias if ones mask */
    int q = (x + (msb & bias)) >> k;
    /* Calculate remainder so we know how to compensate when multiplying */
    int r = x - (q << k);
    r = (((r<<1) + r) + ((r >> 31) & bias)) >> k;
    return (q<<1) + q + r;
}


int main() {
    /* 2.80 */
    assert(threefourths(8) == 6);
    assert(threefourths(9) == 6);
    assert(threefourths(10) == 7);
    assert(threefourths(11) == 8);
    assert(threefourths(12) == 9);
    assert(threefourths(INT_MAX) == 1610612735);

    assert(threefourths(-8) == -6);
    assert(threefourths(-9) == -6);
    assert(threefourths(-10) == -7);
    assert(threefourths(-11) == -8);
    assert(threefourths(-12) == -9);
    assert(threefourths(-INT_MAX) == -1610612735);
    printf("%d\n", threefourths(-11));
    return 0;

    /* 2.79 */
    printf("%d\n", mul3div4(-15));
    return 0;

    /* 2.78 */
    printf("%d\n", divide_power2(-15, 1));
    return 0;

    /* 2.77 */
    printf("%d\n", mul_by_17(2));
    printf("%d\n", mul_by_minus_7(2));
    printf("%d\n", mul_by_60(2));
    printf("%d\n", mul_by_minus_112(1));
    return 0;
}
