#include <stdio.h>

/*
 * x in %rdi, y in %rsi, z in %rdx
 * arith3:
 *   orq %rsi, %rdx
 *   sarq $9, %rdx
 *   notq %rdx
 *   movq %rdx, %bax <------- what is this register??
 *   subq %rsi, %rbx
 *   ret
 */
short arith3(short x, short y, short z) {
    short p1 = z | y;
    short p2 = p1>>9;
    short p3 = ~p2;
    short p4 = p3;
    return p4;
}

int main() {

}
