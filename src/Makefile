include codetree
export $(shell sed 's/=.*//' codetree)

kernelboot:
	@qemu-system-i386 -kernel ../build/kernel/kernel.bin
kernelbootiso:
	@qemu-system-i386 -cdrom ../build/kernel/kernel.iso
buildimage:
	@mkdir -p ../build/kernel/tree/boot/grub
	@cp ../build/kernel/kernel.bin ../build/kernel/tree/boot/
	@cp boot/grub.cfg ../build/kernel/tree/boot/grub/grub.cfg
	@grub-mkrescue -o ../build/kernel/kernel.iso ../build/kernel/tree
	@rm -r ../build/kernel/tree
linkage:
	@mkdir -p ../build/kernel

	@echo Linking ...

	@i686-linux-gnu-gcc -T link.ld -o ../build/kernel/kernel.bin -ffreestanding -O2 -nostdlib $(FILES) -lgcc

	@echo Done.

	@make buildimage
all: $(CODEDIRS) linkage

$(CODEDIRS):
	@$(MAKE) -C $@
.PHONY: $(CODEDIRS)

