#define OP <

// x <- %rdi
// %rbx <- 15 + (x), bias to round towards zero
// ZF, SF <- %rdi & %rdi, check if pos or neg
// %rbx <- x if x >= 0, set to unbiased if pos
// %rbx <- %rbx >> 4, divide by 16
short arith(short x) {
    return x / 16;
}
