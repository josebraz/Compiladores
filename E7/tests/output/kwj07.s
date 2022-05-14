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
	movl	$2, -8(%rbp)
	movl	$3, -12(%rbp)
	movl	-8(%rbp), %eax
	movl	-12(%rbp), %ebx
	movl	%edx, %r14d
	cltd
	imull	%ebx
	movl	%r14d, %edx
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	movl	-12(%rbp), %ebx
	movl	%edx, %r14d
	cltd
	imull	%ebx
	movl	%r14d, %edx
	movl	%eax, -8(%rbp)
	movl	-4(%rbp), %eax
	movl	-8(%rbp), %ebx
	movl	%edx, %r14d
	cltd
	imull	%ebx
	movl	%r14d, %edx
	movl	%eax, -12(%rbp)
	movl	-12(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
