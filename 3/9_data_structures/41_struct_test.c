struct test {
    short *p;
    struct {
        short x;
        short y;
    } s;
    struct test *next;
}

// A.
//      p: 0, it's at the beginning of the struct
//      s.x: (length p) <- 8
//      s.y: (length p) + (length s.x) <- 10
//      next: (length p) + (length s.x) + (length s.y) <- 12
// B.
//      total bytes should be 20. pointer + short + short + pointer
// C.
//  st in %rdi
//  st_init:
//      movl 8(%rdi), %eax
//      movl %eax, 10(%rdi)
//      leaq 10(%rdi), %rax
//      movq %rax, (%rdi)
//      movq %rdi, 12(%rdi)
//      ret
void st_init(struct test *st) {
    st->s.y = st->s.x;
    st->p = &(st->s.y);
    st->next = st;
}
