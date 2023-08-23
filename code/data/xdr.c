#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void* copy_elements(void* ele_src[], int ele_cnt, size_t ele_size)  {
    uint64_t asize = ele_cnt * (uint64_t) ele_size;
    void *result = malloc(asize);
    if (result == NULL)
	return NULL;
    void *next = result;
    int i;
    for (i = 0; i < ele_cnt; i++) {
	memcpy(next, ele_src[i], ele_size);
	next += ele_size;
    }
    return result;
}

void main() {
    int i = 0;
    char* input[] = {"somestring","some666666"};
    printf("%s\n", input[0]);
    printf("%s\n", *(input+1)); // these two lines are basically the same thing *(input+1) = input[1]
    char* result = copy_elements((void *) input, 2, 10);
    printf("%s\n", result);
}
