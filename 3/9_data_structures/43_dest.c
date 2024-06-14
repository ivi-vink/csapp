#define type long;

typedef union {
    struct {
        long    u;
        short   v;
        char    w;
    } t1;
    struct {
        int     a[2];
        char    *p;
    } t2;
} u_type;

// Kinda confused when I'm moving a memory address
// Forgot it was a union
// Also forgot I had to move to dest
//
// up and dest in rdi and rsi
//
// expr                 type            code
//
// up->t1.u             long            movq (%rdi), %rax
//                                      movq %rax, (%rsi)
//
// up->t1.v             short           movw 8(%rdi), %ax
//                                      movw %ax, (%rsi)
//
// &up->t1.w            char*           addq 10, %rdi
//                                      movq %rdi, (%rsi)
//
// up->t2.a             int *           movq %rdi, (%rsi)
//
// up->t2.a[up->t1.u]   int             movq (%rdi), %rax               // What's interesting: rdi is the t2.a int* and the t1.u long, and they are being used in the same expression!
//                                      movl (%rdi, %rax, 4), %eax
//                                      movl %eax, (%rsi)
//
// *up->t2.p            char            movq 8(%rdi), %rax
//                                      movb (%rax), %al                // Remember, you cannot have Memory -- Memory moves!
//                                      movb %al, (%rsi)
void get(u_type *up, type *dest) {
    *dest = ___;
}
