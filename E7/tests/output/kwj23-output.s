	.comm	c,4,4
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
	movl	$0, %ebx
	movl	%ebx, -8(%rbp)
	movl	$0, %ecx
	movl	%ecx, -4(%rbp)
.L1:
	cmpl	$24, %ecx
	jge  	.L3
.L2:
	addl	$1, %ebx
	movl	%ebx, -8(%rbp)
	addl	%ecx, %ebx
	movl	%ebx, c(%rip)
	addl	$2, %ecx
	movl	%ecx, -4(%rbp)
	jmp 	.L1
.L3:
	movl	%ebx, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main