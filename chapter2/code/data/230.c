#include <limits.h>
#include <stdio.h>

int tadd_ok(int x, int y) {
    int positive_overflow = x > 0 && y > 0 && x + y < 0;
    int negative_overflow = x < 0 && y < 0 && x + y >= 0;
    return !positive_overflow && !negative_overflow;
}

int tadd_buggy(int x, int y) {
    int sum = x+y;
    printf("sum: %d, sum-x: %d, sum-y: %d", sum, sum-x, sum-y);
    return (sum-x == y) && (sum-y == x);
}

/* buggy */
int tsub_ok(int x, int y) {
    return tadd_ok(x, -y);
}

void main() {
    printf("INT_MIN: %d, %d\n", -(INT_MIN), INT_MIN);
    printf("result:  %d\n", tadd_ok(10, 100));
    printf("result2: %d", tadd_buggy(INT_MAX, 1)); // The sum is a very negative number, when we take the difference with it's parts it just does a negative overflow to get the original parts back.
} 
