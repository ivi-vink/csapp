#include <stdio.h>

#define POS_INFINITY 1.8e400
#define NEG_INFINITY -POS_INFINITY
#define NEG_ZERO (-1.0/POS_INFINITY)

int main() {
    /*
      2.53
    */
    printf("%f\n", POS_INFINITY);
    printf("%f\n", NEG_INFINITY);
    printf("%f\n", NEG_ZERO);

    /*
      2.54
      A. Yes, int->double->int, int->double preserves value, so double->int after that also has the same value, since we know rounding and overflow is not relevant.
      B. NO, same as A, actually Fmax < Tmax, so casting from int to float can overflow.
      C. No, double->float->double, float has lower range, so overflow could happen. Float also has lower precision, so when converting to float there may also be round-to-even.
      D. Yes, float->double->float, exact value can be kept when casting to double.
      E. Yes, Sign bit can be flipped without influencing the rest of the bit pattern. So the double negation cancels itself and the value is exactly the same after.
      F. Yes, 1.0/2 == 1/2.0, integers are first cast to float.
      G. Yes, d*d >= 0.0, this is a result of the monotonicity property of floating point numbers.
      H. (f+d)-f == d, in the addition rounding errors can occur, for example when adding a small value to a large value. It can also overflow, causing (inf-f) = inf.
      In this comparison the problem arises when the value that is compared is the small one, since that will get lost in the rounding error of the addition.
    */
    int x = (1<<31) - 1;
    float f = 3.14f;
    double d = 1e307f;
    printf("%d\n", x == (int) (double) x);
    printf("%d\n", x == (int) (float) x);
    printf("%d, value: %f\n", d == (double) (float) d, (double) (float) d);
    printf("%d, value: %f, orig: %f\n", f == (float) (double) f, (float) (double) f, f);
    printf("%d\n", f == -(-f));
    printf("%d\n", 1.0/2 == 1/2.0);
    printf("%d\n", d * d >= 0.0);
    printf("%d\n", (f+d)-f == d);
    return 0;
}
