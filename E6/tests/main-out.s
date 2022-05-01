
 ------- ILOC CODE ---------- 
// MARK: CODE_MARK_INIT_CODE_START, p1 = 0, p2 = 0
loadI 1024 => rfp
loadI 1024 => rsp
loadI 49 => rbss
jumpI => L2
// MARK: CODE_MARK_INIT_CODE_END, p1 = 0, p2 = 0
// MARK: CODE_MARK_FUN_START, p1 = 0, p2 = 0
L0:                           // Declaração da função fn
i2i rsp => rfp
addI rsp, 20 => rsp
// MARK: CODE_MARK_SAVE_REGS_START, p1 = 0, p2 = 0// Salva o estado dos registradores usados na função
storeAI r0 => rfp, 16
// MARK: CODE_MARK_SAVE_REGS_END, p1 = 0, p2 = 0
// MARK: CODE_MARK_FUN_RET_START, p1 = 0, p2 = 0
loadI 10 => r0                // Início do retorno
// MARK: CODE_MARK_FUN_RETURN_VALUE, p1 = 0, p2 = 0
storeAI r0 => rfp, 12         // Escreve o valor de retorno na pilha
// MARK: CODE_MARK_LOAD_REGS_START, p1 = 0, p2 = 0// Restaura o estado dos registradores usados
loadAI rfp, 16 => r0
// MARK: CODE_MARK_LOAD_REGS_END p1 = 0, p2 = 0
loadAI rfp, 4 => r0           // Carrega ultimo RSP
i2i r0 => rsp
loadAI rfp, 8 => r0           // Carrega ultimo RFP
i2i r0 => rfp
loadAI rfp, 0 => r0           // Carrega end de retorno
jump => r0
// MARK: CODE_MARK_FUN_RET_END, p1 = 0, p2 = 0
// MARK: CODE_MARK_FUN_END, p1 = 0, p2 = 0
// MARK: CODE_MARK_FUN_START, p1 = 0, p2 = 0
L1:                           // Declaração da função foo
i2i rsp => rfp
addI rsp, 20 => rsp
// MARK: CODE_MARK_SAVE_REGS_START, p1 = 0, p2 = 0// Salva o estado dos registradores usados na função
storeAI r0 => rfp, 16
// MARK: CODE_MARK_SAVE_REGS_END, p1 = 0, p2 = 0
// MARK: CODE_MARK_FUN_RET_START, p1 = 0, p2 = 0
loadI 20 => r0                // Início do retorno
// MARK: CODE_MARK_FUN_RETURN_VALUE, p1 = 0, p2 = 0
storeAI r0 => rfp, 12         // Escreve o valor de retorno na pilha
// MARK: CODE_MARK_LOAD_REGS_START, p1 = 0, p2 = 0// Restaura o estado dos registradores usados
loadAI rfp, 16 => r0
// MARK: CODE_MARK_LOAD_REGS_END p1 = 0, p2 = 0
loadAI rfp, 4 => r0           // Carrega ultimo RSP
i2i r0 => rsp
loadAI rfp, 8 => r0           // Carrega ultimo RFP
i2i r0 => rfp
loadAI rfp, 0 => r0           // Carrega end de retorno
jump => r0
// MARK: CODE_MARK_FUN_RET_END, p1 = 0, p2 = 0
// MARK: CODE_MARK_FUN_END, p1 = 0, p2 = 0
// MARK: CODE_MARK_FUN_START, p1 = 0, p2 = 0
L2:                           // Declaração da função main
i2i rsp => rfp
addI rsp, 36 => rsp
// MARK: CODE_MARK_SAVE_REGS_START, p1 = 0, p2 = 0// Salva o estado dos registradores usados na função
storeAI r0 => rfp, 28
storeAI r1 => rfp, 32
// MARK: CODE_MARK_SAVE_REGS_END, p1 = 0, p2 = 0
loadI 100 => r0
storeAI r0 => rfp, 24         // Grava variável c
// MARK: CODE_MARK_FUN_RET_START, p1 = 0, p2 = 0
// MARK: CODE_MARK_LOAD_REGS_START, p1 = 0, p2 = 0// Restaura o estado dos registradores usados
loadAI rfp, 28 => r0
loadAI rfp, 32 => r1
// MARK: CODE_MARK_LOAD_REGS_END p1 = 0, p2 = 0
loadAI rfp, 24 => r0          // Início do retorno
loadI 5 => r1
add r0, r1 => r0
// MARK: CODE_MARK_FUN_CALL_START, p1 = 0, p2 = 0
storeAI rsp => rsp, 4         // Inicio da chamada de fn()
storeAI rfp => rsp, 8
// MARK: FUN CALL JUMP, p1 = 0, p2 = 0
addI rpc, 3 => r0
storeAI r0 => rsp, 0
jumpI => L0                   // Salta para a função fn()
loadAI rsp, 12 => r1          // Carrega o valor de retorno de fn()
// MARK: CODE_MARK_FUN_CALL_END, p1 = 0, p2 = 0
add r0, r1 => r0
// MARK: CODE_MARK_FUN_RETURN_VALUE, p1 = 0, p2 = 0
storeAI r0 => rfp, 12         // Escreve o valor de retorno na pilha
halt                          // Termina o programa
// MARK: CODE_MARK_FUN_RET_END, p1 = 0, p2 = 0
// MARK: CODE_MARK_FUN_END, p1 = 0, p2 = 0


 ------- ASSEMBLY CODE ----------
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
	addl	$20, %rsp
	##### Não rolou de imprimir: // MARK: CODE_MARK_SAVE_REGS_START, p1 = 0, p2 = 0// Salva o estado dos registradores usados na função
	movl	%rax, -16(%rbp)
	##### Não rolou de imprimir: // MARK: CODE_MARK_SAVE_REGS_END, p1 = 0, p2 = 0
	##### Não rolou de imprimir: // MARK: CODE_MARK_FUN_RET_START, p1 = 0, p2 = 0
	movl	$10, %rax
	movl	%rax, %eax
	leave
	.cfi_def_cfa 7, 8 
	ret
	.cfi_endproc
	##### Não rolou de imprimir: // MARK: CODE_MARK_LOAD_REGS_END p1 = 0, p2 = 0
	movl	-4(%rbp), %rax
	movl	%rax, %rsp
	movl	-8(%rbp), %rax
	movl	%rax, %rbp
	movl	-0(%rbp), %rax
	##### Não rolou de imprimir: jump => r0
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
	addl	$20, %rsp
	##### Não rolou de imprimir: // MARK: CODE_MARK_SAVE_REGS_START, p1 = 0, p2 = 0// Salva o estado dos registradores usados na função
	movl	%rax, -16(%rbp)
	##### Não rolou de imprimir: // MARK: CODE_MARK_SAVE_REGS_END, p1 = 0, p2 = 0
	##### Não rolou de imprimir: // MARK: CODE_MARK_FUN_RET_START, p1 = 0, p2 = 0
	movl	$20, %rax
	movl	%rax, %eax
	leave
	.cfi_def_cfa 7, 8 
	ret
	.cfi_endproc
	##### Não rolou de imprimir: // MARK: CODE_MARK_LOAD_REGS_END p1 = 0, p2 = 0
	movl	-4(%rbp), %rax
	movl	%rax, %rsp
	movl	-8(%rbp), %rax
	movl	%rax, %rbp
	movl	-0(%rbp), %rax
	##### Não rolou de imprimir: jump => r0
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
	addl	$36, %rsp
	##### Não rolou de imprimir: // MARK: CODE_MARK_SAVE_REGS_START, p1 = 0, p2 = 0// Salva o estado dos registradores usados na função
	movl	%rax, -28(%rbp)
	movl	%rbx, -32(%rbp)
	##### Não rolou de imprimir: // MARK: CODE_MARK_SAVE_REGS_END, p1 = 0, p2 = 0
	movl	$100, %rax
	movl	%rax, -24(%rbp)
	##### Não rolou de imprimir: // MARK: CODE_MARK_FUN_RET_START, p1 = 0, p2 = 0
	##### Não rolou de imprimir: // MARK: CODE_MARK_LOAD_REGS_START, p1 = 0, p2 = 0// Restaura o estado dos registradores usados
	movl	-28(%rbp), %rax
	movl	-32(%rbp), %rbx
	##### Não rolou de imprimir: // MARK: CODE_MARK_LOAD_REGS_END p1 = 0, p2 = 0
	movl	-24(%rbp), %rax
	addl	$5, %rax
	movl	%rsp, -4(%rsp)
	movl	%rbp, -8(%rsp)
	call	fn
	movl	-12(%rsp), %rbx
	##### Não rolou de imprimir: // MARK: CODE_MARK_FUN_CALL_END, p1 = 0, p2 = 0
	addl	%rbx, %rax
	movl	%rax, %eax
	leave
	.cfi_def_cfa 7, 8 
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
