CPARAMS=-ffreestanding -O2 -Wall -Wextra -no-pie -g
.RECIPEPREFIX = >

all:
> @mkdir ../../build -p
> @mkdir ../../build/drivers -p

> @echo Compiling drivers/terminal80x25.c ...
        
> @i686-linux-gnu-gcc -c terminal80x25.c $(CPARAMS) -o ../../build/drivers/terminal80x25.o 
            
> @echo Compiling drivers/vga80x25.c ...
        
> @i686-linux-gnu-gcc -c vga80x25.c $(CPARAMS) -o ../../build/drivers/vga80x25.o 
            
> @echo drivers branch done.
    