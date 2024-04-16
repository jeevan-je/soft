	.file	"source_code.c"
	.text
	.p2align 4,,15
	.globl	_fact
	.def	_fact;	.scl	2;	.type	32;	.endef
_fact:
LFB12:
	.cfi_startproc
	movl	4(%esp), %edx
	movl	$1, %eax
	cmpl	$1, %edx
	jle	L4
	.p2align 4,,10
L3:
	imull	%edx, %eax
	subl	$1, %edx
	jne	L3
	rep ret
	.p2align 4,,10
L4:
	rep ret
	.cfi_endproc
LFE12:
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
LC0:
	.ascii "%d\0"
	.section	.text.startup,"x"
	.p2align 4,,15
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
LFB13:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	andl	$-16, %esp
	subl	$16, %esp
	call	___main
	movl	$1, %edx
	movl	$7, %eax
	.p2align 4,,10
L8:
	imull	%eax, %edx
	subl	$1, %eax
	jne	L8
	movl	%edx, 4(%esp)
	movl	$LC0, (%esp)
	call	_printf
	xorl	%eax, %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE13:
	.ident	"GCC: (MinGW.org GCC-6.3.0-1) 6.3.0"
	.def	_printf;	.scl	2;	.type	32;	.endef
