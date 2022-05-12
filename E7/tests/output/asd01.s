#ORIGINAL
#// MARK: CODE_MARK_FUN_START, p1 = 0, p2 = 0
#L0:                           // Declaração da função main
#i2i rsp => rfp
#loadI 4 => r1
#loadI 2 => r2
#div r1, r2 => r3
#loadI 2 => r0
#add r0, r3 => r4
#loadI 4 => r5
#loadI 4 => r6
#mult r5, r6 => r7
#add r4, r7 => r8
#storeAI r8 => rfp, 16         // Grava variável a
#loadAI rfp, 16 => r9          // Início do retorno
#// MARK: CODE_MARK_FUN_RETURN_VALUE_START, p1 = 0, p2 = 0
#storeAI r9 => rfp, 12         // Escreve o valor de retorno na pilha
#// MARK: CODE_MARK_FUN_RETURN_VALUE_END, p1 = 0, p2 = 0
#halt                          // Termina o programa
#// MARK: CODE_MARK_FUN_END, p1 = 0, p2 = 0
#OPTMIZED
#// MARK: CODE_MARK_FUN_START, p1 = 0, p2 = 0
#L0:                           // Declaração da função main
#i2i rsp => rfp
#loadI 20 => r0
#storeAI r0 => rfp, 16         // Grava variável a
#// MARK: CODE_MARK_FUN_RETURN_VALUE_START, p1 = 0, p2 = 0
#storeAI r0 => rfp, 12         // Escreve o valor de retorno na pilha
#// MARK: CODE_MARK_FUN_RETURN_VALUE_END, p1 = 0, p2 = 0
#halt                          // Termina o programa
#// MARK: CODE_MARK_FUN_END, p1 = 0, p2 = 0
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
	movl	$20, %eax
	movl	%eax, -4(%rbp)
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
