
./fcvt:     file format elf64-x86-64


Disassembly of section .init:

0000000000401000 <_init>:
  401000:	f3 0f 1e fa          	endbr64
  401004:	48 83 ec 08          	sub    $0x8,%rsp
  401008:	48 8b 05 e9 2f 00 00 	mov    0x2fe9(%rip),%rax        # 403ff8 <__gmon_start__@Base>
  40100f:	48 85 c0             	test   %rax,%rax
  401012:	74 02                	je     401016 <_init+0x16>
  401014:	ff d0                	call   *%rax
  401016:	48 83 c4 08          	add    $0x8,%rsp
  40101a:	c3                   	ret

Disassembly of section .plt:

0000000000401020 <__stack_chk_fail@plt-0x10>:
  401020:	ff 35 b2 2f 00 00    	push   0x2fb2(%rip)        # 403fd8 <_GLOBAL_OFFSET_TABLE_+0x8>
  401026:	ff 25 b4 2f 00 00    	jmp    *0x2fb4(%rip)        # 403fe0 <_GLOBAL_OFFSET_TABLE_+0x10>
  40102c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000401030 <__stack_chk_fail@plt>:
  401030:	ff 25 b2 2f 00 00    	jmp    *0x2fb2(%rip)        # 403fe8 <__stack_chk_fail@GLIBC_2.4>
  401036:	68 00 00 00 00       	push   $0x0
  40103b:	e9 e0 ff ff ff       	jmp    401020 <_init+0x20>

Disassembly of section .text:

0000000000401040 <_start>:
  401040:	f3 0f 1e fa          	endbr64
  401044:	31 ed                	xor    %ebp,%ebp
  401046:	49 89 d1             	mov    %rdx,%r9
  401049:	5e                   	pop    %rsi
  40104a:	48 89 e2             	mov    %rsp,%rdx
  40104d:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
  401051:	50                   	push   %rax
  401052:	54                   	push   %rsp
  401053:	45 31 c0             	xor    %r8d,%r8d
  401056:	31 c9                	xor    %ecx,%ecx
  401058:	48 c7 c7 4f 11 40 00 	mov    $0x40114f,%rdi
  40105f:	ff 15 8b 2f 00 00    	call   *0x2f8b(%rip)        # 403ff0 <__libc_start_main@GLIBC_2.34>
  401065:	f4                   	hlt
  401066:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  40106d:	00 00 00 

0000000000401070 <_dl_relocate_static_pie>:
  401070:	f3 0f 1e fa          	endbr64
  401074:	c3                   	ret
  401075:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  40107c:	00 00 00 
  40107f:	90                   	nop

0000000000401080 <deregister_tm_clones>:
  401080:	b8 10 40 40 00       	mov    $0x404010,%eax
  401085:	48 3d 10 40 40 00    	cmp    $0x404010,%rax
  40108b:	74 13                	je     4010a0 <deregister_tm_clones+0x20>
  40108d:	b8 00 00 00 00       	mov    $0x0,%eax
  401092:	48 85 c0             	test   %rax,%rax
  401095:	74 09                	je     4010a0 <deregister_tm_clones+0x20>
  401097:	bf 10 40 40 00       	mov    $0x404010,%edi
  40109c:	ff e0                	jmp    *%rax
  40109e:	66 90                	xchg   %ax,%ax
  4010a0:	c3                   	ret
  4010a1:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  4010a8:	00 00 00 00 
  4010ac:	0f 1f 40 00          	nopl   0x0(%rax)

00000000004010b0 <register_tm_clones>:
  4010b0:	be 10 40 40 00       	mov    $0x404010,%esi
  4010b5:	48 81 ee 10 40 40 00 	sub    $0x404010,%rsi
  4010bc:	48 89 f0             	mov    %rsi,%rax
  4010bf:	48 c1 ee 3f          	shr    $0x3f,%rsi
  4010c3:	48 c1 f8 03          	sar    $0x3,%rax
  4010c7:	48 01 c6             	add    %rax,%rsi
  4010ca:	48 d1 fe             	sar    %rsi
  4010cd:	74 11                	je     4010e0 <register_tm_clones+0x30>
  4010cf:	b8 00 00 00 00       	mov    $0x0,%eax
  4010d4:	48 85 c0             	test   %rax,%rax
  4010d7:	74 07                	je     4010e0 <register_tm_clones+0x30>
  4010d9:	bf 10 40 40 00       	mov    $0x404010,%edi
  4010de:	ff e0                	jmp    *%rax
  4010e0:	c3                   	ret
  4010e1:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  4010e8:	00 00 00 00 
  4010ec:	0f 1f 40 00          	nopl   0x0(%rax)

00000000004010f0 <__do_global_dtors_aux>:
  4010f0:	f3 0f 1e fa          	endbr64
  4010f4:	80 3d 15 2f 00 00 00 	cmpb   $0x0,0x2f15(%rip)        # 404010 <__TMC_END__>
  4010fb:	75 13                	jne    401110 <__do_global_dtors_aux+0x20>
  4010fd:	55                   	push   %rbp
  4010fe:	48 89 e5             	mov    %rsp,%rbp
  401101:	e8 7a ff ff ff       	call   401080 <deregister_tm_clones>
  401106:	c6 05 03 2f 00 00 01 	movb   $0x1,0x2f03(%rip)        # 404010 <__TMC_END__>
  40110d:	5d                   	pop    %rbp
  40110e:	c3                   	ret
  40110f:	90                   	nop
  401110:	c3                   	ret
  401111:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  401118:	00 00 00 00 
  40111c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000401120 <frame_dummy>:
  401120:	f3 0f 1e fa          	endbr64
  401124:	eb 8a                	jmp    4010b0 <register_tm_clones>

0000000000401126 <fcvt>:
  401126:	c5 f0 57 c9          	vxorps %xmm1,%xmm1,%xmm1
  40112a:	c5 fa 10 06          	vmovss (%rsi),%xmm0
  40112e:	48 8b 01             	mov    (%rcx),%rax
  401131:	c4 61 fb 2c 02       	vcvttsd2si (%rdx),%r8
  401136:	4c 89 01             	mov    %r8,(%rcx)
  401139:	c5 f2 2a d7          	vcvtsi2ss %edi,%xmm1,%xmm2
  40113d:	c5 fa 11 16          	vmovss %xmm2,(%rsi)
  401141:	c4 e1 f3 2a c8       	vcvtsi2sd %rax,%xmm1,%xmm1
  401146:	c5 fb 11 0a          	vmovsd %xmm1,(%rdx)
  40114a:	c5 fa 5a c0          	vcvtss2sd %xmm0,%xmm0,%xmm0
  40114e:	c3                   	ret

000000000040114f <main>:
  40114f:	48 83 ec 28          	sub    $0x28,%rsp
  401153:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  40115a:	00 00 
  40115c:	48 89 44 24 18       	mov    %rax,0x18(%rsp)
  401161:	31 c0                	xor    %eax,%eax
  401163:	c7 44 24 04 00 00 00 	movl   $0x3f000000,0x4(%rsp)
  40116a:	3f 
  40116b:	48 8b 05 96 0e 00 00 	mov    0xe96(%rip),%rax        # 402008 <_IO_stdin_used+0x8>
  401172:	48 89 44 24 08       	mov    %rax,0x8(%rsp)
  401177:	48 c7 44 24 10 01 00 	movq   $0x1,0x10(%rsp)
  40117e:	00 00 
  401180:	48 8d 4c 24 10       	lea    0x10(%rsp),%rcx
  401185:	48 8d 54 24 08       	lea    0x8(%rsp),%rdx
  40118a:	48 8d 74 24 04       	lea    0x4(%rsp),%rsi
  40118f:	bf 2a 00 00 00       	mov    $0x2a,%edi
  401194:	e8 8d ff ff ff       	call   401126 <fcvt>
  401199:	48 8b 44 24 18       	mov    0x18(%rsp),%rax
  40119e:	64 48 2b 04 25 28 00 	sub    %fs:0x28,%rax
  4011a5:	00 00 
  4011a7:	75 0a                	jne    4011b3 <main+0x64>
  4011a9:	b8 00 00 00 00       	mov    $0x0,%eax
  4011ae:	48 83 c4 28          	add    $0x28,%rsp
  4011b2:	c3                   	ret
  4011b3:	e8 78 fe ff ff       	call   401030 <__stack_chk_fail@plt>

Disassembly of section .fini:

00000000004011b8 <_fini>:
  4011b8:	f3 0f 1e fa          	endbr64
  4011bc:	48 83 ec 08          	sub    $0x8,%rsp
  4011c0:	48 83 c4 08          	add    $0x8,%rsp
  4011c4:	c3                   	ret
