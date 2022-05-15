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
	movl	$3, %eax
	movl	%eax, -4(%rbp)
	movl	$6, %ebx
	movl	%ebx, -8(%rbp)
	addl	%ebx, %eax
	movl	%eax, -12(%rbp)
	movl	%eax, -16(%rbp)
	movl	%eax, -20(%rbp)
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
