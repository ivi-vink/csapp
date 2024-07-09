typedef arg1_t int;
typedef arg2_t double;
typedef arg3_t double;

typedef arg4_t double;
double funct1(arg1_t p, arg2_t q, arg3_t r, double s)
{
    return p/(q+r) - s;
}
// funct 1:
//      vcvtsi2ssq      %rsi, %xmm2, %xmm2          convert long to double?
//      vaddss          %xmm0, %xmm2, %xmm0         xmm0 <- xmm2 + xmm0 (q+r)
//      vcvtsi2ss       %edi, %xmm2, %xmm2          convert to float (p)
//      vdivss          %xmm0, %xmm2, %xmm0         xmm0 <- xmm2 (p float) / xmm0 (q+r float)
//      vunpcklps       %xmm0, %xmm0, %xmm0         convert float to double?
//      vcvtps2pd       %xmm0, %xmm0                convert float to double?
//      vsubsd          %xmm1, %xmm0, %xmm0         xmm0 <- xmm0 - (double) s?
//      ret

// s must be in xmm1, it's only used at the end to subtract from xmm0, it must also be double since vsubsd is used
//
// p                                q                   r                   q+r                 p/(q+r)
// rdi, int, since it's             xmm0, float         rsi, long           float, xmm0         float, xmm0
//      converted
//      on line 3
//
// rdi, int, since it's             rsi, long          xmm0, float          float, xmm0         float, xmm0
//      converted
//      on line 3
