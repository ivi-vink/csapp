#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <math.h>
#include "../code/data/show-bytes.c"


float my_u2f(unsigned int my_u) {
    assert(sizeof(unsigned int) == sizeof(float));
    union {
        unsigned int u;
        float f;
    } my_union;
    /* Apparently you cannot print the bytes of a float directly? like this printf("%x\n", f); */
    my_union.u = my_u;
    return my_union.f;
}

float fpwr2(int x)
{
    /* Result exponent and fraction */
    unsigned exp, frac;
    unsigned u;

    int k = 8;
    int n = 23;

    int bias = (1<<(k-1))-1;
    int max_e = ((1<<k) - 2) - bias;

    if (x < 1-bias-n) {
        /*  Too small. Return 0.0 */
        exp = 0;
        frac = 0;
    } else if (x < 1-bias) {
        /* Denormalized, [(1-bias-n), (1-bias)]  [-139, -126] */
        exp = 0;
        frac = 1<<(x+1-bias-n);
    } else if (x<=max_e) {
        /* Normalized */
        exp = x+bias;
        frac = 0;
    } else {
        /* Too big. Return +oo */
        exp = (1<<8)-1;
        frac = 0;
    }

    /* Pack exp and frac into 32 bits */
    u = (exp << 23) | frac;
    /* Return as float */
    return my_u2f(u);
}


int main(void) {

    /* 2.90 */
    printf("%f\n", fpwr2(-1));  /* 65536 */
    printf("%f\n", fpwr2(16));  /* 65536 */
    printf("%f\n", fpwr2(15));  /* 32768 */
    printf("%f\n", fpwr2(14));  /* 16384 */
    printf("%f\n", fpwr2(13));  /* 8192 */
    printf("%f\n", fpwr2(12));  /* 4096 */
    printf("%f\n", fpwr2(11));  /* 2048 */
    printf("%f\n", fpwr2(10));  /* 1024 */
    printf("%f\n", fpwr2(128));
    return 0;

    /* 2.91 */
    printf("%x\n", 0b01000000010010010000111111011011);
    /*
      0 10000000 10010010000111111011011
      E = 128-127 = 1
      M = 1 + f
      f = (2^22+2^19+2^16+2^11+2^10+2^9+2^8+2^7+2^6+2^4+2^3+2^1+2^0)/2^23
      V = (2^E)(M)

      13176795/4194304

      22/7 = 2(1+f)
      11/7 = (1+f)
      4/7 = f

      n = 0.yyy = f
      n = Y/((1<<k) - 1)
      n = 4/((1<<3) - 1)
      0 10000000 [100]+
    */
    show_float(22.0f/7.0f);
    printf("%b\n", 0x40492492);
    /* so we have 22/7
       0 10000000 10010010010010010010010
       and the approx
       0 10000000 10010010000111111011011
       at the 9th position the values diverge
     */
    return 0;

    /* 2.90 */
    printf("%f\n", fpwr2(-1));  /* 65536 */
    printf("%f\n", fpwr2(16));  /* 65536 */
    printf("%f\n", fpwr2(15));  /* 32768 */
    printf("%f\n", fpwr2(14));  /* 16384 */
    printf("%f\n", fpwr2(13));  /* 8192 */
    printf("%f\n", fpwr2(12));  /* 4096 */
    printf("%f\n", fpwr2(11));  /* 2048 */
    printf("%f\n", fpwr2(10));  /* 1024 */
    printf("%f\n", fpwr2(128));
    return 0;
}
