#include <stdio.h>

// Remember that jumps flip conditionals
// Also testq rdi rdi and jge test if the sign bit is set
short test(short x, short y) {
    short val = 12 + y;
    if (x < 0) {
        if (x >= y)
            val = x | y;
        else
            val = x * y;
    } else if (y >= 10) {
        val = x / y;
    }
    return val;
}

int main(void) {
    return 0;
}
