#include "../include/terminal80x25.h"

#include "../include/tunnel.h"
#include "../include/vga80x25.h"

#include "../include/application_bootscreen/main.h"

#include <stdbool.h>

void kernel_main(void) 
{
	__terminal_init();

	// int i = 0;
	
	// while(i < 8) {
	// 	__terminal_write("Helo, World!\nye, hi\n");
	// 	if(i % 2) {
	// 		__terminal_setColor(vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_WHITE));
 	// 	} else {
	// 		__terminal_setColor(vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK));
	// 	}
		
	// 	i++;
	// }

	__app_bootscreen_init();

	//__page_directory_init();
	
	tunnel_config.terminal.row = 3;
    tunnel_config.terminal.column = 1;

	//__terminal_setColor(vga_entry_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK));

	__terminal_write("Paging successful.");

	while(1);
}