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
	movl	$4, %eax
	movl	%edx, %r14d
	movl	$2, %r13d
	cltd
	idivl	%r13d
	movl	%r14d, %edx
	movl	%eax, %ebx
	movl	%r15d, %eax
	addl	$2, %ebx
	movl	$4, %eax
	movl	$4, %r13d
	cltd
	imull	%r13d
	movl	%eax, %edx
	movl	%r15d, %eax
	movl	%edx, %r15d
	addl	%ebx, %r15d
	movl	%r15d, %eax
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
