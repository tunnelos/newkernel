CPARAMS=-ffreestanding -O2 -Wall -Wextra -no-pie -g
.RECIPEPREFIX = >

all:
> @mkdir ../../build -p
> @mkdir ../../build/crt -p

> @echo Compiling crt/crti.asm ...
        
> @i686-linux-gnu-as crti.asm -g -o ../../build/crt/crti.o 
            
> @echo Compiling crt/crtn.asm ...
        
> @i686-linux-gnu-as crtn.asm -g -o ../../build/crt/crtn.o 
            
> @echo crt branch done.
    