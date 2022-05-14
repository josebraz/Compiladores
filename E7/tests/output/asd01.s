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
	movl	$20, %eax
	movl	%eax, -8(%rbp)
	movl	$30, %ebx
	movl	%ebx, -12(%rbp)
	movl	%ebx, %r15d
	addl	%eax, %r15d
	movl	%r15d, %ecx
	movl	%eax, %r15d
	movl	%ecx, %eax
	cltd
	imull	%ecx
	movl	%eax, %edx
	movl	%r15d, %eax
	movl	%ecx, %r15d
	subl	%edx, %r15d
	movl	%r15d, %eax
	movl	%eax, -4(%rbp)
	movl	%ecx, -16(%rbp)
	movl	$10, %eax
	movl	%eax, -8(%rbp)
	addl	%ebx, %eax
	movl	%eax, -4(%rbp)
	movl	%eax, -16(%rbp)
	movl	$40, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
