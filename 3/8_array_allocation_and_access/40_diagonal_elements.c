// A in rdi, val in rsi
//  fix_set_diag:
//      movl    $0, %eax
//  .L13
//      movl    %esi, (%rdi, %rax)
//      addq    $68, %rax
//      cmpq    $1088, %rax
//      jne     .L13
//      rep; ret
#include <stdio.h>
#define N 16
typedef int fix_matrix[N][N];

void fix_set_diag(fix_matrix A, int val) {
    long i;
    for (i = 0; i < N; i++) {
        A[i][i] = val;
    }
}

void fix_set_diag_opt(fix_matrix A, int val) {
    int *Aptr = &A[0][0];
    int *Aend = &A[N][N];
    do {
        *Aptr = val;
        Aptr += N; // Next row
        Aptr ++; // Next column
    } while (Aptr != Aend);
}

int main(void) {
    int i, j;
    fix_matrix A;
    for (i=0; i < N; i++) {
        for (j=0; j < N; j++) {
            A[i][j] = 0;
        }
    }

    i, j = 0, 0;
    fix_set_diag_opt(A, 1);
    for (i=0; i < N; i++) {
        for (j=0; j < N; j++) {
            printf("%ld", A[i][j]);
        }
        printf("\n");
    }
}
