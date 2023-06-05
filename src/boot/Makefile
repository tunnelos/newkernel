CPARAMS=-ffreestanding -O0 -Wall -Wextra -no-pie -fno-pic
.RECIPEPREFIX = >

all:
> @mkdir ../../build -p
> @mkdir ../../build/boot -p

> @echo Compiling boot/boot.asm ...
        
> @i686-linux-gnu-as boot.asm  -o ../../build/boot/boot.o 
            
> @echo boot branch done.
    