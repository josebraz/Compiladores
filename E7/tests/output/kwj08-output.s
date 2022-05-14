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
	movl	$15, %eax
	movl	%eax, -8(%rbp)
	movl	$3, %ebx
	movl	%ebx, -12(%rbp)
	movl	%edx, %r14d
	cltd
	imull	%ebx
	movl	%r14d, %edx
	addl	$10, %eax
	movl	%eax, -4(%rbp)
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
