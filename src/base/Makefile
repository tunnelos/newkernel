CPARAMS=-ffreestanding -O0 -Wall -Wextra -no-pie -fno-pic
.RECIPEPREFIX = >

all:
> @mkdir ../../build -p
> @mkdir ../../build/base -p

> @echo Compiling base/main.c ...
        
> @i686-linux-gnu-gcc -c main.c $(CPARAMS) -o ../../build/base/main.o 
            
> @echo Compiling base/mm.c ...
        
> @i686-linux-gnu-gcc -c mm.c $(CPARAMS) -o ../../build/base/mm.o 
            
> @echo Compiling base/tunnel.c ...
        
> @i686-linux-gnu-gcc -c tunnel.c $(CPARAMS) -o ../../build/base/tunnel.o 
            
> @echo base branch done.
    