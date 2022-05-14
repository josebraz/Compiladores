	.comm	a,4,4
	.comm	b,4,4
	.comm	z,4,4
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$4, b(%rip)
	movl	$9, z(%rip)
	movl	z(%rip), %eax
	movl	b(%rip), %ebx
	addl	%ebx, %eax
	movl	%eax, a(%rip)
	movl	a(%rip), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
