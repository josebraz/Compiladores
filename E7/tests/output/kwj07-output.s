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
	movl	$2, %eax
	movl	%eax, -8(%rbp)
	movl	$3, %ebx
	movl	%ebx, -12(%rbp)
	movl	%edx, %r14d
	cltd
	imull	%ebx
	movl	%r14d, %edx
	movl	%eax, %ecx
	movl	%r15d, %eax
	movl	%ecx, -4(%rbp)
	movl	%eax, %r15d
	movl	%ecx, %eax
	movl	%edx, %r14d
	cltd
	imull	%ebx
	movl	%r14d, %edx
	movl	%eax, -8(%rbp)
	movl	%eax, %r15d
	movl	%ecx, %eax
	movl	%edx, %r14d
	cltd
	imull	%eax
	movl	%r14d, %edx
	movl	%eax, %ebx
	movl	%r15d, %eax
	movl	%ebx, -12(%rbp)
	movl	%ebx, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
