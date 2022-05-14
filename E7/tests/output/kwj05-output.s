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
	movl	$14, %eax
	movl	%eax, -8(%rbp)
	movl	$16, %ebx
	movl	%ebx, -12(%rbp)
	movl	%ebx, %r15d
	subl	%eax, %r15d
	movl	%r15d, %ecx
	movl	%ecx, -4(%rbp)
	movl	%ebx, %r15d
	subl	%ecx, %r15d
	movl	%r15d, %eax
	movl	%eax, -8(%rbp)
	movl	%eax, %r15d
	subl	%ecx, %r15d
	movl	%r15d, %ebx
	movl	%ebx, -12(%rbp)
	movl	%ebx, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
