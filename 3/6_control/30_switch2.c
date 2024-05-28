#include <stdio.h>

// x in %rdi
// switch2:
//   addq   $1, %rdi
//   cmpq   $8, %rdi
//   ja     .L2     if (x + 1) > 8 then goto default
//   jmp    *.L4(,%rdi,8)   take the address at x*8 from .L4
void switch2(long x, long *dest) {
    long val = 0;
    switch (x) {
        case -1:
            printf(".L9");
            break;
        case 0:
        case 7:
            printf(".L5");
            break;
        case 1:
            printf(".L6");
            break;
        case 2:
        case 4:
            printf(".L7");
            break;
        case 5:
            printf(".L8");
            break;

    }
    *dest = val;
}

int main(void) {
    printf("val: %ld\n");
    return 0;
}
