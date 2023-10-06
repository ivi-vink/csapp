#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <math.h>
#include "../code/data/show-bytes.c"

typedef unsigned float_bits;

#define M ~0

unsigned i2u(int i) {
    union {
        unsigned u;
        int i;
    } ui;
    ui.i = i;
    return ui.u;
}

float u2f(unsigned int my_u) {
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
    return u2f(u);
}

/*
  int and unsigned and their operations are allowed.
 */
float_bits float_denorm_zero(float_bits f) {
    unsigned sign = f>>31;
    unsigned exp =  f>>23 & 0xFF;
    unsigned frac = f     & 0x7FFFFF;
    if (exp == 0) {
        frac = 0;
    }
    return (sign << 31) | (exp << 23) | frac;
}

float_bits float_negate(float_bits f) {
    unsigned is_valid_exp =  (f>>23) ^ 0xFF;
    unsigned frac = f     & 0x7FFFFF;
    if (!is_valid_exp && frac) return f;
    return (1<<31) ^ f;
}

float_bits float_absval(float_bits f) {
    unsigned is_valid_exp =  (f>>23) ^ 0xFF;
    unsigned frac = f     & 0x7FFFFF;
    if (!is_valid_exp && frac) return f;
    return ~(1<<31) & f;
}

float_bits float_twice(float_bits f) {
    /*
     */
    unsigned sign = f>>31;
    unsigned exp = (f>>23) & 0xFF;
    unsigned frac = f     & 0x7FFFFF;
    unsigned is_valid_exp =  exp ^ 0xFF;
    if (!is_valid_exp) return f;

    if (!exp) {
        /*
          Denormalized because we have a zero exponent
          f<<1
         */
        return (sign<<31) | (frac<<1);
    } else {
        /*
          Normalized value.
          = (2^k(1+f))*2
          = 2^(k+1)(1+f)
         */
        unsigned twice_exp = exp + 1;
        if (twice_exp == 0xFF) {
            frac = 0;
        }
        return (sign<<31) | (twice_exp<<23) | frac;
    }
}

float_bits float_half(float_bits f) {
    unsigned sign = f>>31;
    unsigned exp = (f>>23) & 0xFF;
    unsigned frac = f     & 0x7FFFFF;
    unsigned is_valid_exp =  exp ^ 0xFF;
    if (!is_valid_exp) return f;

    if (!exp) {
        /*
          Denormalized because we have a zero exponent
          f>>1
         */
        if (frac&1 && frac^1) {
            /*
              Round to nearest even?
            */
            frac >>= 1;
            frac += frac&1;
        } else {
            frac >>= 1;
        }
        return (sign<<31) | frac;
    } else {
        /*
          Normalized value.
         */
        unsigned half_exp = exp;
        /* Can we halve with exp? */
        if ((half_exp - 1) == 0) {
            /* Is it the value in the middle between norm and denorm? */
            if ((frac ^ 0x7FFFFF) == 0) {
                frac = 0;
            } else {
                /* Otherwise, normally divide the (1+f) by two */
                half_exp -= 1;
                if (frac&1 && frac^1) {
                    frac >>= 1;
                    frac += frac&1;
                } else {
                    frac >>= 1;
                }
                frac |= 1<<22;
            }
        } else {
            half_exp -= 1;
        }
        return (sign<<31) | (half_exp<<23) | frac;
    }
}

/*
  Compute (int) f.
  If conversion causes overflow or f is NaN, return 0x80 00 00 00
 */
int float_f2i(float_bits f) {
    int invalid = 0x80000000;
    unsigned sign = f>>31;
    unsigned exp = (f>>23) & 0xFF;
    unsigned frac = f     & 0x7FFFFF;
    unsigned is_valid_exp =  exp ^ 0xFF;
    if (!is_valid_exp) return invalid;

    unsigned bias = (1<<7) - 1;
    if (exp < bias) return 0;
    exp -= bias;
    /*
      Smallest odd that cannot be represented exactly
      2^(n+1) + 1
    */
    if (exp < 24) {
        int result = (1<<exp) + (frac>>(23 - exp));
        if (sign) {
            result = ~result + 1;
        }
        return result;
    }
    if (exp < 31) {
        int result = (1<<exp) + (frac<<(exp - 23));
        if (sign) {
            result = ~result + 1;
        }
        return result;
    }
    return invalid;
}

float_bits float_i2f(int i) {
    if (i==0) return 0;
    /*
      Need to calculate exp and frac based on integer, so we will take apart the integer into exp and frac using the fundamenal property of division.
      p = q + r, where q and r are integers and q is the result of integer division of p
     */
    unsigned sign = i>>31;
    int exp, frac, k, n, bias;

    k = 8;
    n = 23;
    bias = (1<<(k-1))-1;
    exp = bias;
    frac = 0;

    if (i==INT_MIN) {
        /* Special case since ~i+1=i, if i=INT_MIN */
        return (sign<<31) | ((exp+31)<<23) | 0;
    }

    /* Get the greatest power of 2, p2 and remainder */
    int p2, rem;
    int u = (i & ~sign) | ((~i + 1) & sign);
    int u_orig = u;
    int b16, b8, b4, b2, b1, b0;

    b16 = (!!(u>>16))<<4;
    u >>= b16;
    b8 = (!!(u>>8))<<3;
    u >>= b8;
    b4 = (!!(u>>4))<<2;
    u >>= b4;
    b2 = (!!(u>>2))<<1;
    u >>= b2;
    b1 = (!!(u>>1));

    p2 = b16 + b8 + b4 + b2 + b1;
    exp += p2;
    rem = u_orig - (1<<p2);

    /* How much greater than precision are we */
    int prec = (p2-23);
    int prec2 = (1<<prec);

    if (rem == 0) {
        frac = 0;
    } else {
        if (p2 > 23) {
            /* Outside of float32 precision */

            /* Special case, Is remainder greater than half precision removed from highest power? */
            if ((1<<p2) - (prec2>>1) <= rem) {
                /* Round up into next power level */
                frac = 0;
                exp += 1;
            } else {
                /* Encode remainder as fraction with prec denom */
                frac = rem>>prec;
                if (prec>1) {
                    /* Rounding is non binary, need to check if round to even applies or round up */
                    int r = rem%prec2;
                    if (r > (prec2>>1)) {
                        frac += 1;
                    } else if (r==(prec2>>1)) {
                        frac += frac&1;
                    }
                } else {
                    /* Binary rounding is easy, even rem don't need it and odd rem need it if the result is odd */
                    frac += rem&1 && frac&1;
                }
            }
        } else {
            /* Within precision, just encode remainder as fraction with prec denom */
            frac = (rem<<(23-p2));
        }
    }
    return (sign<<31) | (exp<<23) | frac;
    /*
      1 1001 1101 [0]+
      1 1001 1100 [1]+
     */
    /*
      Denormalized
       V = M * 2^E
       M = f < 1-e
       E = 1 - bias
       <=> V < 1

       Normalized
       M = 1 + f
       V = 1 = 2^E *(1+f)    <==>    e>=bias, e=bias <=> V=(2^0)(1+f)
       E = e-bias
       bias=127

       smallest int
       -(2^31)
       biggest int
       (2^31)-1
       1 <> 0 0111 1111 [0]+
       2 <> 0 1000 0000 [0]+
       3 <> 0 1000 0000 1[0]+
       4 <> 0 1000 0001 [0]+
       5 <> 0 1000 0001 01[0]+
       6 <> 0 1000 0001 1[0]+
       7 <> 0 1000 0001 11[0]+
       8 <> 0 1000 0010 000[0]+
       9 <> 0 1000 0010 001[0]+
       10 <> 0 1000 0010 010[0]+
       11 <> 0 1000 0010 011[0]+
     */
    return 1;
}

int main(void) {
    /* 2.97 */
    int j;
    for (j=INT_MIN; j<INT_MAX; j++) {
        float v = u2f(float_i2f(j));
        int result = (((float) j) == v);
            /* show_float((float) j); */
            /* show_float(v); */
        if (!result) {
            printf("want: %f, got: %f\n", ((float) j), v);
            show_float((float) j);
            show_float(v);
        }
        assert(result);
    }
    return 0;

    /* 2.96 */
    unsigned i;
    for (i=0; i<M; i++) {
        int v = float_f2i(i);
        int result = isnan(u2f(i)) || (((int) u2f(i)) == v);
        if (!result) {
            printf("want: %d, got: %d\n", ((int) u2f(i)), v);
            show_float(u2f(i));
        }
        assert(result);
    }
    return 0;

    /* 2.95 */
    for (i=0; i<M; i++) {
        float v = u2f(float_half(i));
        int result = isnan(u2f(i)) || (0.5f*u2f(i) == v);
        if (!result) {
            printf("want: %f, got: %f\n", 0.5f*u2f(i), v);
            show_float(u2f(1));
            show_float(u2f(i));
            show_float(0.5f*u2f(i));
            show_float(v);
        }
        assert(result);
    }
    return 0;

    /* 2.94 */
    for (i=0; i<M; i++) {
        float v = u2f(float_twice(i));
        int result = isnan(u2f(i)) || (2*u2f(i) == v);
        if (!result) {
            printf("want: %f, got: %f\n", 2*u2f(i), v);
            show_float(2*u2f(i));
            show_float(v);
        }
        assert(result);
    }
    return 0;

    /* 2.93 */
    for (i=0; i<M; i++) {
        float v = u2f(float_absval(i));
        int result = isnan(v) || (fabsf(u2f(i)) == v);
        if (!result) {
            printf("%f\n", fabsf(u2f(i)));
        }
        assert(result);
    }
    return 0;

    /* 2.92 */
    for (i=0; i<M; i++) {
        float v = u2f(float_negate(i));
        int result = isnan(v) || (-u2f(i) == v);
        if (!result) {
            printf("%f\n", u2f(i));
        }
        assert(result);
    }
    return 0;
}
