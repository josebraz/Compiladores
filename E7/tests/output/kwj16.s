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
	movl	$2, -8(%rbp)
	movl	-4(%rbp), %eax
	cmpl	$0, %eax
	jle  	.L3
.L1:
	movl	$3, -8(%rbp)
	jmp 	.L2
.L3:
	movl	$4, -8(%rbp)
.L2:
	movl	-8(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
