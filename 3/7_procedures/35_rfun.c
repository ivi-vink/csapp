// x in %rdi
// rfun:
//      pushq %rbx          save rbx, since we use it and in case we are called
//      movq %rdi, %rbx     %rbx <- x
//      movl $0             %rax <- 0
//      testq %rdi, %rdi    ZF <- %rdi == 0
//      je .L2              jump to if ZF
//      shrq $2, %rdi       shift x to the lift by 2 bits (divide by four)
//      call rfun
//      addq %rbx, %rax     add our calculation to the rest
//  .L2
//      popq %rbx           set rbx back to the value of our caller's calculation
//      ret
//
//  A>
//      The value x is stored in rbx, and each iteration stores (int64_t) x/4
//  B>
long rfun(unsigned long x) {
    if (x == 0) {
        return 0;
    }
    unsigned long nx = x>>2;
    long rv = rfun(nx);
    return x + rv;
}
