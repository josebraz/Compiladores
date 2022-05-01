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
	subq	$48, %rsp
	movl	%eax, -28(%rbp)
	movl	%ebx, -32(%rbp)
	movl	$10, %eax
	movl	%eax, -16(%rbp)
	movl	$20, %eax
	movl	%eax, -20(%rbp)
	movl	$30, %eax
	movl	%eax, -24(%rbp)
	# Não rolou de imprimir: // MARK: CODE_MARK_FUN_RET_START, p1 = 0, p2 = 0
	movl	-16(%rbp), %eax
	movl	-20(%rbp), %ebx
	addl	%ebx, %eax
	movl	-24(%rbp), %ebx
	addl	%ebx, %eax
	leave
	.cfi_def_cfa 7, 8 
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
