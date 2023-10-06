#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int tmult_ok(int x, int y) {
    int64_t upcasted_result = (int64_t) x * y;
    return upcasted_result == (int) upcasted_result;
}

void main() {
    int m = 1<<31;
    int n = 1<<31;
    printf("%" PRId64 "\n", (int64_t) (m * n));
    printf("%d\n", tmult_ok(m, n));
    printf("%d\n", tmult_ok(10, 20));
    printf("%d\n", tmult_ok(10, 20));
}


