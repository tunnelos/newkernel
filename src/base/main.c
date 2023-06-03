#include "../include/tunnel.h"
#include "../include/vga80x25.h"

#include "../include/application_bootscreen/main.h"

#include "../include/stdio.h"

#include <stdbool.h>
#include <assert.h>

void kernel_main(void) {
	__app_bootscreen_init();
	
	tunnel_config.terminal.row = 3;
    tunnel_config.terminal.column = 1;
	tunnel_config.terminal.color = vga_entry_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);

	puts("Paging successful.\n");

	char buffer[20];

	printf("\n hello: %s \n", ftoa(20.1f, buffer));

	assert(false);

	while(1);
}