short dw_loop(short x)
{
    short y = x/9;
    short *p = &x;
    short n = 4*x;
    do {
        x += y;
        (*p) += 5;
        n += 2;
    } while (n > 0);
    return x;
}

// x in %rdi
// dw_loop:
//    movq %rdi, %rdx           # %rbx <- x
//    movq %rdi, %rcx           # %rcx <- x
//    idivq $9, %rcx            # %rcx (y) <- x / 9
//    leaq (,%rdi,4), %rdx      # %rdx (n) <- x * 4
// .L2:
//    leaq 5(%rbx,%rcx), %rcx   # %rbx (x) <- 5 + %rbx (x) + %rcx (y)
//    subq $1, %rdx             # %rdx (n) <- n - 1
//    testq %rdx, %rdx          # n > 0 ?
//    jg .L2                    # if n > 0, goto .L2
//    rep; ret
//
//    A. x in rbx, y in rcx, n in rdx
//    B. The pointer is never used besides incrementing the value at the address. So it is replaced by a incrementing instruction in the loop.
