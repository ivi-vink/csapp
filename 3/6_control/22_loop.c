#include <limits.h>
#include <stdint.h>
#include <stdio.h>
// do
//    body
//    while (test);
//
// loop:
//   body
//   t = test;
//   if (t)
//      goto loop;

typedef int64_t fact_t;

long fact_do(long n)
{
    long result = 1;
    do {
        result *= n;
        n = n-1;
    } while (n > 1);
    return result;
}

int tmult_ok(fact_t x, fact_t y)
{
    fact_t p = x*y;
    return !x || p/x == y;
}

fact_t fact_do_int(size_t n)
{
    fact_t result = 1;
    do {
        if (tmult_ok(result, n)) {
            result *= n;
            n = n-1;
        } else {
            printf("would overflow this iter, n=%ld\n", n);
            n = 0;
        }
    } while (n > 1);
    return result;
}

int main(void) {
    size_t f = 20;
    printf("result: %ld, max: %ld, less: %d", fact_do_int(f), INT64_MAX, fact_do_int(f) < INT64_MAX);
    return 0;
}
