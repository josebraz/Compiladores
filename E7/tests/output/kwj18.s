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
	movl	$0, -8(%rbp)
	movl	$2, -12(%rbp)
.L2:
	movl	-12(%rbp), %eax
	cmpl	$2, %eax
	jne  	.L4
.L1:
	movl	-4(%rbp), %eax
	cmpl	$5, %eax
	jle  	.L4
.L3:
	movl	-4(%rbp), %eax
	subl	$1, %eax
	movl	%eax, -4(%rbp)
	movl	-8(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -8(%rbp)
	jmp 	.L2
.L4:
	movl	-8(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
