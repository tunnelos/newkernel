.section .text
.global __avx_init
.type __avx_init, @function

.intel_syntax noprefix


__avx_init:
    push eax
    push ecx
    push edx
    xor ecx, ecx
    xgetbv 
    or eax, 7
    xsetbv
    pop edx
    pop ecx
    pop eax
    ret
