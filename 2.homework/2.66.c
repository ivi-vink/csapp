#include <stdio.h>

typedef unsigned char *byte_pointer;

int is_little_endian() {
    int val = 1;
    byte_pointer pval = (byte_pointer) &val;
    return *pval == 1;
}

/*
  Generate mask indicating leftmost 1 in x. Assume w=32
  For example, 0xFF00 -> 0x8000, and 0x6600 --> 0x4000

  |, &, ^, >>, <<
  +, -
  &&, ||

  0110 0110 0000 0000
  ....
  0110 0110 0110 0110
  |
  0000 0110 0110 0110
  |
  0001 1001 1001 1001
  =
  0111 1111 1111 1111
  ~
  1000 0000 0000 0000
  >>1
  0100 0000 0000 0000

  0001 0000 0000 0000
  |>>8
  0001 0000 0001 0000
  |>>4
  0001 0001 0001 0001
  |>>2
  0001 0101 0101 0101
  |>>1
  0001 1111 1111 1111

 */
int leftmost_one(unsigned x) {
    x |= x>>16;
    x |= x>>8;
    x |= x>>4;
    x |= x>>2;
    x |= x>>1;
    return x & ~(x>>1);
}

int bad_int_size_is_32() {
    /* Set most significant bit (msb) of 32-bit machine */
    int set_msb = 1 << 15;
    set_msb = set_msb << 15;
    set_msb = set_msb << 1;

    /* Shift past msb of 32-bit word ?? A. undefined behavior if you shift more than the data type*/
    int beyond_msb = set_msb + set_msb; /* should overflow to zero if on 32 bit machine */

    /*
      set_msb is nonzero when word size >= 32
      beyond_msb is zero when word size <= 32
     */
    return set_msb && !beyond_msb;
}

/*
  Mask with least significant n bits set to 1
  Examples: n = 6 --> 0x3F, n = 17 --> 0x1FFFF
  Assume 1 <= n <= w
 */
int lower_one_mask(int n) {
    return ((unsigned) ~0)>>(32-n);
}

/*
  Do a rotating left shift. Assume 0 <= n < w
  Examples when x = 0x12345678 and w = 32:
      n=4 -> 0x23456781, n=20 -> 0x67812345
 */
unsigned rotate_left(unsigned x, int n) {
    unsigned left_part = x<<n;
    unsigned right_part = x>>(31-n)>>1;
    return left_part | right_part;
}

/*
  Return 1 when x can be represented as an n-bit, 2's-complement
  number; 0 otherwise
  Assume 1 <= n <= w

  Two's complement
  TMAX = 2^(w-1) - 1
  TMIN = 2^(w-1)

  All bits are less than the nth bit.
  Negative x should have their sign bit set.

  Check by truncating via shifting.
  This takes care of the positive and negative cases with logical or arithmetic shift back.

  I also assumed w = 32
 */
int fits_bits(int x, int n) {
    return x == (x<<(32-n))>>(32-n);
}

int main() {
    printf("fits_bits: %x\n", fits_bits(7, 4));
    printf("fits_bits: %x\n", fits_bits(8, 4));
    return 0;

    printf("rotate_left: %x\n", rotate_left(0x12345678, 0));
    printf("rotate_left: %x\n", rotate_left(0x12345678, 4));
    printf("rotate_left: %x\n", rotate_left(0x12345678, 20));
    return 0;

    printf("lower_one_mask: %x\n", lower_one_mask(6));
    printf("lower_one_mask: %x\n", lower_one_mask(17));
    return 0;

    printf("int_size_is_32: %d\n", bad_int_size_is_32());
    return 0;

    printf("is little endian: %d\n", is_little_endian());
    printf("%d\n", 0xFF00);
    printf("%x\n", leftmost_one(0xFF00));
    printf("%x\n", leftmost_one(0x6600));
    printf("%x\n", leftmost_one(0));

    return 0;
}
