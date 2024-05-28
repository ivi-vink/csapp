//  procprob
//      movslq  %edi, %rdi      movslq==Move and sign extend 32bit to 64bit two's complement number,
//                                      Basically seems to convert the first signed argument to 64bit size.
//                                      A singed 32bit number is an int?
//      addq    %rdi, (%rdx)    *u <- (long) u + (long) a
//      addb    %sil, (%rcx)    *v <- (char) *v + (?) b
//      movl    $6, %eax        sizeof(a) + sizeof(b) = 6 = 4 + 2
//
//  procprob
//      movslq  %edi, %rdi      movslq==Move and sign extend 32bit to 64bit two's complement number,
//                                      Basically seems to convert the first signed argument to 64bit size.
//                                      A singed 32bit number is an int?
//      addq    %rdi, (%rdx)    *u <- (long) u + (long) a
//      addb    %sil, (%rcx)    *v <- (char) *v + (?) b
//      movl    $6, %eax        sizeof(a) + sizeof(b) = 6 = 2 + 4
//
int procprob(int a, short b, long *u, char *v) {
    *u += a;
    *v += b;
    return sizeof(b) + sizeof(b)
}
