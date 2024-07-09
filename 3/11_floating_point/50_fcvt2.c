#include <stdio.h>

// ip = rdi
// fp = rsi
// dp = rdx
// l  = rcx
// fcvt:
//      movl            (%rdi), %eax                eax<-int value of ip to eax
//      vmovss          (%rsi), %xmm0               xmm0<- move int value to float (vmov signed single?)
//      vcvttsd2si      (%rdx), %r8d                r8d<- double value to signed integer?
//      movl            %r8d, (%rdi)                *ip<- set pointer to truncated value of rdx
//      vcvttsd2ss      %eax, %xmm1, %xmm1          xmm1<- convert int to float
//      vmovss          %xmm1, (%rsi)               fp<-*ip
//      vcvtsi2sdq      %rcx, %xmm1, %xmm1          xmm1<- convert long to double
//      vmovsd          %xmm1, (%rdx)               dp<- l
//      vunpcklps       %xmm0, %xmm0, %xmm0
//      vcvtps2pd       %xmm0, %xmm0
//      ret
double fcvt2(int *ip, float *fp, double *dp, long l)
{
    int i = *ip; float f = *fp; double d = *dp;

    *ip = (int)         d;
    *fp = (float)       i;
    *dp = (double)      l;
    return (double)     f;
}
