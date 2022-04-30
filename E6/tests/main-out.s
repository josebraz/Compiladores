ORIGINAL
// MARK: CODE_MARK_INIT_CODE_START, p1 = 0, p2 = 0
loadI 1024 => rfp
loadI 1024 => rsp
loadI 57 => rbss
jumpI => L1
// MARK: CODE_MARK_INIT_CODE_END, p1 = 0, p2 = 0
// MARK: CODE_MARK_FUN_START, p1 = 0, p2 = 0
L0:                           // Declaração da função fn
i2i rsp => rfp
addI rsp, 40 => rsp
// MARK: CODE_MARK_SAVE_REGS_START, p1 = 0, p2 = 0// Salva o estado dos registradores usados na função
storeAI r0 => rfp, 16
storeAI r1 => rfp, 20
storeAI rsp => rfp, 24
storeAI r2 => rfp, 28
storeAI rfp => rfp, 32
storeAI r3 => rfp, 36
// MARK: CODE_MARK_SAVE_REGS_END, p1 = 0, p2 = 0
// MARK: CODE_MARK_FUN_RET_START, p1 = 0, p2 = 0
loadI 10 => r0                // Início do retorno
storeAI r0 => rfp, 12         // Escreve o valor de retorno na pilha
// MARK: CODE_MARK_LOAD_REGS_START, p1 = 0, p2 = 0// Restaura o estado dos registradores usados
loadAI rfp, 16 => r0
loadAI rfp, 20 => r1
loadAI rfp, 24 => rsp
loadAI rfp, 28 => r2
loadAI rfp, 32 => rfp
loadAI rfp, 36 => r3
// MARK: CODE_MARK_LOAD_REGS_END p1 = 0, p2 = 0
loadAI rfp, 4 => r1           // Carrega ultimo RSP
i2i r1 => rsp
loadAI rfp, 8 => r2           // Carrega ultimo RFP
i2i r2 => rfp
loadAI rfp, 0 => r3           // Carrega end de retorno
jump => r3
// MARK: CODE_MARK_FUN_RET_END, p1 = 0, p2 = 0
// MARK: CODE_MARK_FUN_END, p1 = 0, p2 = 0
// MARK: CODE_MARK_FUN_START, p1 = 0, p2 = 0
L1:                           // Declaração da função main
i2i rsp => rfp
addI rsp, 56 => rsp
// MARK: CODE_MARK_SAVE_REGS_START, p1 = 0, p2 = 0// Salva o estado dos registradores usados na função
storeAI r4 => rfp, 28
storeAI r5 => rfp, 32
storeAI r6 => rfp, 36
storeAI r7 => rfp, 40
storeAI r8 => rfp, 44
storeAI r9 => rfp, 48
storeAI r10 => rfp, 52
// MARK: CODE_MARK_SAVE_REGS_END, p1 = 0, p2 = 0
loadI 100 => r4
storeAI r4 => rfp, 24         // Grava variável c
// MARK: CODE_MARK_FUN_RET_START, p1 = 0, p2 = 0
// MARK: CODE_MARK_LOAD_REGS_START, p1 = 0, p2 = 0// Restaura o estado dos registradores usados
loadAI rfp, 28 => r4
loadAI rfp, 32 => r5
loadAI rfp, 36 => r6
loadAI rfp, 40 => r7
loadAI rfp, 44 => r8
loadAI rfp, 48 => r9
loadAI rfp, 52 => r10
// MARK: CODE_MARK_LOAD_REGS_END p1 = 0, p2 = 0
loadAI rfp, 24 => r5          // Início do retorno
loadI 5 => r6
add r5, r6 => r7
// MARK: CODE_MARK_FUN_CALL_START, p1 = 0, p2 = 0
storeAI rsp => rsp, 4         // Inicio da chamada de fn()
storeAI rfp => rsp, 8
// MARK: FUN CALL JUMP, p1 = 0, p2 = 0
addI rpc, 3 => r8
storeAI r8 => rsp, 0
jumpI => L0                   // Salta para a função fn()
loadAI rsp, 12 => r9          // Carrega o valor de retorno de fn()
// MARK: CODE_MARK_FUN_CALL_END, p1 = 0, p2 = 0
add r7, r9 => r10
// MARK: CODE_MARK_FUN_RETURN_VALUE, p1 = 0, p2 = 0
storeAI r10 => rfp, 12        // Escreve o valor de retorno na pilha
halt                          // Termina o programa
// MARK: CODE_MARK_FUN_RET_END, p1 = 0, p2 = 0
// MARK: CODE_MARK_FUN_END, p1 = 0, p2 = 0
REMOVE MARKS
// MARK: CODE_MARK_FUN_START, p1 = 0, p2 = 0
L0:                           // Declaração da função fn
i2i rsp => rfp
addI rsp, 40 => rsp
// MARK: CODE_MARK_FUN_RET_START, p1 = 0, p2 = 0
loadI 10 => r0                // Início do retorno
storeAI r0 => rfp, 12         // Escreve o valor de retorno na pilha
loadAI rfp, 4 => r1           // Carrega ultimo RSP
i2i r1 => rsp
loadAI rfp, 8 => r2           // Carrega ultimo RFP
i2i r2 => rfp
loadAI rfp, 0 => r3           // Carrega end de retorno
jump => r3
// MARK: CODE_MARK_FUN_RET_END, p1 = 0, p2 = 0
// MARK: CODE_MARK_FUN_END, p1 = 0, p2 = 0
// MARK: CODE_MARK_FUN_START, p1 = 0, p2 = 0
L1:                           // Declaração da função main
i2i rsp => rfp
addI rsp, 56 => rsp
loadI 100 => r4
storeAI r4 => rfp, 24         // Grava variável c
// MARK: CODE_MARK_FUN_RET_START, p1 = 0, p2 = 0
loadAI rfp, 24 => r5          // Início do retorno
loadI 5 => r6
add r5, r6 => r7
// MARK: CODE_MARK_FUN_CALL_START, p1 = 0, p2 = 0
storeAI rsp => rsp, 4         // Inicio da chamada de fn()
storeAI rfp => rsp, 8
// MARK: FUN CALL JUMP, p1 = 0, p2 = 0
addI rpc, 3 => r8
storeAI r8 => rsp, 0
jumpI => L0                   // Salta para a função fn()
loadAI rsp, 12 => r9          // Carrega o valor de retorno de fn()
// MARK: CODE_MARK_FUN_CALL_END, p1 = 0, p2 = 0
add r7, r9 => r10
// MARK: CODE_MARK_FUN_RETURN_VALUE, p1 = 0, p2 = 0
storeAI r10 => rfp, 12        // Escreve o valor de retorno na pilha
halt                          // Termina o programa
// MARK: CODE_MARK_FUN_RET_END, p1 = 0, p2 = 0
// MARK: CODE_MARK_FUN_END, p1 = 0, p2 = 0
	 0	1	2	3	4	5	6	7	8	9	10	
0	[1	]
1	[0	0	]
2	[0	0	0	]
3	[0	0	0	0	]
4	[0	0	0	0	1	]
5	[0	0	0	0	0	1	]
6	[0	0	0	0	0	1	1	]
7	[0	0	0	0	0	0	0	1	]
8	[0	0	0	0	0	0	0	0	0	]
9	[0	0	0	0	0	0	0	1	0	1	]
10	[0	0	0	0	0	0	0	0	0	0	1	]
CORES:
0 - 0
1 - 0
2 - 0
3 - 0
4 - 0
5 - 0
6 - 1
7 - 0
8 - 0
9 - 1
10 - 0

OPTIMIZE REGS
// MARK: CODE_MARK_FUN_START, p1 = 0, p2 = 0
L0:                           // Declaração da função fn
i2i rsp => rfp
addI rsp, 40 => rsp
// MARK: CODE_MARK_FUN_RET_START, p1 = 0, p2 = 0
loadI 10 => r0                // Início do retorno
storeAI r0 => rfp, 12         // Escreve o valor de retorno na pilha
loadAI rfp, 4 => r0           // Carrega ultimo RSP
i2i r0 => rsp
loadAI rfp, 8 => r0           // Carrega ultimo RFP
i2i r0 => rfp
loadAI rfp, 0 => r0           // Carrega end de retorno
jump => r0
// MARK: CODE_MARK_FUN_RET_END, p1 = 0, p2 = 0
// MARK: CODE_MARK_FUN_END, p1 = 0, p2 = 0
// MARK: CODE_MARK_FUN_START, p1 = 0, p2 = 0
L1:                           // Declaração da função main
i2i rsp => rfp
addI rsp, 56 => rsp
loadI 100 => r0
storeAI r0 => rfp, 24         // Grava variável c
// MARK: CODE_MARK_FUN_RET_START, p1 = 0, p2 = 0
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

Assembly:
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
 -----------> Não rolou de imprimir: // MARK: CODE_MARK_FUN_RET_START, p1 = 0, p2 = 0
	movl	$10, %rax
	movl	%rax, -12(%rbp)
	movl	-4(%rbp), %rax
	movl	%rax, %rsp
	movl	-8(%rbp), %rax
	movl	%rax, %rbp
	movl	-0(%rbp), %rax
 -----------> Não rolou de imprimir: jump => r0
 -----------> Não rolou de imprimir: // MARK: CODE_MARK_FUN_RET_END, p1 = 0, p2 = 0
.LFE0:
	.size	fn, .-fn
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
	movl	$100, %rax
	movl	%rax, -24(%rbp)
 -----------> Não rolou de imprimir: // MARK: CODE_MARK_FUN_RET_START, p1 = 0, p2 = 0
	movl	-24(%rbp), %rax
	addl	$5, %rax
	movl	%rsp, -4(%rsp)
	movl	%rbp, -8(%rsp)
	call	fn
	movl	-12(%rsp), %rbx
 -----------> Não rolou de imprimir: // MARK: CODE_MARK_FUN_CALL_END, p1 = 0, p2 = 0
	addl	%rbx, %rax
	movl	%rax, %eax
	leave
	.cfi_def_cfa 7, 8 
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
