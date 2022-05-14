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
	movl	$75, -8(%rbp)
	movl	$3, -12(%rbp)
	movl	-8(%rbp), %eax
	movl	-12(%rbp), %ebx
	movl	%edx, %r14d
	cltd
	idivl	%ebx
	movl	%r14d, %edx
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	movl	%edx, %r14d
	movl	$5, %r13d
	cltd
	idivl	%r13d
	movl	%r14d, %edx
	movl	%eax, -8(%rbp)
	movl	-4(%rbp), %eax
	movl	%edx, %r14d
	movl	$2, %r13d
	cltd
	idivl	%r13d
	movl	%r14d, %edx
	movl	%eax, -12(%rbp)
	movl	-12(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
