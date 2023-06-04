CPARAMS=-ffreestanding -O2 -Wall -Wextra -no-pie
.RECIPEPREFIX = >

all:
> @mkdir ../../build -p
> @mkdir ../../build/drivers -p

> @echo Compiling drivers/ps2keyboard.c ...
        
> @i686-linux-gnu-gcc -c ps2keyboard.c $(CPARAMS) -o ../../build/drivers/ps2keyboard.o 
            
> @echo Compiling drivers/serial.c ...
        
> @i686-linux-gnu-gcc -c serial.c $(CPARAMS) -o ../../build/drivers/serial.o 
            
> @echo Compiling drivers/terminal80x25.c ...
        
> @i686-linux-gnu-gcc -c terminal80x25.c $(CPARAMS) -o ../../build/drivers/terminal80x25.o 
            
> @echo Compiling drivers/vga80x25.c ...
        
> @i686-linux-gnu-gcc -c vga80x25.c $(CPARAMS) -o ../../build/drivers/vga80x25.o 
            
> @echo drivers branch done.
    