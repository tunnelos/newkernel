#include "../include/tunnel.h"
#include "../include/vga80x25.h"
#include "../include/terminal80x25.h"

#include "../include/application_bootscreen/main.h"
#include "../include/application_terminal/main.h"

#include "../include/stdio.h"

#include "../include/external/multiboot.h"
#include "../include/serial.h"

#include <stdbool.h>
#include <assert.h>

void kernel_main(void) {
	__terminal_init();
    __terminal_reset();

	__app_bootscreen_init();
	
	tunnel_config.terminal.row = 3;
    tunnel_config.terminal.column = 1;
	tunnel_config.terminal.color = vga_entry_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);

	char *data = (char *)0x00800000;
	data[0] = 0xDE;
	data[1] = 0xAD;
	data[2] = 0xBE;
	data[3] = 0xEF;

	multiboot_info_t *info = (multiboot_info_t *)0x00402000;

	multiboot_memory_map_t *mmmt = info + 0xA8;

	__serial_write_fmt("Memory maps: %d\r\n", info->mmap_length);
	__serial_write_fmt("Memory map addr: %X\r\n", info->mmap_addr);
	__serial_write_fmt("Flags: %X\r\n", info->flags);
	__serial_write_fmt("Mem lower: %X\r\n", info->mem_lower);
	__serial_write_fmt("Mem upper: %X\r\n", info->mem_upper);

	// mmap
	// assert(!(info->flags >> 6 & 0x1));

	__application_terminal_init();

	while(1);
}