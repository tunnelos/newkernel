#include "../include/tunnel.h"
#include "../include/vga80x25.h"
#include "../include/terminal80x25.h"

#include "../include/application_bootscreen/main.h"
#include "../include/application_terminal/main.h"

#include "../include/stdio.h"

#include "../include/external/multiboot.h"
#include "../include/serial.h"

#include "../include/mm.h"
#include <stdlib.h>

#include <stdbool.h>
#include <assert.h>

#include "../include/gdt.h"

void kernel_main(void) {
	__terminal_init();

	__app_bootscreen_init();
	
	tunnel_config.terminal.row = 3;
    tunnel_config.terminal.column = 1;
	tunnel_config.terminal.color = vga_entry_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);

	multiboot_info_t *info = (multiboot_info_t *)0x00402000;
	tunnel_config.tmap = (tunnel_memory_map_t *)0x00800000;

	__serial_write_fmt("Increments: %d\r\n", ((uint32_t *)0x00800000)[0]);
	__serial_write_fmt("Mem upper: %X\r\n", info->mem_upper);

	tunnel_config.tmap->memsize_kb = info->mem_upper;
	__mm_setup(tunnel_config.tmap);

	char *aa = (char *)(malloc(513));
	aa[0] = 'L';
	free(aa);

	__application_terminal_init();

	while(1);
}