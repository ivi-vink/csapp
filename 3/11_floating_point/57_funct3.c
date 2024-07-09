double funct3(int *ap, double b, long c, float *dp) {
    int a = *ap;
    float d = *dp;
    if (b <= a) {
        return (c * d);
    }
    return (c + 2 * d);
}

// ap in rdi, b in xmm0, c in rsi, dp in rdx
// funct3:
//   vmovss         (%rdx), %xmm1               // y <- dp
//   vcvtsi2sd      (%rdi), %xmm2, %xmm2        // z <- (double a)
//   vucomisd       %xmm2, %xmm0                // compare:  (<=  b z  )
//   jbe            .L8                         // jump to .L8: if <
//   vcvtsi2ssq     %rsi, %xmm0, %xmm0          // x <- (float) c
//   vmulss         %xmm1, %xmm0, %xmm1         // y <- (* x y)
//   vunpcklps      %xmm1, %xmm1, %xmm1         // float->double
//   vcvtps2pd      %xmm1, %xmm0                // float->double
//   ret
// .L8:
//   vaddss         %xmm1, %xmm1, %xmm1         // y <- (+ y y )
//   vcvtsi2ssq     %rsi, %xmm0, %xmm0          // x <- (float c)
//   vaddss         %xmm1, %xmm0, %xmm0         // x <- x + y
//   vunpcklps      %xmm0, %xmm0, %xmm0         // float->double
//   vcvtps2pd      %xmm0, %xmm0                // float->double
//   ret
