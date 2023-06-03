.section .bss, "aw"
    .align 16
__sse_region:
    .skip 512

.section .text
.global __sse_save
.global __sse_init
.type __sse_init, @function
.type __sse_save, @function

.intel_syntax noprefix

__sse_save:
    fxsave __sse_region
    ret

__sse_init:
    mov eax, cr0
    and ax, 0xFFFB
    or ax, 0x2
    mov cr0, eax
    mov eax, cr4
    or ax, 3 << 9
    mov cr4, eax
    call __sse_save
    ret
