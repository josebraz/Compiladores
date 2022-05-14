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
	movl	$400, -8(%rbp)
	movl	$2, -12(%rbp)
	movl	-8(%rbp), %eax
	movl	-12(%rbp), %ebx
	movl	%edx, %r14d
	cltd
	idivl	%ebx
	movl	%r14d, %edx
	movl	%eax, %ebx
	movl	%r15d, %eax
	movl	-8(%rbp), %eax
	movl	-12(%rbp), %ecx
	movl	%edx, %r14d
	cltd
	idivl	%ecx
	movl	%r14d, %edx
	movl	-12(%rbp), %ecx
	cltd
	idivl	%ecx
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
