ORIGINAL
// MARK: INIT CODE START, p1 = 0, p2 = 0
loadI 1024 => rfp
loadI 1024 => rsp
loadI 29 => rbss
L0:
// MARK: INIT CODE END, p1 = 0, p2 = 0
// MARK: FUN START, p1 = 0, p2 = 0
L0:                           // Declaração da função main
i2i rsp => rfp
addI rsp, 52 => rsp
// MARK: SAVE REGS START, p1 = 0, p2 = 0// Salva o estado dos registradores usados na função
storeAI r0 => rfp, 28
storeAI r1 => rfp, 32
storeAI r2 => rfp, 36
storeAI r3 => rfp, 40
storeAI r4 => rfp, 44
storeAI r5 => rfp, 48
// MARK: SAVE REGS END, p1 = 0, p2 = 0
loadAI rfp, 16 => r0          // Carrega variável a
loadAI rfp, 20 => r1          // Carrega variável b
add r0, r1 => r2
loadI 100 => r3
add r2, r3 => r4
storeAI r4 => rfp, 24         // Grava variável c
// MARK: LOAD REGS START, p1 = 0, p2 = 0// Restaura o estado dos registradores usados
loadAI rfp, 28 => r0
loadAI rfp, 32 => r1
loadAI rfp, 36 => r2
loadAI rfp, 40 => r3
loadAI rfp, 44 => r4
loadAI rfp, 48 => r5
// MARK: LOAD REGS END, p1 = 0, p2 = 0
loadAI rfp, 24 => r5          // Início do retorno
storeAI r5 => rfp, 12         // Escreve o valor de retorno na pilha
halt                          // Termina o programa
// MARK: FUN END, p1 = 0, p2 = 0
REMOVE MARKS
// MARK: FUN START, p1 = 0, p2 = 0
L0:                           // Declaração da função main
i2i rsp => rfp
addI rsp, 52 => rsp
loadAI rfp, 16 => r0          // Carrega variável a
loadAI rfp, 20 => r1          // Carrega variável b
add r0, r1 => r2
loadI 100 => r3
add r2, r3 => r4
storeAI r4 => rfp, 24         // Grava variável c
loadAI rfp, 24 => r5          // Início do retorno
storeAI r5 => rfp, 12         // Escreve o valor de retorno na pilha
halt                          // Termina o programa
// MARK: FUN END, p1 = 0, p2 = 0
	 0	1	2	3	4	5	
0	[1	]
1	[1	1	]
2	[0	0	1	]
3	[0	0	1	1	]
4	[0	0	0	0	1	]
5	[0	0	0	0	0	1	]
CORES:
0 - 0
1 - 1
2 - 0
3 - 1
4 - 0
5 - 0

OPTIMIZE REGS
// MARK: FUN START, p1 = 0, p2 = 0
L0:                           // Declaração da função main
i2i rsp => rfp
addI rsp, 52 => rsp
loadAI rfp, 16 => r0          // Carrega variável a
loadAI rfp, 20 => r1          // Carrega variável b
add r0, r1 => r0
loadI 100 => r1
add r0, r1 => r0
storeAI r0 => rfp, 24         // Grava variável c
loadAI rfp, 24 => r0          // Início do retorno
storeAI r0 => rfp, 12         // Escreve o valor de retorno na pilha
halt                          // Termina o programa
// MARK: FUN END, p1 = 0, p2 = 0

Assembly:
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
	movl	-16(%rbp), %rax
	movl	-20(%rbp), %rbx
	addl	%rbx, %rax
	movl	$100, %rbx
	addl	%rbx, %rax
	movl	%rax, -24(%rbp)
	movl	-24(%rbp), %rax
	movl	%rax, -12(%rbp)
 -----------> Não rolou de imprimir: halt                          // Termina o programa
.LFE0:
	.size	main, .-main
