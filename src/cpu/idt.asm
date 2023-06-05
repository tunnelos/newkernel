.section .bss, "aw"

.global __idt_stub_table
.global __idt_currentInterrupt

__idt_stub_table:
    .skip 1024
__idt_currentInterrupt:
    .skip 4

.section .text
.global isr_stub_0
.type isr_stub_0, @function
.global isr_stub_1
.type isr_stub_1, @function
.global isr_stub_2
.type isr_stub_2, @function
.global isr_stub_3
.type isr_stub_3, @function
.global isr_stub_4
.type isr_stub_4, @function
.global isr_stub_5
.type isr_stub_5, @function
.global isr_stub_6
.type isr_stub_6, @function
.global isr_stub_7
.type isr_stub_7, @function
.global isr_stub_8
.type isr_stub_8, @function
.global isr_stub_9
.type isr_stub_9, @function
.global isr_stub_10
.type isr_stub_10, @function
.global isr_stub_11
.type isr_stub_11, @function
.global isr_stub_12
.type isr_stub_12, @function
.global isr_stub_13
.type isr_stub_13, @function
.global isr_stub_14
.type isr_stub_14, @function
.global isr_stub_15
.type isr_stub_15, @function
.global isr_stub_16
.type isr_stub_16, @function
.global isr_stub_17
.type isr_stub_17, @function
.global isr_stub_18
.type isr_stub_18, @function
.global isr_stub_19
.type isr_stub_19, @function
.global isr_stub_20
.type isr_stub_20, @function
.global isr_stub_21
.type isr_stub_21, @function
.global isr_stub_22
.type isr_stub_22, @function
.global isr_stub_23
.type isr_stub_23, @function
.global isr_stub_24
.type isr_stub_24, @function
.global isr_stub_25
.type isr_stub_25, @function
.global isr_stub_26
.type isr_stub_26, @function
.global isr_stub_27
.type isr_stub_27, @function
.global isr_stub_28
.type isr_stub_28, @function
.global isr_stub_29
.type isr_stub_29, @function
.global isr_stub_30
.type isr_stub_30, @function
.global isr_stub_31
.type isr_stub_31, @function

.intel_syntax noprefix

isr_stub_0:
    push ebp
    mov ebp, esp
    mov edi, 0
    mov dword [ebp-8], edi
    mov eax, dword [ebp-8]
    call __idt_interrupt_handler
    pop ebp
    iret

isr_stub_1:
    push ebp
    mov ebp, esp
    mov edi, 1
    mov dword [ebp-8], edi
    mov eax, dword [ebp-8]
    call __idt_interrupt_handler
    pop ebp
    iret

isr_stub_2:
    push ebp
    mov ebp, esp
    mov edi, 2
    mov dword [ebp-8], edi
    mov eax, dword [ebp-8]
    call __idt_interrupt_handler
    pop ebp
    iret

isr_stub_3:
    push ebp
    mov ebp, esp
    mov edi, 3
    mov dword [ebp-8], edi
    mov eax, dword [ebp-8]
    call __idt_interrupt_handler
    pop ebp
    iret

isr_stub_4:
    push ebp
    mov ebp, esp
    mov edi, 4
    mov dword [ebp-8], edi
    mov eax, dword [ebp-8]
    call __idt_interrupt_handler
    pop ebp
    iret

isr_stub_5:
    push ebp
    mov ebp, esp
    mov edi, 5
    mov dword [ebp-8], edi
    mov eax, dword [ebp-8]
    call __idt_interrupt_handler
    pop ebp
    iret

isr_stub_6:
    push ebp
    mov ebp, esp
    mov edi, 6
    mov dword [ebp-8], edi
    mov eax, dword [ebp-8]
    call __idt_interrupt_handler
    pop ebp
    iret

isr_stub_7:
    push ebp
    mov ebp, esp
    mov edi, 7
    mov dword [ebp-8], edi
    mov eax, dword [ebp-8]
    call __idt_interrupt_handler
    pop ebp
    iret

isr_stub_8:
    push ebp
    mov ebp, esp
    mov edi, 8
    mov dword [ebp-8], edi
    mov eax, dword [ebp-8]
    call __idt_exception_handler
    pop ebp
    iret

isr_stub_9:
    push ebp
    mov ebp, esp
    mov edi, 9
    mov dword [ebp-8], edi
    mov eax, dword [ebp-8]
    call __idt_interrupt_handler
    pop ebp
    iret

isr_stub_10:
    push ebp
    mov ebp, esp
    mov edi, 10
    mov dword [ebp-8], edi
    mov eax, dword [ebp-8]
    call __idt_exception_handler
    pop ebp
    iret

isr_stub_11:
    push ebp
    mov ebp, esp
    mov edi, 11
    mov dword [ebp-8], edi
    mov eax, dword [ebp-8]
    call __idt_exception_handler
    pop ebp
    iret

isr_stub_12:
    push ebp
    mov ebp, esp
    mov edi, 12
    mov dword [ebp-8], edi
    mov eax, dword [ebp-8]
    call __idt_exception_handler
    pop ebp
    iret

isr_stub_13:
    push ebp
    mov ebp, esp
    mov edi, 13
    mov dword [ebp-8], edi
    mov eax, dword [ebp-8]
    call __idt_exception_handler
    pop ebp
    iret

isr_stub_14:
    push ebp
    mov ebp, esp
    mov edi, 14
    mov dword [ebp-8], edi
    mov eax, dword [ebp-8]
    call __idt_exception_handler
    pop ebp
    iret

isr_stub_15:
    push ebp
    mov ebp, esp
    mov edi, 15
    mov dword [ebp-8], edi
    mov eax, dword [ebp-8]
    call __idt_interrupt_handler
    pop ebp
    iret

isr_stub_16:
    push ebp
    mov ebp, esp
    mov edi, 16
    mov dword [ebp-8], edi
    mov eax, dword [ebp-8]
    call __idt_interrupt_handler
    pop ebp
    iret

isr_stub_17:
    push ebp
    mov ebp, esp
    mov edi, 17
    mov dword [ebp-8], edi
    mov eax, dword [ebp-8]
    call __idt_exception_handler
    pop ebp
    iret

isr_stub_18:
    push ebp
    mov ebp, esp
    mov edi, 18
    mov dword [ebp-8], edi
    mov eax, dword [ebp-8]
    call __idt_interrupt_handler
    pop ebp
    iret

isr_stub_19:
    push ebp
    mov ebp, esp
    mov edi, 19
    mov dword [ebp-8], edi
    mov eax, dword [ebp-8]
    call __idt_interrupt_handler
    pop ebp
    iret

isr_stub_20:
    push ebp
    mov ebp, esp
    mov edi, 20
    mov dword [ebp-8], edi
    mov eax, dword [ebp-8]
    call __idt_interrupt_handler
    pop ebp
    iret

isr_stub_21:
    push ebp
    mov ebp, esp
    mov edi, 21
    mov dword [ebp-8], edi
    mov eax, dword [ebp-8]
    call __idt_interrupt_handler
    pop ebp
    iret

isr_stub_22:
    push ebp
    mov ebp, esp
    mov edi, 22
    mov dword [ebp-8], edi
    mov eax, dword [ebp-8]
    call __idt_interrupt_handler
    pop ebp
    iret

isr_stub_23:
    push ebp
    mov ebp, esp
    mov edi, 23
    mov dword [ebp-8], edi
    mov eax, dword [ebp-8]
    call __idt_interrupt_handler
    pop ebp
    iret

isr_stub_24:
    push ebp
    mov ebp, esp
    mov edi, 24
    mov dword [ebp-8], edi
    mov eax, dword [ebp-8]
    call __idt_interrupt_handler
    pop ebp
    iret

isr_stub_25:
    push ebp
    mov ebp, esp
    mov edi, 25
    mov dword [ebp-8], edi
    mov eax, dword [ebp-8]
    call __idt_interrupt_handler
    pop ebp
    iret

isr_stub_26:
    push ebp
    mov ebp, esp
    mov edi, 26
    mov dword [ebp-8], edi
    mov eax, dword [ebp-8]
    call __idt_interrupt_handler
    pop ebp
    iret

isr_stub_27:
    push ebp
    mov ebp, esp
    mov edi, 27
    mov dword [ebp-8], edi
    mov eax, dword [ebp-8]
    call __idt_interrupt_handler
    pop ebp
    iret

isr_stub_28:
    push ebp
    mov ebp, esp
    mov edi, 28
    mov dword [ebp-8], edi
    mov eax, dword [ebp-8]
    call __idt_interrupt_handler
    pop ebp
    iret

isr_stub_29:
    push ebp
    mov ebp, esp
    mov edi, 29
    mov dword [ebp-8], edi
    mov eax, dword [ebp-8]
    call __idt_interrupt_handler
    pop ebp
    iret

isr_stub_30:
    push ebp
    mov ebp, esp
    mov edi, 30
    mov dword [ebp-8], edi
    mov eax, dword [ebp-8]
    call __idt_exception_handler
    pop ebp
    iret

isr_stub_31:
    push ebp
    mov ebp, esp
    mov edi, 31
    mov dword [ebp-8], edi
    mov eax, dword [ebp-8]
    call __idt_interrupt_handler
    pop ebp
    iret
