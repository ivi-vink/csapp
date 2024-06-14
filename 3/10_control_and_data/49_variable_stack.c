// A.
// vframe:
//      pushq       %rbp
//      movq        %rsp, %rbp
//      subq        $16, %rsp
//      leaq        22(,%rdi,8), %rax
//      andq        $-16, %rax
//
//
//      bitlevel representation of -16
//              1111111111111111111111111111111111111111111111111111111111110000
//
//      rax
//      22 + n*8
//      n=0     0000000000000000000000000000000000000000000000000000000000010110    22
//      n=1     0000000000000000000000000000000000000000000000000000000000011110    30
//      n=2     0000000000000000000000000000000000000000000000000000000000100110    38
//      n=3     0000000000000000000000000000000000000000000000000000000000101110    46
//      n=4     0000000000000000000000000000000000000000000000000000000000110110    54
//      n=5     0000000000000000000000000000000000000000000000000000000000111110    62
//
//      (22 + n*8) & -16
//      n=0     0000000000000000000000000000000000000000000000000000000000010000    16 8n+16
//      n=1     0000000000000000000000000000000000000000000000000000000000010000    16 8n+8
//      n=2     0000000000000000000000000000000000000000000000000000000000100000    32 8n+16
//      n=3     0000000000000000000000000000000000000000000000000000000000100000    32 8n+8
//      n=4     0000000000000000000000000000000000000000000000000000000000110000    48
//      n=5     0000000000000000000000000000000000000000000000000000000000110000    48
//
// print("{:064b}".format((0*8+22) & -16))
// print("{:064b}".format((1*8+22) & -16))
// print("{:064b}".format((2*8+22) & -16))
// print("{:064b}".format((3*8+22) & -16))
// print("{:064b}".format((4*8+22) & -16))
// print("{:064b}".format((5*8+22) & -16))
//
// B.
// vframe:
//      pushq       %rbp
//      movq        %rsp, %rbp
//      subq        $16, %rsp
//      leaq        22(,%rdi,8), %rax
//      andq        $-16, %rax
//
//      subq        %rax, %rsp
//
//      leaq        7(%rsp), %rax           rax <- (rsp+7) = (rsp+(n-1)), n = 8
//      shrq        $3, %rax                rax <- (floor(rax/8))
//      leaq        0(,%rax,8), %r8         r8 <- ceil(rsp/8)*8
//
// Important We are growing the stack downwards.
// But the array index grows upwards.
//
//  See 2.3.7 for derivation.
// If x%(1<<k) == 0 then the bias has no effect, rounding down does not happen, there is no fraction.
// else
//  Since the operation of adding the bias and then flooring happens,
//  this results in rounding towards zero, or taking the ceiling.
//
// So if rsp was a multiple of 8 then nothing happens.
// Otherwise the start of the array is set to the first multiple of 8 towards the bottom of the stack (ceil goes towards greater addresses of the bottom).
//
// C.
//
// s_2 = (- s_1
//          (+ (if (odd? n) 8 16) (* n 8) )
//       )
//
// p = ceil(s2/8)*8
// e2 = (- p s2)
// e1 = (- s2 s1 e2 8n)
//
// 2065 - (8+5*8)
//
//      n       s_1         s_2         p           e_1         e_2
//      5       2065        2017        2024        1           7
//      6       2064        2000        2000        16          0
//
// D.
//      p is 8byte aligned owing to the 8-10 instructions.
//      s2 is not guaranteed to be aligned, so 1 byte. (But all we are doing is subtracting multiples of 16 from s1... not sure how this helps)
