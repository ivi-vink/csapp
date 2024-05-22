#include <stdio.h>

typedef char data_t;

#define COMP <=

// a in rdx, b in rsi
//
// cmpl %esi, %edi  (Compare long (double word, or 4 bytes). (a - b) )
// setl %al (set lower? %rax return value)
//
// COMP is <, and data_t is 32 bits so maybe int or unsigned int or float
//
// cmpw %si, %di (Compare word (a-b), short)
// setge %al     (Greater than or equal >=)
//
// cmpb %sil, %dil (Compare byte (a-b))
// setbe %al (Comp <=)
//
// cmpq %rsi, %rdi (Compare 8 bytes quad words (long , double, char *))
// setne %al
int comp(data_t a, data_t b) {
    return a COMP b;
}

#define TEST >

int test(data_t a) {
    return a TEST 0;
}

int main() {
    printf("%x hello world", comp(1, 2));
    return 0;
}

