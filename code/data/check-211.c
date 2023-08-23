#include <stdio.h>

void inplace_swap(int *x, int *y) {
    *y = *x ^ *y;
    *x = *x ^ *y;
    *y = *x ^ *y;
}

void reverse_array(int a[], int cnt) {
    int first, last;
    for (first = 0, last = cnt-1;
         first < last;
         first++,last--)
        inplace_swap(&a[first], &a[last]);
}

void print_array(int a[], int len) {
    int i;
    for (i = 0; i < len; i++)
        printf("%d", a[i]);
}

void main() {
    int a[] = {1,2,3,4,5, 6};
    reverse_array(a, 6);
    print_array(a, 6);
}
