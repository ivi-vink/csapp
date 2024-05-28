// Label    PC      Instruction     %rdi    %rsi    %rax    %rsp            *%rsp   Description
// M1       400560  callq           10                      7fffffffe820            Call first(10)
//
// F1       400548  lea             10                      7fffffffe818    400565  v <- x + 1
// F2       40054c  sub             10      11              7fffffffe818    400565  u <- x - 1
// F3       400550  callq           9       11              7fffffffe818    400565  Call last(9, 11)
//
// L1       400540  mov             9       11              7fffffffe810    400555  rax <- u
// L2       400543  imul            9       11      9       7fffffffe810    400555  rax <- rax * v
// L3       400547  retq            9       11      99      7fffffffe810    400555  return
//
// F4       400555  retq            9       11      99      7fffffffe818    400565  return
//
// M2       400565  mov             9       11      99                              Resume
