.code32

.section .init
.global _init
.type _init, @function

_init:
    push %ebp
    movl %esp, %ebp

.section .fini
.global fini
.type _fini, @function

_fini:
    push %ebp
    movl %esp, %ebp
