	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 15	sdk_version 10, 15
	.globl	_main                   ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$4032, %rsp             ## imm = 0xFC0
	movq	___stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rax
	movq	%rax, -8(%rbp)
	movl	$0, -4020(%rbp)
	movl	$0, -4024(%rbp)
LBB0_1:                                 ## =>This Inner Loop Header: Depth=1
	cmpl	$1000, -4024(%rbp)      ## imm = 0x3E8
	jge	LBB0_4
## %bb.2:                               ##   in Loop: Header=BB0_1 Depth=1
	movslq	-4024(%rbp), %rax
	movl	$0, -4016(%rbp,%rax,4)
## %bb.3:                               ##   in Loop: Header=BB0_1 Depth=1
	movl	-4024(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -4024(%rbp)
	jmp	LBB0_1
LBB0_4:
	movl	-4020(%rbp), %eax
	movq	___stack_chk_guard@GOTPCREL(%rip), %rcx
	movq	(%rcx), %rcx
	movq	-8(%rbp), %rdx
	cmpq	%rdx, %rcx
	movl	%eax, -4028(%rbp)       ## 4-byte Spill
	jne	LBB0_6
## %bb.5:                               ## %SP_return
	movl	-4028(%rbp), %eax       ## 4-byte Reload
	addq	$4032, %rsp             ## imm = 0xFC0
	popq	%rbp
	retq
LBB0_6:                                 ## %CallStackCheckFailBlk
	callq	___stack_chk_fail
	ud2
	.cfi_endproc
                                        ## -- End function

.subsections_via_symbols
