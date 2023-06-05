CPARAMS=-ffreestanding -O0 -Wall -Wextra -no-pie -fno-pic
.RECIPEPREFIX = >

all:
> @mkdir ../../build -p
> @mkdir ../../build/crt -p

> @echo Compiling crt/crti.asm ...
        
> @i686-linux-gnu-as crti.asm  -o ../../build/crt/crti.o 
            
> @echo Compiling crt/crtn.asm ...
        
> @i686-linux-gnu-as crtn.asm  -o ../../build/crt/crtn.o 
            
> @echo crt branch done.
    