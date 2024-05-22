#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include <stdint.h>

/*
  Addition that saturates to TMIN or TMAX
  2^(w-2) + 2^(w-2)
  w=4
  0100
  0100
  +
  1000 (-8)
  Normally overflow wraps around to the other extreme.
  z mod 2w
  and do unsigned addition

  positive overflow -> TMAX
  negative overflow -> TMIN

  for w=4
  1000
  1000
  +
  1000

  0100
  0100
  +
  0111

  z +

  note: you can apparently also do something like

  thing_is_true && (x = my_value)

  in c :/.
  Now I did it with a weird method using masks based on booleans.
*/
int saturating_add(int x, int y) {
    int sum = x + y;
    printf("sum: %x\n", sum);
    int min = INT_MIN;
    int did_negative_overflow = ((min & x) && (min & y) && !(min & sum)) - 1;
    int did_positive_overflow = (!(min & x) && !(min & y) && (min & sum)) - 1;
    sum |= INT_MIN & ~did_negative_overflow;
    sum &= INT_MIN | did_negative_overflow;
    sum |= INT_MAX & ~did_positive_overflow;
    sum &= INT_MAX | did_positive_overflow;
    return sum;
}

/*
  Determine whether arguments can be subtracted without overflow.
  important to note is that the positive range of integers is shorter than the negative.

  positive [0, 2^{w-1} - 1]
  negative [-2^{w-1}, 0]
*/
int tsub_ok(int x, int y) {
    if (y == INT_MIN) {
        return 0;
    }
    int positive_overflow = x > 0 && y < 0 && x - y < 0;
    int negative_overflow = x < 0 && y > 0 && x - y >= 0;
    return !positive_overflow && !negative_overflow;
}

/*
  The result of 2.18 shows us
  T2B(x*y) <=> U2B(x'*y')
  but this is only for w bits.
  In this case we are looking at the 2w bits.


 */
int signed_high_prod(int x, int y) {
    int64_t result = (int64_t) x * y;
    return result >> 32;
}
unsigned correct_unsigned_high_prod(unsigned x, unsigned y) {
    uint64_t result = (uint64_t) x * y;
    return result >> 32;
}
unsigned unsigned_high_prod(unsigned x, unsigned y) {
    unsigned xl = x>>31;
    unsigned yl = y>>31;
    return signed_high_prod(x, y) + xl*y + yl*x;
}

int main() {
    /* assert(unsigned_high_prod(0xFFFFFFFF, 3) == correct_unsigned_high_prod(0xFFFFFFFF, 3)); */
    unsigned x = 0x12345678;
    unsigned y = 0xFFFFFFFF;

    assert(correct_unsigned_high_prod(x, y) == unsigned_high_prod(x, y));
    return 0;

    printf("%d\n", tsub_ok(1, INT_MIN>>1));
    printf("%d\n", tsub_ok(1, (INT_MIN>>1) - 1));
    printf("%d\n", tsub_ok(1, INT_MIN));
    printf("%d\n", tsub_ok(INT_MIN, INT_MAX));
    printf("%d\n", -((INT_MIN>>1) - 1));
    printf("%d\n", INT_MAX);
    return 0;

    printf("%x\n", INT_MIN);
    printf("%x\n", saturating_add(INT_MIN, INT_MIN));
    printf("%x\n", saturating_add(4, 4));
    printf("%x\n", saturating_add(-3, 4));
    return 0;
}
