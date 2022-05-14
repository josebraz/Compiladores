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
	movl	$1, -4(%rbp)
	movl	$0, -8(%rbp)
	movl	$2, -12(%rbp)
	movl	$3, -16(%rbp)
	movl	-4(%rbp), %eax
	movl	-8(%rbp), %ebx
	cmpl	%ebx, %eax
	jge  	.L4
.L1:
	movl	-12(%rbp), %eax
	movl	-16(%rbp), %ebx
	cmpl	%ebx, %eax
	jge  	.L4
.L2:
	movl	$2, -20(%rbp)
	jmp 	.L3
.L4:
	movl	$3, -20(%rbp)
.L3:
	movl	-20(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
