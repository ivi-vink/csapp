#define EXPR

double simplefun(double x) {
    return EXPR(x);
}
// A
// vmovsd       .LC1(%rip), %xmm1
// vandpd       %xmm1, xmm0, xmm0
// .LC1:
// 1111111111111111111111111111111111111111111111111111 11111111111 0
//
// Checks if any bit is set in the arg by anding with all ones
//
//
// B
// vxorpd      %xmm0, %xmm0, %xmm0
//
// Sets the argument to zero
//
// C
// vmovsd       .LC2(%rip), %xmm1
// vxorpd       xmm1, %xmm0, %xmm0
// 10000000000000000000000000000000 00000000000000000000000000000000
//
// Flipping the sign bit
