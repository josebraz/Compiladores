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
	movl	$15, %ebx
	movl	%ebx, -8(%rbp)
	movl	$3, %eax
	movl	%eax, -12(%rbp)
	movl	%eax, %r15d
	addl	%ebx, %r15d
	movl	%r15d, %ecx
	movl	%ebx, %r15d
	addl	%ecx, %r15d
	movl	%r15d, %eax
	movl	$10, %r15d
	addl	%ecx, %r15d
	movl	%r15d, %eax
	movl	%eax, -4(%rbp)
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
