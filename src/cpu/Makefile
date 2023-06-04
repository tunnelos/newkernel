CPARAMS=-ffreestanding -O2 -Wall -Wextra -no-pie
.RECIPEPREFIX = >

all:
> @mkdir ../../build -p
> @mkdir ../../build/cpu -p

> @echo Compiling cpu/avx.asm ...
        
> @i686-linux-gnu-as avx.asm  -o ../../build/cpu/avx.o 
            
> @echo Compiling cpu/fpu.asm ...
        
> @i686-linux-gnu-as fpu.asm  -o ../../build/cpu/fpu.o 
            
> @echo Compiling cpu/gdtstatic.c ...
        
> @i686-linux-gnu-gcc -c gdtstatic.c $(CPARAMS) -o ../../build/cpu/gdtstatic.o 
            
> @echo Compiling cpu/io.c ...
        
> @i686-linux-gnu-gcc -c io.c $(CPARAMS) -o ../../build/cpu/io.o 
            
> @echo Compiling cpu/sse.asm ...
        
> @i686-linux-gnu-as sse.asm  -o ../../build/cpu/sse.o 
            
> @echo Compiling cpu/tlb.c ...
        
> @i686-linux-gnu-gcc -c tlb.c $(CPARAMS) -o ../../build/cpu/tlb.o 
            
> @echo cpu branch done.
    