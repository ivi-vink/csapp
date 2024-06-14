#include <stdio.h>
double fcvt(int i, float *fp, double *dp, long *lp) {
    float f = *fp; double d = *dp; long l = *lp;
    *lp = (long)    d; // double->long
    *fp = (float)   i; // int->float
    *dp = (double)  l; // long->double
    return (double) f; // float->double
}

int main(void) {
    float f = 0.5f; double d = 1.0; long l = 1;

    float *fp = &f; double *dp = &d; long *lp = &l;

    fcvt(42, fp, dp, lp);
    return 0;
}
