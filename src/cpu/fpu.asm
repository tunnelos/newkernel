.section .text
.global __fpu_init
.type __fpu_init, @function

.intel_syntax noprefix

__fpu_init:
    mov edx, cr0
    and edx, (-1) - 12
    mov cr0, edx
    fninit
    ret
