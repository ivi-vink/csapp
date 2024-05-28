#include <stdio.h>

//  x in rdi
//  fun_b:
//      movl    $64, %edx   i <- 64  (32 bits?, long presumably)
//      movl    $0, %eax    val <- 0
//  .L10:
//      movq    %rdi, %rcx  tmp <- x
//      andl    $1, %ecx    tmp <- tmp & 1
//      addq    %rax, %rax  val <- val + val
//      orq     %rcx, %rax  val <- val | tmp
//      shrq    %rdi
//      subq    $1, %rdx    i <- i-1
//      jne     .L10        if i != 0 then goto .L10
//      rep; ret
long fun_b(unsigned long x) {
    long val = 0;
    long i;
    for (i = 64; i!=0; i--) {
        long tmp = x;
        tmp &= 1; // check 1 bit
        val += val; // multiply by two
        val |= tmp; // add 1 bit if present
        x >>= 1;    // shift next bit into 1 bit
    }
    return val;
}

// Seems to compute the value shifted to the left (63 - nbit), (or in other words the mirror image)
int main() {
    printf("val: %ld, computed: %ld, bits: %lb\n", fun_b(10), (long) 10 << 59, 10);
    return 0;
}
