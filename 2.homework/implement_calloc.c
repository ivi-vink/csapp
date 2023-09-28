#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *my_calloc(size_t nmemb, size_t size) {
    if (nmemb == 0 || size == 0) {
        return NULL;
    }
    /* Check if invariant of multiplication is broken by overflow */
    size_t membytes = nmemb * size;
    if (membytes/nmemb != size) {
        return NULL;
    }
    void *mem_or_null = malloc(membytes);
    if (mem_or_null == NULL) {
        return NULL;
    }

    return memset(mem_or_null, 0, membytes);
}

int main() {
    char *buf = my_calloc(10, 15);
    int i;
    for (i=0; i<10*15; ++i)
        printf("%c", 97 + buf[i]);
    return 0;
}
