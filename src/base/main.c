#include <tunnel.h>
#include <vga80x25.h>
#include <terminal80x25.h>
#include <drivers/display/pixel_terminal.h>

#include <application_bootscreen/main.h>
#include <application_terminal/main.h>

#include <stdio.h>

#include <external/multiboot.h>
#include <serial.h>

#include <mm.h>
#include <stdlib.h>

#include <stdbool.h>
#include <assert.h>

#include <gdt.h>

#include <service_load.h>

#include <drivers/ide/ide.h>

#include <etc/appman.h>

uint32_t bars[5] = {
	0x1F0, 0x3F6, 0x170, 0x376, 0x000
};

void kernel_main_fun1() {
	__ide_init(bars);
}

void kernel_main(void) {
	__serial_write_fmt("Welcome to the Tunnel OS!\r\n");
	
	tunnel_config.debug = true;

	multiboot_info_t *info = (multiboot_info_t *)0x01802000;
	tunnel_config.tmap = (tunnel_memory_map_t *)0x00800000;
	tunnel_config.multiboot = info;

	__serial_write_fmt("Mem lower: %d\r\n", info->mem_lower);
	__serial_write_fmt("Mem upper: %d\r\n", info->flags);

	if (info->mem_lower == 0) tunnel_config.terminal = __terminal80x25_createTerminal();
	else {
		tunnel_config.terminal = __pixel_terminal_createTerminal();
	}
	
	__global_currentTextTerminal = tunnel_config.terminal;

	tunnel_config.terminal.row = 3;
    tunnel_config.terminal.column = 1;
	tunnel_config.terminal.color = vga_entry_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);

	__service_startInitService(tunnel_config.terminal.init, "Framebuffer", true);

	__service_startInitService(__gdt_init, "GDT", true);

	// __gdt_init();

	tunnel_config.tmap->statistics.blocks_allocated = info->mem_upper;
	__mm_setup(tunnel_config.tmap);

	__service_startInitService(kernel_main_fun1, "IDE", true);

	__service_startInitService(__appman_init, "App Manager", true);

	__service_startInitService(__app_bootscreen_init, "Bootscreen", true);

	__application_terminal_init();
	// __service_startInitService(__application_terminal_init, "Terminal", true);

	while(1);
}