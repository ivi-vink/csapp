double funct2(double w, int x, float y, long z)
{
    return x*y - w/z;
}

// double funct2(double w, int x, float y, long z)
// w in xmm0, x in edi, y in xmm1, z in rsi
// funct2:
//      vcvtsi2ss       %edi, %xmm2, %xmm2      // convert int to float
//      vmulss          %xmm1, %xmm2, %xmm1     // xmm1<- x*y, multiply sencond and third float
//      vunpcklps       %xmm1, %xmm1, %xmm1     // do convert float to double?
//      vcvtps2pd       %xmm1, %xmm2            // do convert float to double?
//      vcvtsi2sdq      %rsi, %xmm1, %xmm1      // xmm1 <- z, convert long to double?
//      vdivsd          %xmm1, %xmm0, %xmm0     // xmm0<- w/z
//      vsubsd          %xmm0, %xmm2, %xmm0     // xmm0<- (x*y) - w/z
//      ret
