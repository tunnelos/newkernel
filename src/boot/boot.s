.code32

# Declare constants for the multiboot header.
.set ALIGN,    1<<0                       # align loaded modules on page boundaries
.set MEMINFO,  1<<1                       # provide memory map
.set MONINFO,  1<<2                       # set video resolution
.set FLAGS,    ALIGN | MEMINFO | MONINFO  # this is the Multiboot 'flag' field
.set MAGIC,    0x1BADB002                 # 'magic number' lets bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS)           # checksum of above, to prove we are multiboot

# Declare a multiboot header that marks the program as a kernel.
.section .multiboot.data, "aw"
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM
.long 0
.long 0
.long 0
.long 0
.long 0
.long 0
.long 1280
.long 720
.long 32

# Allocate the initial stack.
.section .bootstrap_stack, "aw", @nobits
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

# Preallocate pages used for paging. Don't hard-code addresses and assume they
# are available, as the bootloader might have loaded its multiboot structures or
# modules there. This lets the bootloader know it must avoid the addresses.
.section .bss, "aw", @nobits
	.align 4096
boot_page_directory:
	.skip 4096
boot_page_table1:
	.skip 4096
boot_page_table2:
	.skip 4096
boot_page_table3:
	.skip 4096
boot_page_table4:
	.skip 4096
boot_page_table5:
	.skip 4096
boot_page_table6:
	.skip 4096
boot_page_table7:
	.skip 4096
boot_memorytables:
	.skip 32
multiboot_address:
	.skip 4
# Further page tables may be required if the kernel grows beyond 3 MiB.

# The kernel entry point.
.section .multiboot.text, "a"
.global _start
.type _start, @function
.global _print_character
.type _print_character, @function

_print_character:
	# ecx - buffer address
	# edx - character
	push %ebp
	movl %esp, %ebp

	movl %edx, (%ecx)
	incl %ecx
	movl $0x0F, (%ecx)
	incl %ecx

	pop %ebp
	ret
_start:
	# Map Multiboot structure
	
	orl $0x003, %ebx
	movl %ebx, boot_page_table7 - 0xC0000000 + 2 * 4 

	movl $0x000B8000, %ecx
	movl $'T', %edx
	call _print_character
	movl $'u', %edx
	call _print_character
	movl $'n', %edx
	call _print_character
	movl $'n', %edx
	call _print_character
	movl $'e', %edx
	call _print_character
	movl $'l', %edx
	call _print_character
	movl $' ', %edx
	call _print_character
	movl $'O', %edx
	call _print_character
	movl $'S', %edx
	call _print_character
	movl $' ', %edx
	call _print_character
	movl $'P', %edx
	call _print_character
	movl $'r', %edx
	call _print_character
	movl $'e', %edx
	call _print_character
	movl $'l', %edx
	call _print_character
	movl $'o', %edx
	call _print_character
	movl $'a', %edx
	call _print_character
	movl $'d', %edx
	call _print_character
	movl $'e', %edx
	call _print_character
	movl $'r', %edx
	call _print_character
# aa:
	# jmp aa
	# Physical address of boot_page_table1.
	# TODO: I recall seeing some assembly that used a macro to do the
	#       conversions to and from physical. Maybe this should be done in this
	#       code as well?
	movl $(boot_page_table1 - 0xC0000000), %edi
	# First address to map is address 0.
	# TODO: Start at the first kernel page instead. Alternatively map the first
	#       1 MiB as it can be generally useful, and there's no need to
	#       specially map the VGA buffer.
	movl $0, %esi
	
	# Map all 1024 pages for the kernel code.
	movl $1024, %ecx

1:
	# Only map the kernel.
	cmpl $_kernel_start, %esi
	jl 2f
	cmpl $(_kernel_end - 0xC0000000), %esi
	jge 3f

	# Map physical address as "present, writable". Note that this maps
	# .text and .rodata as writable. Mind security and map them as non-writable.
	movl %esi, %edx
	orl $0x003, %edx
	movl %edx, (%edi)

2:
	# Size of page is 4096 bytes.
	addl $4096, %esi
	# Size of entries in boot_page_table1 is 4 bytes.
	addl $4, %edi
	# Loop to the next entry if we haven't finished.
	loop 1b

3:
	# Map VGA video memory to 0x00400000 as "present, writable".
	movl    %ebx, %esi
	movl    $boot_page_table2+1073741824, %edx
	movl    $753664, %eax
.L2:
	movl    %eax, %ecx
	orl     $3, %ecx
    movl    %ecx, (%edx)
    addl    $4096, %eax
    addl    $4, %edx
    cmpl    $4947968, %eax
    jne     .L2
    movl    $0, %eax
	movl    $0x000BA000, %ebx
	movl    $0, %ecx
	movl    $0, %edx

	movl $(0x000BA000 | 0x003), boot_page_table2 - 0xC0000000 + 2 * 4

	# Map free memory
	
	movl $0x000B8000, %ebp

	movb $0x30, (%ebp)
	incl %ebp
	movb $0x0F, (%ebp)
	incl %ebp

	movl boot_memorytables - 0xC0000000 + 0, %esi
	
	movl $(boot_page_table3 - 0xC0000000), %edi
	movl %edi, (%esi)

	addl $4, %esi
	movl $(boot_page_table4 - 0xC0000000), %edi
	movl %edi, (%esi)

	addl $4, %esi
	movl $(boot_page_table5 - 0xC0000000), %edi
	movl %edi, (%esi)

	addl $4, %esi
	movl $(boot_page_table6 - 0xC0000000), %edi
	movl %edi, (%esi)
	
	movb $0x31, (%ebp)
	incl %ebp
	movb $0x0F, (%ebp)
	incl %ebp

10:
	movl $0x01000000, %eax # physical address
	movl boot_memorytables - 0xC0000000 + 0, %esi # virtual address
	movl $0, %edx # tb 2
11:
	movl $0, %ecx # table pointer
	movl (%esi), %edi # table address
12:
	movl %eax, %ebx
	orl $0x003, %ebx

	movl %ebx, (%edi, %ecx, 4)

	cmpl $1024, %ecx
	je 13f

	incl %ecx

	add $0x1000, %eax

	jmp 12b
13:
	incl %edx
	cmpl $4, %edx

	je 14f

	addl $4, %esi

	jne 11b
14:
	# The page table is used at both page directory entry 0 (virtually from 0x0
	# to 0x3FFFFF) (thus identity mapping the kernel) and page directory entry
	# 768 (virtually from 0xC0000000 to 0xC03FFFFF) (thus mapping it in the
	# higher half). The kernel is identity mapped because enabling paging does
	# not change the next instruction, which continues to be physical. The CPU
	# would instead page fault if there was no identity mapping.

	# Map the page table to both virtual addresses 0x00000000 and 0xC0000000.
	movl $(boot_page_table1 - 0xC0000000 + 0x003), boot_page_directory - 0xC0000000 + 0
	movl $(boot_page_table1 - 0xC0000000 + 0x003), boot_page_directory - 0xC0000000 + 768 * 4
	movl $(boot_page_table2 - 0xC0000000 + 0x003), boot_page_directory - 0xC0000000 + 1 * 4
	movl $(boot_page_table3 - 0xC0000000 + 0x003), boot_page_directory - 0xC0000000 + 2 * 4
	movl $(boot_page_table4 - 0xC0000000 + 0x003), boot_page_directory - 0xC0000000 + 3 * 4
	movl $(boot_page_table5 - 0xC0000000 + 0x003), boot_page_directory - 0xC0000000 + 4 * 4
	movl $(boot_page_table6 - 0xC0000000 + 0x003), boot_page_directory - 0xC0000000 + 5 * 4
	movl $(boot_page_table7 - 0xC0000000 + 0x003), boot_page_directory - 0xC0000000 + 6 * 4

	# Set cr3 to the address of the boot_page_directory.
	movl $(boot_page_directory - 0xC0000000), %ecx
	movl %ecx, %cr3

	# Enable paging and the write-protect bit.
	movl %cr0, %ecx
	orl $0x80010000, %ecx
	movl %ecx, %cr0

	# Jump to higher half with an absolute jump. 
	lea 4f, %ecx
	jmp *%ecx

.section .text

4:
	# At this point, paging is fully set up and enabled.

	# Unmap the identity mapping as it is now unnecessary. 
	movl $0, boot_page_directory + 0

	# Reload crc3 to force a TLB flush so the changes to take effect.
	movl %cr3, %ecx
	movl %ecx, %cr3

	# Set up the stack.
	mov $stack_top, %esp

	# Enter the high-level kernel.
	call __sse_init
	call __fpu_init
	# call __avx_init
	call __keyboard_ps2_init
	# call __serial_init
	# call __terminal_init

	call kernel_main

	# Infinite loop if the system has nothing more to do.
	cli
1:	hlt
	jmp 1b
