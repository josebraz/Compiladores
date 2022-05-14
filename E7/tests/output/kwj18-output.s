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
	movl	$10, %ebx
	movl	%ebx, -4(%rbp)
	movl	$0, %ecx
	movl	%ecx, -8(%rbp)
	movl	$2, %eax
	movl	%eax, -12(%rbp)
.L2:
	cmpl	$2, %eax
	jne  	.L4
.L1:
	cmpl	$5, %ebx
	jle  	.L4
.L3:
	subl	$1, %ebx
	movl	%ebx, -4(%rbp)
	addl	$1, %ecx
	movl	%ecx, -8(%rbp)
	jmp 	.L2
.L4:
	movl	%ecx, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
