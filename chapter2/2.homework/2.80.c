#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

unsigned bit_pattern_A(int k) {
    return (~0)<<k;
}

unsigned bit_pattern_B(int k, int j) {
    return ~((~0)<<k) << j;
}

float fraction_bit_pattern(unsigned Y, unsigned k) {
    return 0;
}

unsigned f2u(float f) {
    union {
        float f;
        unsigned u;
    } fu = { .f = f };
    return fu.u;
}

/*
  floating point number
  The unsigned numbers can be compared.
  The bits in the unsigned number can be mapped to bits in the floating point number in a monotonic way.
 */
int float_le(float x, float y) {
    unsigned ux = f2u(x);
    unsigned uy = f2u(y);
    printf("ux: %x, uy: %x, ux<=uy: %d\n", ux, uy, ux<=uy);

    /*  Get the sign bits */
    unsigned sx = ux >> 31;
    unsigned sy = uy >> 31;
    printf("sx: %d, sy: %d\n", sx, sy);

    /* Give an expression using only ux, uy, sx, and sy */
    printf("sx && !sy: %d, ((uy - sy) <= (ux - sx)): %d\n", sx && !sy, ux<=uy);
    return (ux << 1 == 0 && uy << 1 == 0)
        || (sx && !sy)
        || (sx && sy) && (uy <= ux)
        || ((!sx && !sy) && (ux <= uy));
}

int main() {
    /* 2.85
       V=(2^E)*M
       bias=2^(k-1) - 1
       k=8
       0111 1111
       k bit exponent has values from (2^k)-bias

       (A) V=7.0
           E=(bias+2)-bias, has k-1 bit set plus 1, since (2^(k-1) -1)-bias == 0
           M=1/2+1/4=3/4, first two bits
           7.0=2^2(1+f)=4+4f=4+3
       (B)
       largest integer --> largest odd integer
     */
    return 0;

    /* 2.84 */
    printf("%d\n", f2u(0.1f));
    printf("%d\n", float_le(1, 0.1));
    return 0;

    /* 2.83
       Y=B2U(y), y is k bit word
       I couldn't solve this one. Was stuck looking for patterns with arrows and tables instead of algebra.

       n = 0.yyyy..
       n<<k = y.yyyy..
       n<<k = Y + n
       n<<k - n = Y
       n(1<<k - 1) = Y
       n = Y/(1<<k - 1)

       B. (a) 1/3
          (b) 6/15 -> 2/5
          (c) 19/63
     */
    return 0;

    /*
      32bit int and unsigned with arithmetic shift
     */
    srand(time(NULL));
    int x = random();
    int y = random();
    unsigned ux = (unsigned) x;
    unsigned uy = (unsigned) y;
    printf("x: %d, y: %d\n", x, y);
    /*
      x<y == -x>-y
      +x +y -> always true
      -x -y -> alwyas true
      -x +y -> x<y is true, -x>-y is also true, since the sign changes
      +x -y -> x<y is false, -x>-y is also false, since the sign changes
     */
    printf("A: %d\n", (x<y) == (-x>-y));
    /*
      <=>
      ((x<<4) + (y<<4) + y - x) mod 2^w
      (16x + 16y + y - x) mod 2^w
     */
    printf("B: %d\n", ((x+y)<<4) + y-x == 17*y+15*x);
    /*
      ~:
      number --(~)--> -number -1

      Using this observation we can do this (everything is under modulo 2^w, which is fine... right?):
      ~x + ~y + 1:
      -x - 1 - y - 1 + 1
      -x -y - 1
      -(x+y) - 1
      ~(x+y)
     */
    printf("C: %d\n", ~x + ~y + 1 == ~(x+y));

    /*
      number --(unsigned)--> number + msb * 2^32

      x + (msbx * 2^32) - (y + msby * 2^32)
      x - y + msbx * 2^32 - msby * 2^32
      -(y-x) + msbx * 2^32 - msby * 2^32

      -(unsigned)(y-x)
      -((y-x) + (msbyx * 2^32))
      -(y-x) - (msbyx * 2^32)

      (msbx * 2^32 - msby * 2^32) = (msbyx * 2^32) = 0?
      msbx = 0 and msby = 0 -> msbyx = 0 ?
      0100 - 0101 = 1111 -> if x > y and x,y>0 this expression is not true
     */
    y = 4;
    x = 5;
    printf("D: %d\n", (ux-uy) == -(unsigned)(y-x));

    /*
      number -->>2--> floor(number/4)
      number --<<4--> number*4

      So the first two bits are always lost. And that means for negative and postive
      two's complement number that the number either equals or is less than before.
     */
    printf("E: %d\n", ((x >> 2) << 2) <= x);
    return 0;

    /* 2.81 */
    printf("%x\n", bit_pattern_A(16));
    printf("%x\n", bit_pattern_B(8, 8));
    return 0;
}
