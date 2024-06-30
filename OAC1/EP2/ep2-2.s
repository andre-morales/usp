	.file	"ep2-2.c"
	.intel_syntax noprefix
	.text
	.def	__main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
.LC0:
	.ascii "algo\0"
.LC1:
	.ascii "outro\0"
.LC2:
	.ascii "xeque\0"
	.text
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
main:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 48
	call	__main
	mov	edx, DWORD PTR -4[rbp]
	mov	eax, DWORD PTR -8[rbp]
	add	eax, edx
	cmp	DWORD PTR -12[rbp], eax
	jle	.L2
	add	DWORD PTR -16[rbp], 1
	lea	rax, .LC0[rip]
	mov	rcx, rax
	call	printf
	jmp	.L3
.L2:
	add	DWORD PTR -8[rbp], 1
	lea	rax, .LC1[rip]
	mov	rcx, rax
	call	puts
.L3:
	add	DWORD PTR -12[rbp], 5
	lea	rax, .LC2[rip]
	mov	rcx, rax
	call	printf
	nop
	leave
	ret
	.ident	"GCC: (x86_64-posix-seh-rev0, Built by MinGW-Builds project) 13.2.0"
	.def	printf;	.scl	2;	.type	32;	.endef
	.def	puts;	.scl	2;	.type	32;	.endef
