#define M 20;
#define N 30;

long P[5][7];
long Q[7][5];

// i in rdi, j in rsi
// sum_element:
//      leaq    0(,%rdi, 8), %rdx       %rdx <- 8*i
//      subq    %rdi, %rdx              %rdx <- %rdx - i
//      addq    %rsi, %rdx              %rdx <- %rdx + j
//      leaq    (%rsi, %rsi, 4), %rax   %rax <- 5j
//      addq    %rax, %rdi              %rdi <- %rax + %rdi // rdi <- 5j + i
//      movq    Q(, %rdi, 8), %rax      %rax <- xq + 8(5j + i)
//      addq    P(, %rdx, 8), %rax      %rax <- %rax + xp + 8(7i + j)
long sum_element(long i, long j) {
    return P[i][j] + Q[j][i];
}
