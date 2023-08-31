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

int main() {
    int A = -1;
    int w = sizeof(int)<<3;
    int k = 0;
    int shifted_off_by_one = (A<<(w-k - 1));
    int shifted = shifted_off_by_one + shifted_off_by_one;
    printf("w: %d, k: %d, A<<(w-k): %d\n", w, k, shifted);
    show_int(shifted);

    printf("%d\n", ((1<<(w - 1)) & INT_MAX) && 1);

}
