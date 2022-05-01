	.comm	int_global,4,4
	.comm	segundo_global,4,4
	.globl	fn
	.type	fn, @function
fn:
LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	addq	$20, %rsp
	# Não rolou de imprimir: # MARK: CODE_MARK_SAVE_REGS_START, p1 = 0, p2 = 0// Salva o estado dos registradores usados na função
	movq	%rax, -16(%rbp)
	# Não rolou de imprimir: # MARK: CODE_MARK_SAVE_REGS_END, p1 = 0, p2 = 0
	# Não rolou de imprimir: # MARK: CODE_MARK_FUN_RET_START, p1 = 0, p2 = 0
	movq	$10, %rax
	movq	%rax, %eax
	leave
	.cfi_def_cfa 7, 8 
	ret
	.cfi_endproc
	# Não rolou de imprimir: # MARK: CODE_MARK_LOAD_REGS_END p1 = 0, p2 = 0
	movq	-4(%rbp), %rax
	movq	%rax, %rsp
	movq	-8(%rbp), %rax
	movq	%rax, %rbp
	movq	-0(%rbp), %rax
	# Não rolou de imprimir: jump => r0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	fn, .-fn
	.globl	foo
	.type	foo, @function
foo:
LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	addq	$28, %rsp
	# Não rolou de imprimir: # MARK: CODE_MARK_SAVE_REGS_START, p1 = 0, p2 = 0// Salva o estado dos registradores usados na função
	movq	%rax, -20(%rbp)
	movq	%rbx, -24(%rbp)
	# Não rolou de imprimir: # MARK: CODE_MARK_SAVE_REGS_END, p1 = 0, p2 = 0
	movq	$-1, %rax
	movq	%rax, -16(%rbp)
	# Não rolou de imprimir: # MARK: CODE_MARK_FUN_RET_START, p1 = 0, p2 = 0
	# Não rolou de imprimir: # MARK: CODE_MARK_LOAD_REGS_START, p1 = 0, p2 = 0// Restaura o estado dos registradores usados
	movq	-20(%rbp), %rax
	movq	-24(%rbp), %rbx
	# Não rolou de imprimir: # MARK: CODE_MARK_LOAD_REGS_END p1 = 0, p2 = 0
	movq	-16(%rbp), %rbx
	movq	%rbx, %r15
	addq	$20, %r15
	movq	%r15, %rax
	movq	%rax, %eax
	leave
	.cfi_def_cfa 7, 8 
	ret
	.cfi_endproc
	movq	-8(%rbp), %rax
	movq	%rax, %rbp
	movq	-0(%rbp), %rax
	# Não rolou de imprimir: jump => r0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	foo, .-foo
	.globl	main
	.type	main, @function
main:
LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	addq	$32, %rsp
	# Não rolou de imprimir: # MARK: CODE_MARK_SAVE_REGS_START, p1 = 0, p2 = 0// Salva o estado dos registradores usados na função
	movq	%rax, -24(%rbp)
	movq	%rbx, -28(%rbp)
	# Não rolou de imprimir: # MARK: CODE_MARK_SAVE_REGS_END, p1 = 0, p2 = 0
	movq	$-10, %rax
	movq	%rax, -16(%rbp)
	movq	$-20, %rax
	movq	%rax, -20(%rbp)
	# Não rolou de imprimir: # MARK: CODE_MARK_FUN_RET_START, p1 = 0, p2 = 0
	# Não rolou de imprimir: # MARK: CODE_MARK_LOAD_REGS_START, p1 = 0, p2 = 0// Restaura o estado dos registradores usados
	movq	-24(%rbp), %rax
	movq	-28(%rbp), %rbx
	# Não rolou de imprimir: # MARK: CODE_MARK_LOAD_REGS_END p1 = 0, p2 = 0
	movq	-20(%rbp), %rbx
	movq	%rbx, %r15
	addq	$100, %r15
	movq	%r15, %rax
	movq	%rsp, -4(%rsp)
	movq	%rbp, -8(%rsp)
	call	fn
	movq	-12(%rsp), %rbx
	# Não rolou de imprimir: # MARK: CODE_MARK_FUN_CALL_END, p1 = 0, p2 = 0
	addq	%rbx, %rax
	movq	%rax, %eax
	leave
	.cfi_def_cfa 7, 8 
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
