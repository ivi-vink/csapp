// addq     %rdx, %rdi              Aptr = xa + 64i
// fix_matrix = int[16][16], so each int is 4 bytes and we need to multiple by the number of columns to find the
// i row,   A + L(C*i + j) <=> A + 4(16*i)
//
//  leaq (%rsi, %rcx, 4), %rcx      Bptr = xb + 4k, this one is simple B + L(C*i + j) <=> B + 4(j), find the first row of the column j
//
//  leaq 1024(%rcx), %rsi           Bend = xb + 4k + 1024, find the N row of column k,
//                                                          B + 4(16*16 + k) <=> B + 1024 + 4k
