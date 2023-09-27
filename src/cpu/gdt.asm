.section .text
.global __gdt_load
.type __gdt_load, @function
.type __gdt_return, @function

.intel_syntax noprefix

__gdt_load:
    lgdt [eax]
    ret
