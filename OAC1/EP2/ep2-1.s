	.file	"ep2-1.c"
	.intel_syntax noprefix
	.text
	.def	__main;	.scl	2;	.type	32;	.endef
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
main:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 112
	call	__main
	mov	edx, DWORD PTR -4[rbp]
	mov	eax, DWORD PTR -8[rbp]
	add	edx, eax
	mov	eax, DWORD PTR -12[rbp]
	add	edx, eax
	mov	eax, DWORD PTR -16[rbp]
	add	edx, eax
	mov	eax, DWORD PTR -20[rbp]
	add	edx, eax
	mov	eax, DWORD PTR -24[rbp]
	add	edx, eax
	mov	eax, DWORD PTR -28[rbp]
	add	edx, eax
	mov	eax, DWORD PTR -32[rbp]
	add	edx, eax
	mov	eax, DWORD PTR -36[rbp]
	add	edx, eax
	mov	eax, DWORD PTR -40[rbp]
	add	edx, eax
	mov	eax, DWORD PTR -44[rbp]
	add	edx, eax
	mov	eax, DWORD PTR -48[rbp]
	add	edx, eax
	mov	eax, DWORD PTR -52[rbp]
	add	edx, eax
	mov	eax, DWORD PTR -56[rbp]
	add	edx, eax
	mov	eax, DWORD PTR -60[rbp]
	add	edx, eax
	mov	eax, DWORD PTR -64[rbp]
	add	edx, eax
	mov	eax, DWORD PTR -68[rbp]
	add	edx, eax
	mov	eax, DWORD PTR -72[rbp]
	add	eax, edx
	mov	DWORD PTR -76[rbp], eax
	nop
	leave
	ret
	.ident	"GCC: (x86_64-posix-seh-rev0, Built by MinGW-Builds project) 13.2.0"
