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
	movl	$0, %eax
	movl	%eax, -4(%rbp)
	movl	$1, %ebx
	movl	%ebx, -8(%rbp)
	movl	$2, %ecx
	movl	%ecx, -12(%rbp)
	movl	$3, %edx
	movl	%edx, -16(%rbp)
	movl	$5, -20(%rbp)
	cmpl	%ebx, %eax
	jl   	.L2
.L1:
	cmpl	%edx, %ecx
	jge  	.L3
.L2:
	movl	$2, %r8d
	movl	%r8d, -20(%rbp)
.L3:
	movl	%r8d, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
