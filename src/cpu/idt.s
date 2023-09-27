.code32

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
    pushad
    cld
    push 0
    call __idt_interrupt_handler
    pop eax
    pop eax
    pop eax
    pop eax
    popad
    iret

isr_stub_1:
    pushad
    cld
    push 1
    call __idt_interrupt_handler
    pop eax
    pop eax
    pop eax
    pop eax
    popad
    iret

isr_stub_2:
    pushad
    cld
    push 2
    call __idt_interrupt_handler
    pop eax
    pop eax
    pop eax
    pop eax
    popad
    iret

isr_stub_3:
    pushad
    cld
    push 3
    call __idt_interrupt_handler
    pop eax
    pop eax
    pop eax
    pop eax
    popad
    iret

isr_stub_4:
    pushad
    cld
    push 4
    call __idt_interrupt_handler
    pop eax
    pop eax
    pop eax
    pop eax
    popad
    iret

isr_stub_5:
    pushad
    cld
    push 5
    call __idt_interrupt_handler
    pop eax
    pop eax
    pop eax
    pop eax
    popad
    iret

isr_stub_6:
    pushad
    cld
    push 6
    call __idt_interrupt_handler
    pop eax
    pop eax
    pop eax
    pop eax
    popad
    iret

isr_stub_7:
    pushad
    cld
    push 7
    call __idt_interrupt_handler
    pop eax
    pop eax
    pop eax
    pop eax
    popad
    iret

isr_stub_8:
    pushad
    cld
    push 8
    call __idt_exception_handler
    pop eax
    pop eax
    pop eax
    pop eax
    popad
    iret

isr_stub_9:
    pushad
    cld
    push 9
    call __idt_interrupt_handler
    pop eax
    pop eax
    pop eax
    pop eax
    popad
    iret

isr_stub_10:
    pushad
    cld
    push 10
    call __idt_exception_handler
    pop eax
    pop eax
    pop eax
    pop eax
    popad
    iret

isr_stub_11:
    pushad
    cld
    push 11
    call __idt_exception_handler
    pop eax
    pop eax
    pop eax
    pop eax
    popad
    iret

isr_stub_12:
    pushad
    cld
    push 12
    call __idt_exception_handler
    pop eax
    pop eax
    pop eax
    pop eax
    popad
    iret

isr_stub_13:
    pushad
    cld
    push 13
    call __idt_exception_handler
    pop eax
    pop eax
    pop eax
    pop eax
    popad
    iret

isr_stub_14:
    pushad
    cld
    push 14
    call __idt_exception_handler
    pop eax
    pop eax
    pop eax
    pop eax
    popad
    iret

isr_stub_15:
    pushad
    cld
    push 15
    call __idt_interrupt_handler
    pop eax
    pop eax
    pop eax
    pop eax
    popad
    iret

isr_stub_16:
    pushad
    cld
    push 16
    call __idt_interrupt_handler
    pop eax
    pop eax
    pop eax
    pop eax
    popad
    iret

isr_stub_17:
    pushad
    cld
    push 17
    call __idt_exception_handler
    pop eax
    pop eax
    pop eax
    pop eax
    popad
    iret

isr_stub_18:
    pushad
    cld
    push 18
    call __idt_interrupt_handler
    pop eax
    pop eax
    pop eax
    pop eax
    popad
    iret

isr_stub_19:
    pushad
    cld
    push 19
    call __idt_interrupt_handler
    pop eax
    pop eax
    pop eax
    pop eax
    popad
    iret

isr_stub_20:
    pushad
    cld
    push 20
    call __idt_interrupt_handler
    pop eax
    pop eax
    pop eax
    pop eax
    popad
    iret

isr_stub_21:
    pushad
    cld
    push 21
    call __idt_interrupt_handler
    pop eax
    pop eax
    pop eax
    pop eax
    popad
    iret

isr_stub_22:
    pushad
    cld
    push 22
    call __idt_interrupt_handler
    pop eax
    pop eax
    pop eax
    pop eax
    popad
    iret

isr_stub_23:
    pushad
    cld
    push 23
    call __idt_interrupt_handler
    pop eax
    pop eax
    pop eax
    pop eax
    popad
    iret

isr_stub_24:
    pushad
    cld
    push 24
    call __idt_interrupt_handler
    pop eax
    pop eax
    pop eax
    pop eax
    popad
    iret

isr_stub_25:
    pushad
    cld
    push 25
    call __idt_interrupt_handler
    pop eax
    pop eax
    pop eax
    pop eax
    popad
    iret

isr_stub_26:
    pushad
    cld
    push 26
    call __idt_interrupt_handler
    pop eax
    pop eax
    pop eax
    pop eax
    popad
    iret

isr_stub_27:
    pushad
    cld
    push 27
    call __idt_interrupt_handler
    pop eax
    pop eax
    pop eax
    pop eax
    popad
    iret

isr_stub_28:
    pushad
    cld
    push 28
    call __idt_interrupt_handler
    pop eax
    pop eax
    pop eax
    pop eax
    popad
    iret

isr_stub_29:
    pushad
    cld
    push 29
    call __idt_interrupt_handler
    pop eax
    pop eax
    pop eax
    pop eax
    popad
    iret

isr_stub_30:
    pushad
    cld
    push 30
    call __idt_exception_handler
    pop eax
    pop eax
    pop eax
    pop eax
    popad
    iret

isr_stub_31:
    pushad
    cld
    push 31
    call __idt_interrupt_handler
    pop eax
    pop eax
    pop eax
    pop eax
    popad
    iret