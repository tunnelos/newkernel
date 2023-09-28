include codetree
export $(shell sed 's/=.*//' codetree)

RANDOM := $(shell od -An -N2 -i /dev/random | tr -d ' ')

vhd:
	@dd if=/dev/zero of=VHD$(RANDOM).img bs=1M count=512	
kernelboot:
	@qemu-system-i386 -m 32M -kernel ../build/kernel.elf -no-shutdown -no-reboot -s -serial stdio -drive file=VHD.img,format=raw,index=0,media=disk #-d int
kernelbootiso:
	@qemu-system-i386 -m 32M -cdrom ../build/kernel/kernel.iso -no-shutdown -no-reboot -s -serial stdio -drive file=VHD.img,format=raw,index=0,media=disk #-d int
buildimage:
	@mkdir -p ../build/kernel/tree/boot/grub
	@cp ../build/kernel.elf ../build/kernel/tree/boot/
	@cp boot/grub.cfg ../build/kernel/tree/boot/grub/grub.cfg
	@grub-mkrescue -o ../build/kernel/kernel.iso ../build/kernel/tree
	@rm -r ../build/kernel/tree
process_debugging:
	@objcopy --only-keep-debug ../build/kernel.elf ../build/kernel.sym
	@objdump -D ../build/kernel.elf > ../build/kernel.txt
linkage:
	@mkdir -p ../build/kernel

	@echo Linking ...

	@$(CC) -T link.ld -o ../build/kernel.elf $(CARGS) -nostdlib $(FILES) -lgcc

	@echo Done.

	@make buildimage --no-print-directory