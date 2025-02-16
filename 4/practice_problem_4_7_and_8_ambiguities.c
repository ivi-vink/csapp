/*
pushtest:
	movq %rsp, %rax 	Copy stack pointer
	pushq %rsp		Push stack pointer, original or after incrementing
	popq %rdx		Pop the value back
	subq %rdx, %rax		Always 0 on this machine

It must first push the original rsp decremented address and then decrement rsp itself, otherwise a difference is expected after pushing and popping.
*/

/*
poptest:
	movq %rsp, %rdi		Save the original sp
	pushq $0xabcd		Push test value
	popq %rsp		Pop test value to rsp
	movq %rsp, %rax 	Set popped value as return value
	movq %rdi, %rsp
	ret

Rsp gets set the value in memory at rsp.

From solutions:
mrmovq (%rsp), %rsp

I guess it just reads the stack value and overwrites it into rsp
*/
