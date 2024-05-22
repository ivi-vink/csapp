#include <stdio.h>
#include <limits.h>

float sum_elements(float a[], unsigned length) {
    int i;
    float result = 0;
        
    for (i = 0; i <= length-1; i++) {
        printf("iter\n");
        result += a[i];
    }
    return result;
}

void main() {
  printf("hi\n");
  float ele[] = {1.0, 2.0};
  // sum_elements(ele, 0);
  printf("%d", INT_MAX+1);
}
