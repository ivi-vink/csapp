#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// char *get_line()
//      400720: 53                  push %rbx
//      400721: 48 83 ec 10         sub $0x10,%rsp
//      400725: 48 89 e7            mov %rsp,%rdi
//      400728  e8 73 ff ff ff      callq 4006a0 <gets>
char *get_line() {
    char buf[4];
    char *result;
    gets(buf);
    result = malloc(strlen(buf));
    strcpy(result, buf);
    return result;
}
int main(void) {
    printf("%s\n", get_line());
}
// A. B. (I mistakingly thought $0x10 was the same as $10...)
//      00 34 33 32 31 30 39 38         return address
//      37 36 35 34 33 32 31 30         callee saved %rbx
//      39 38 37 36 35 34 33 32<        sub $rsp - 8
//      31 30 00 00 00 00 00 40         sub $rsp -16
//      07 32<                          return address gets
//
// C. 00 34 33 32 31 30 39 38
// D. %rbx
// E. Malloc should consider the terminating null (strlen+1) and check for NULL pointer result
