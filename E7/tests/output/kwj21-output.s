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
	movl	$-3, %ebx
	movl	%ebx, -4(%rbp)
	movl	$2, -8(%rbp)
	cmpl	$0, %ebx
	jle  	.L3
.L1:
	movl	$3, -8(%rbp)
	jmp 	.L2
.L3:
	movl	$4, %eax
	movl	%eax, -8(%rbp)
.L2:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
