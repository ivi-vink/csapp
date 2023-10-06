#include <stdio.h>
#include <limits.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, size_t len) {
    int i;
    for (i = 0; i < len; i++) {
        printf(" %.2x", start[i]);
    }
    printf("\n");
}

void show_int(int x) {
    show_bytes((byte_pointer) &x, sizeof(int));
}

void show_float(float x) {
    show_bytes((byte_pointer) &x, sizeof(float));
}

void show_pointer(void *x) {
    show_bytes((byte_pointer) &x, sizeof(void *));
}

void test_show_bytes(int val) {
    int ival = val;
    float fval = (float) val;
    int *pval = &ival;
    show_int(ival);
    show_float(fval);
    show_pointer(pval);
}

int is_little_endian() {
    int val = 1;
    byte_pointer pval = (byte_pointer) &val;
    return *pval == 1;
}

unsigned int combine_least_significant_with_remaining(unsigned int x, unsigned int y) {
    return (x & 0xFF) | (y & ~0xFF);
}

unsigned replace_byte(unsigned x, int i, unsigned char b) {
    unsigned remover = ~(0xFF<<(i<<3));
    unsigned adder = b<<(i<<3);
    return (x & remover | adder);
}

int bit_any_one(int x, int mask, int rshift) {
    return (((x >> rshift) & ~0) & mask) && 1 || 0;
}

int bit_any_zero(int x, int mask, int rshift) {
    return (((x >> rshift) ^ ~0) & mask) && 1 || 0;
}

int int_shifts_are_arithmetic() {
    int ones_or_zeroes = ~0;
    int rshifted = ones_or_zeroes >> 1;
    return (rshifted >> (sizeof(int) - 1)) & 1;
}

const int w = sizeof(int)*8;
unsigned srl(unsigned x, int k) {
    /* Perform shift arithmetically */
    unsigned xsra = (int) x >> k;
    unsigned ones_or_zeroes = ~0;
    unsigned shiftl_minus_one = ones_or_zeroes<<(w-1 - k);
    unsigned shiftl = shiftl_minus_one + shiftl_minus_one;
    unsigned mask = ~shiftl;
    printf("value: ");
    show_int(x);
    printf("mask: ");
    show_int(mask);
    return xsra & mask;
}

int sra(int x, int k) {
    /* Perform shift logically */
    int xsrl = (unsigned) x >> k;
    int has_msb = ((1<<(w - 1)) & x) && 1;
    unsigned ones_or_zeroes = (!has_msb) - 1;
    unsigned shiftl_minus_one = ones_or_zeroes<<(w-1 - k);
    unsigned shiftl = shiftl_minus_one + shiftl_minus_one;
    unsigned mask = shiftl;
    printf("value: ");
    show_int(x);
    printf("mask: ");
    show_int(mask);
    return xsrl | mask;
}

void test_srl() {
    printf("===== SRL\n");
    printf("zero shifts, INT_MIN, -1, 0, INT_MAX\n");
    show_int(srl(INT_MIN, 0));
    show_int(srl(-1, 0));
    show_int(srl(0, 0));
    show_int(srl(INT_MAX, 0));
    printf("16 bit shift, INT_MIN, -1, 0, INT_MAX\n");
    show_int(srl(INT_MIN, 16));
    show_int(srl(-1, 16));
    show_int(srl(0, 16));
    show_int(srl(INT_MAX, 16));
}

void test_sra() {
    printf("===== SRA\n");
    printf("zero shifts, INT_MIN, -1, 0, INT_MAX\n");
    show_int(sra(INT_MIN, 0));
    show_int(sra(-1, 0));
    show_int(sra(0, 0));
    show_int(sra(INT_MAX, 0));
    printf("16 bit shift, INT_MIN, -1, 0, INT_MAX\n");
    show_int(sra(INT_MIN, 16));
    show_int(sra(-1, 16));
    show_int(sra(0, 16));
    show_int(sra(INT_MAX, 16));
}

int any_odd_one(unsigned x) {
    return (x & 0xAAAAAAAA) && 1;
}

int odd_ones(unsigned x) {
    /*
      I cheated by looking at other people's answers online for this one after a couple of hours.
      I somehow got stuck on the idea that I should use the previous excercise's mask for odd numbers (Guess I was tired kappa).

      The solution is kind of clever (But requires some C experience imo). It uses the fact that XOR is zero if you have two ones.
      And it kind of subtracts those two ones from the total ones until you have either 0 or 1 left.

      It is done by recursively taking two halves and crossing off or keeping ones in the halves.
      Until the halve is just a 1-bitvector containing the parity bit.
     */
    x ^= x>>16;
    x ^= x>>8;
    x ^= x>>4;
    x ^= x>>2;
    x ^= x>>1;
    return x & 0x01;
}

int main() {
    printf("odd_ones: %d\n", odd_ones(0b11));

    // 64
    printf("any_odd_one: %d\n", any_odd_one(5));
    return 0;

    // 63
    printf("================ 63 ================\n");
    test_srl();
    test_sra();
    return 0;
    // 62
    printf("================ 62 ================\n");
    printf("%d\n", int_shifts_are_arithmetic());

    // 61
    printf("================ 61 ================\n");
    int shift = (sizeof(int) - 1) << 3;
    printf("%d\n", bit_any_one(INT_MIN, 0xFF, shift));
    printf("%d\n", bit_any_one(256, 0xFF, 0));
    printf("%d\n", bit_any_one(1, 0xFF, 0));
    printf("%d\n", bit_any_zero(-1, 0xFF, 0));

    // 60
    printf("================ 60 ================\n");
    printf("%x\n", replace_byte(0x12345678, 2, 0xAB));
    printf("%x\n", replace_byte(0x12345678, 0, 0xAB));

    // 59
    unsigned int combined = combine_least_significant_with_remaining(0x89ABCDEF, 0x76543210);
    show_bytes((byte_pointer) &combined, sizeof(unsigned int));

    // 58
    show_int(1);
    printf("is little endian: %d\n", is_little_endian());

    return 0;
    // 55-57
    test_show_bytes(13);
}
