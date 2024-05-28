#include <stdio.h>

// a in %rdi, b in %rsi, c in %rdx, dest in %rcx
void switcher(long a, long b, long c, long *dest) {
    long val;
    switch (a) {
        case 5: /* Case A .L7 */
            c = 15 ^ a;
            /* Fall through */
        case 0: /* Case B .L3 */
            val = 112 + c;
            break;
        case 2: /* Case C .L5 */
        case 7: /* Case D .L5 */
            val = (c + b)<<2;
            break;
        case 4: /* Case E */
            val = a;
            break;
        default: /* .L2 */
            val = b;
    }
    *dest = val; /* .L6 */
}

int main(void) {
    printf("val: %ld\n");
    return 0;
}
