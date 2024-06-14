#include <stdio.h>

struct ACE {
    short       v;
    struct ACE *p;
};

// B. it's a linked list of short values that are multiplied.
short test(struct ACE *ptr) {
    short v = 1;
    while (ptr) {
        v *= ptr->v;
        ptr = ptr->p;
    }
    return v;
}

int main(void) {
    struct ACE a = {2, NULL};
    struct ACE b = {3, NULL};
    a.p = &b;
    printf("%d\n", test(&a));
}
