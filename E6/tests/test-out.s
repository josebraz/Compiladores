
 # ------- ILOC CODE ---------- 
#// MARK: CODE_MARK_INIT_CODE_START, p1 = 0, p2 = 0
#loadI 1024 => rfp
#loadI 1024 => rsp
#loadI 10 => rbss
#jumpI => L0
#// MARK: CODE_MARK_INIT_CODE_END, p1 = 0, p2 = 0
#// MARK: CODE_MARK_FUN_START, p1 = 0, p2 = 0
#L0:                           // Declaração da função main
#i2i rsp => rfp
#// MARK: CODE_MARK_FUN_RET_START, p1 = 0, p2 = 0
#loadI 10 => r0                // Início do retorno
#// MARK: CODE_MARK_FUN_RETURN_VALUE_START, p1 = 0, p2 = 0
#storeAI r0 => rfp, 12         // Escreve o valor de retorno na pilha
#// MARK: CODE_MARK_FUN_RETURN_VALUE_END, p1 = 0, p2 = 0
#halt                          // Termina o programa
#// MARK: CODE_MARK_FUN_RET_END, p1 = 0, p2 = 0
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
	movl	$10, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
