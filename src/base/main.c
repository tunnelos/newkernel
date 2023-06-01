#include "../include/terminal80x25.h"
 
void kernel_main(void) 
{
	__terminal_init();

	__terminal_write("Helo, World!\nye, hi\n");
	__terminal_write("Helo, World!\nye, hi\n");
	__terminal_write("Helo, World!\nye, hi\n");
	__terminal_write("Helo, World!\nye, hi\n");
	__terminal_write("Helo, World!\nye, hi\n");
	__terminal_write("Helo, World!\nye, hi\n");
	__terminal_write("Helo, World!\nye, hi\n");
	__terminal_write("Helo, World!\nye, hi\n");
	__terminal_write("Helo, World!\nye, hi\n");
	while(1);
}