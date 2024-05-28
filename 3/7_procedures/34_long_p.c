// long P(long x)
// x in %rdi
// bx and bp, r12-15 are callee saved
//
//  P:
//      pushq %r15
//      pushq %r14
//      pushq %r13
//      pushq %r12
//      pushq %rbp
//      pushq %rbx
//      subq $24, %rsp      Allocate 24 extra bytes
//
//      movq %rdi, %rbx     move first arg into rbx
//      leaq 1(%rdi), %r15     move first arg into rbx
//      leaq 2(%rdi), %r14     move first arg into rbx
//      leaq 3(%rdi), %r13     move first arg into rbx
//      leaq 4(%rdi), %r12     move first arg into rbx
//      leaq 5(%rdi), %rbp     move first arg into rbx
//      leaq 6(%rdi), %rax     move first arg into rbx
//      movq %rax, (%rsp)      save %rax in one of the three 8byte spots
//      leaq 7(%rdi), %rdx     move first arg into rdx
//      movq %rdx, 8(%rsp)     save %rdx in the second of the three 8byte spots
//      movl $0, %eax          set ax to zero?
//      call Q
//      ...
//
// A. x, x + 1, x + 2, x + 3, x + 4, x + 5
// B. x + 6, x + 7
// C. There were more than 6?
//
long P(long x) {
    return 0;
}
