#include <stdio.h>

void remdiv(long x, long y, long *qp, long *rp) {
    long q = x/y;
    long r = x%y;
    *qp = q;
    *rp = r;
}

int main() {
    remdiv(0,0,0,0);
}
