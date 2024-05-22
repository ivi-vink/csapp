#include <stdio.h>

int main() {
    if (0 && 1) {
        printf("hi");
    }
    printf("%d\n", (0 && 1) || 0);
}
