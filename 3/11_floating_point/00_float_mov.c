// v1 in %xmm0, src in %rdi, dst in %rsi
// float_mov:
//      vmovaps     %xmm0, %xmm1            Copy v1
//      vmovss      (%rdi), %xmm0           Read v2 from src
//      vmovss      %xmm1, (%rsi)           Write v1 to dst
//      ret;
float float_mov(float v1, float *src, float *dst) {
    float v2 = *src;
    *dst = v1;
    return v2;
}
