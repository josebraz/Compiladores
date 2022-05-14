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
	movl	$1, %eax
	movl	%eax, -4(%rbp)
	movl	$0, %ebx
	movl	%ebx, -8(%rbp)
	movl	$2, %ecx
	movl	%ecx, -12(%rbp)
	movl	$3, %edx
	movl	%edx, -16(%rbp)
	cmpl	%ebx, %eax
	jge  	.L4
.L1:
	cmpl	%edx, %ecx
	jge  	.L4
.L2:
	movl	$2, -20(%rbp)
	jmp 	.L3
.L4:
	movl	$3, %eax
	movl	%eax, -20(%rbp)
.L3:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
