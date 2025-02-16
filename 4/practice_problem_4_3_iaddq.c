#include <stdio.h>

long sum(long *start, long count)
{
	long sum = 0;
	while (count) {
		sum += *start;
		start++;
		count--;
	}
	return sum;
}

int main() {
	long start[] = { 42, 11, 12 };
	return printf("%d\n", sum(start, (long)1));
}

/*
long sum(long *start, long count)
start in %rdi, count in %rsi
sum:
	movl $0, %eax		sum = 0
	jmp .12			Goto test
.L3:				loop:
	addq (%rdi), %rax 		Add *start
	addq $8, %rdi 			start++
	subq $1, %rsi 			count--
.L2: 				test:
	testq %rsi, %rsi 		Test sum
	jne .L3 			If !=O, goto loop
	rep; ret			Return
*/

/*
long sum(long *start, long count)
start in %rdi, count in %rsi
sum:
	irmovq $8,%r8 		Constant 8
	irmovq $1,%r9 		Constant 1
	xorq %rax,%rax		sum = 0
	andq %rsi,%rsi		Set cc
	jmp test		Goto test
loop:
	mrmovq (%rdi), %r10 	Get *start
	addq %r10,%rax		Add to sum
	addq %r8,%rdi 		start++
	subq %r9,%rsi 		count--. Set CC
test:
	jne loop		Stop when 0
	ret
*/

/* Using iaddq
First byte
- C, 12
- 0, first variant of iadd

Second byte
- F, 15, absence of first argument
- rB, register number 0-15 to add V to

Other 0-8 bytes V

long sum(long *start, long count)
start in %rdi, count in %rsi
sum:
	xorq %rax,%rax		sum = 0
	andq %rsi,%rsi		Set cc (nop), ZF=0 if count != 0 else 1, SF=0 if count > 0, OF=0
	jmp test		Goto test
loop:
	mrmovq (%rdi), %r10 	Get *start
	addq %r10,%rax		Add to sum
	iaddq $8,%rdi 		start++
	iaddq $-1,%rsi 		count--. Set CC
test:
	jne loop		Stop when 0, (~ZF)
	ret
*/
