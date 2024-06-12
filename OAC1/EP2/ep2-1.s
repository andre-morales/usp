	.file	"ep2-1.c"
	.intel_syntax noprefix
	.text
	.def	__main;	.scl	2;	.type	32;	.endef
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	push	rbp
	.seh_pushreg	rbp
	mov	rbp, rsp
	.seh_setframe	rbp, 0
	sub	rsp, 112
	.seh_stackalloc	112
	.seh_endprologue
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
	add	rsp, 112
	pop	rbp
	ret
	.seh_endproc
	.ident	"GCC: (x86_64-win32-seh-rev0, Built by MinGW-Builds project) 13.2.0"
