typedef int dest_t
typedef int src_t

dest_t cvt(src_t x)
{
    dest_t y = (dest_t) x;
    return y;
}

// T_x              T_y             Instruction(s)
//
// long             double          vcvtsi2sdq      %rdi, %xmm0
// double           int             vcvttsd2si      %xmm0, %rdi
// double           float           vmovddup        %xmm0, %xmm0
//                                  vcvtpd2psx      %xmm0, %xmm0
// long             float           vcvtsi2ssq      %rdi, %xmm0
// float            long            vcvttss2siq     %xmm0, %rdi
//
