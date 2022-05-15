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
	movl	$12, -4(%rbp)
	movl	$12, %ebx
	movl	%ebx, -8(%rbp)
	movl	$3, %eax
	movl	%eax, -12(%rbp)
	movl	$12, %ecx
	movl	%ecx, -16(%rbp)
	movl	%ecx, %r15d
	addl	%eax, %r15d
	movl	%r15d, %edx
	movl	%edx, -20(%rbp)
	movl	%ebx, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
