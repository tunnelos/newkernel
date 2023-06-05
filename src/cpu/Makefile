CPARAMS=-ffreestanding -O0 -Wall -Wextra -no-pie -fno-pic
.RECIPEPREFIX = >

all:
> @mkdir ../../build -p
> @mkdir ../../build/cpu -p

> @echo Compiling cpu/avx.asm ...
        
> @i686-linux-gnu-as avx.asm  -o ../../build/cpu/avx.o 
            
> @echo Compiling cpu/fpu.asm ...
        
> @i686-linux-gnu-as fpu.asm  -o ../../build/cpu/fpu.o 
            
> @echo Compiling cpu/gdt.asm ...
        
> @i686-linux-gnu-as gdt.asm  -o ../../build/cpu/gdt.o 
            
> @echo Compiling cpu/gdtc.c ...
        
> @i686-linux-gnu-gcc -c gdtc.c $(CPARAMS) -o ../../build/cpu/gdtc.o 
            
> @echo Compiling cpu/gdtstatic.c ...
        
> @i686-linux-gnu-gcc -c gdtstatic.c $(CPARAMS) -o ../../build/cpu/gdtstatic.o 
            
> @echo Compiling cpu/idt.asm ...
        
> @i686-linux-gnu-as idt.asm  -o ../../build/cpu/idt.o 
            
> @echo Compiling cpu/idtc.c ...
        
> @i686-linux-gnu-gcc -c idtc.c $(CPARAMS) -o ../../build/cpu/idtc.o 
            
> @echo Compiling cpu/idtstatic.c ...
        
> @i686-linux-gnu-gcc -c idtstatic.c $(CPARAMS) -o ../../build/cpu/idtstatic.o 
            
> @echo Compiling cpu/io.c ...
        
> @i686-linux-gnu-gcc -c io.c $(CPARAMS) -o ../../build/cpu/io.o 
            
> @echo Compiling cpu/paging.c ...
        
> @i686-linux-gnu-gcc -c paging.c $(CPARAMS) -o ../../build/cpu/paging.o 
            
> @echo Compiling cpu/sse.asm ...
        
> @i686-linux-gnu-as sse.asm  -o ../../build/cpu/sse.o 
            
> @echo Compiling cpu/tlb.c ...
        
> @i686-linux-gnu-gcc -c tlb.c $(CPARAMS) -o ../../build/cpu/tlb.o 
            
> @echo Compiling cpu/tssstatic.c ...
        
> @i686-linux-gnu-gcc -c tssstatic.c $(CPARAMS) -o ../../build/cpu/tssstatic.o 
            
> @echo cpu branch done.
    