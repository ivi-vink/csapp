#include <stdio.h>

long fact_for(long n) {
    long i;
    long result = 1;
    for (i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

// guarded do
//
// init-s
// t = test-e;
// if (!t) goto done;
//
// loop:
//   body-s
//   update-e;
//   t = test-e;
//   if (t) goto loop;
//
// done:

long fact_for_gd_goto(long n) {
    long i = 2;
    long result = 1;

    int t = i<=n;
    if (!t) {
        goto done;
    }
loop:
    result *= i;
    i++;
    t = i<=n;
    if (t) goto loop;
done:
    return result;
}

int main() {
    printf("for: %ld, goto: %ld\n", fact_for(5), fact_for_gd_goto(5));
    return 0;
}
