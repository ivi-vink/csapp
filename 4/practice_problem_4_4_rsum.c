#include <stdio.h>

long rsum(long *start, long count) {
	if (count <= 0)
		return 0;
	return *start + rsum(start + 1, count - 1);
}

int main() {
	long nums[] = {1, 2, 3};
	printf("%d\n", rsum(nums, 3));
}

/*
long rsum(long *start, long count)
start in %rdi, count in %rsi
test:
	xorq 			%rax, %rax 	return = 0
	andq 			%rsi, %rsi,  Set CC again?
	jle return 		Count <= 0, or jump
	push %rbx		keep original rbx around
	mrmovq (%rdi), %rbx 	Get *start
	irmovq $8,%r8 		Constant 8
	irmovq $1,%r9 		Constant 1
	addq %r8,%rdi 		start++
	subq %r9,%rsi 		count--. Set CC
	call rsum		Recurse
	addq %rbx, %rax		Accumulate
	popq %rbx		Restore original rbx
return:
	ret
*/

/*
0000000000001149 <rsum>:
    1149:	48 85 f6             	test   %rsi,%rsi
    114c:	7e 16                	jle    1164 <rsum+0x1b>

    114e:	53                   	push   %rbx
    114f:	48 8b 1f             	mov    (%rdi),%rbx
    1152:	48 83 ee 01          	sub    $0x1,%rsi
    1156:	48 83 c7 08          	add    $0x8,%rdi
    115a:	e8 ea ff ff ff       	call   1149 <rsum>
    115f:	48 01 d8             	add    %rbx,%rax
    1162:	5b                   	pop    %rbx			Return accumulated %rbx
    1163:	c3                   	ret

    1164:	b8 00 00 00 00       	mov    $0x0,%eax 		Return 0 after first test
    1169:	c3                   	ret
*/
