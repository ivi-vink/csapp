// S and i in rdx and rcx
//          type        value       assembly
// S+1      short *     xs + 2      leaq $2(%rdx), %rax, // leaq since we want to store the address not the value
// S[3]     short       M[xs+6]     movw $6(%rdx), %ax
// &S[i]    short *     xs+2i       leaq (rdx, rcx, 2), %rax
// S[4*i+1] short       M[xs+8i+2]  movw $2(%rdx, %rcx, 8), %ax
// S+i-5    short *     xs+2i-10    leaq $-10(%rdx, %rcx, 2), %rax
