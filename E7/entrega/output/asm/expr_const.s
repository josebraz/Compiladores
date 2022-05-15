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
	movl	%edx, %r14d
	movl	$4, %r13d
	cltd
	imull	%r13d
	movl	%r14d, %edx
	movl	%eax, %ebx
	movl	%r15d, %eax
	movl	$3, %eax
	movl	$7, %r13d
	cltd
	idivl	%r13d
	movl	%eax, %edx
	movl	%r15d, %eax
	movl	%edx, %r15d
	addl	%ebx, %r15d
	movl	%r15d, %eax
	movl	%eax, -4(%rbp)
	movl	$3, %eax
	movl	%edx, %r14d
	movl	$4, %r13d
	cltd
	imull	%r13d
	movl	%r14d, %edx
	movl	%eax, %ebx
	movl	%r15d, %eax
	movl	$3, %eax
	movl	$7, %r13d
	cltd
	idivl	%r13d
	movl	%eax, %edx
	movl	%r15d, %eax
	movl	%edx, %r15d
	addl	%ebx, %r15d
	movl	%r15d, %eax
	movl	%eax, -8(%rbp)
	movl	$3, -12(%rbp)
	movl	$3, %eax
	movl	%edx, %r14d
	movl	$4, %r13d
	cltd
	imull	%r13d
	movl	%r14d, %edx
	movl	%eax, %ebx
	movl	%r15d, %eax
	movl	$3, %eax
	movl	$7, %r13d
	cltd
	idivl	%r13d
	movl	%eax, %edx
	movl	%r15d, %eax
	movl	%edx, %r15d
	addl	%ebx, %r15d
	movl	%r15d, %eax
	movl	%eax, -16(%rbp)
	movl	-12(%rbp), %eax
	movl	-16(%rbp), %ebx
	addl	%ebx, %eax
	movl	%eax, -20(%rbp)
	movl	-8(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
