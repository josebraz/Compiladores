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
	movl	$400, %ebx
	movl	%ebx, -8(%rbp)
	movl	$2, %eax
	movl	%eax, -12(%rbp)
	movl	%eax, %r15d
	movl	%ebx, %eax
	movl	%edx, %r14d
	cltd
	idivl	%eax
	movl	%r14d, %edx
	movl	%eax, %ecx
	movl	%r15d, %eax
	movl	%ecx, %r15d
	addl	%ebx, %r15d
	movl	%r15d, %eax
	addl	%ecx, %eax
	movl	%eax, -4(%rbp)
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
