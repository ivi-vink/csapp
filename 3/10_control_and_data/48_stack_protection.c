int len(char *s) {
    return strlen(s);
}

void iptoa(char *s, long *p) {
    long val = *p;
    sprintf(s, "%ld", val);
}

// int inlen(long x)
// x in %rdi
// without canary
//
// intlen:
//      subq        $40, %rsp           allocate 5*8 bytes
//      movq        %rdi, 24(%rsp)      put x on the stack
//      leaq        24(%rsp), %rsi      set &v = &x to the second argument
//      movq        %rsp, %rdi          set buf[12] to %rsp
//      call        iptoa
//
//  0<rsp+32    <-?
//  0<rsp+24    <-v
//  0<rsp+16    <-?
//  0<rsp+8     <-buf[12]
//  0<rsp       <-buf[12]
//
// with canary
//
// intlen:
//      subq        $56, %rsp
//      movq        %fs:40, %rax
//      movq        %rax, 40(%rsp)
//      xorl        %eax, %eax
//      movq        %rdi, 8(%rsp)
//      leaq        8(%rsp), %rsi
//      leaq        16(%rsp), %rdi
//      call        iptoa
//
//  0<rsp+48    <-
//  0<rsp+40    <-canary
//  0<rsp+32    <-
//  0<rsp+24    <-
//  0<rsp+16    <-buf[12]
//  0<rsp+8     <-v
//  0<rsp       <-
int intlen(long x) {
    long v;
    char buf[12];
    v = x;
    iptoa(buf, &v);
    return len(buf);
}
