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
	movl	$10, -4(%rbp)
	movl	$20, -8(%rbp)
	movl	$30, -12(%rbp)
	movl	-4(%rbp), %eax
	movl	-8(%rbp), %ebx
	addl	%ebx, %eax
	movl	-12(%rbp), %ebx
	addl	%ebx, %eax
	addl	$40, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc