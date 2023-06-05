CPARAMS=-ffreestanding -O0 -Wall -Wextra -no-pie -fno-pic
.RECIPEPREFIX = >

all:
> @mkdir ../../build -p
> @mkdir ../../build/std -p

> @echo Compiling std/assert_fail.c ...
        
> @i686-linux-gnu-gcc -c assert_fail.c $(CPARAMS) -o ../../build/std/assert_fail.o 
            
> @echo Compiling std/math.c ...
        
> @i686-linux-gnu-gcc -c math.c $(CPARAMS) -o ../../build/std/math.o 
            
> @echo Compiling std/memcpy.c ...
        
> @i686-linux-gnu-gcc -c memcpy.c $(CPARAMS) -o ../../build/std/memcpy.o 
            
> @echo Compiling std/memset.c ...
        
> @i686-linux-gnu-gcc -c memset.c $(CPARAMS) -o ../../build/std/memset.o 
            
> @echo Compiling std/stdio.c ...
        
> @i686-linux-gnu-gcc -c stdio.c $(CPARAMS) -o ../../build/std/stdio.o 
            
> @echo Compiling std/string.c ...
        
> @i686-linux-gnu-gcc -c string.c $(CPARAMS) -o ../../build/std/string.o 
            
> @echo std branch done.
    