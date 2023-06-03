include codetree
export $(shell sed 's/=.*//' codetree)

kernelboot:
	@qemu-system-i386 -m 256M -kernel ../build/kernel/kernel.bin -no-shutdown -no-reboot -s
kernelbootiso:
	@qemu-system-i386 -m 256M -cdrom ../build/kernel/kernel.iso -no-shutdown -no-reboot -s
buildimage:
	@mkdir -p ../build/kernel/tree/boot/grub
	@cp ../build/kernel/kernel.bin ../build/kernel/tree/boot/
	@cp boot/grub.cfg ../build/kernel/tree/boot/grub/grub.cfg
	@grub-mkrescue -o ../build/kernel/kernel.iso ../build/kernel/tree
	@rm -r ../build/kernel/tree
process_debugging:
	@objcopy --only-keep-debug ../build/kernel/kernel.bin ../build/kernel/kernel.sym
linkage:
	@mkdir -p ../build/kernel

	@echo Linking ...

	@$(CC) -T link.ld -o ../build/kernel/kernel.bin $(CARGS) -nostdlib $(FILES) -lgcc

	@echo Done.

	@make buildimage --no-print-directory
all: $(CODEDIRS)
	@make linkage --no-print-directory
	@make process_debugging --no-print-directory

	@echo
	@echo -----------------------------
	@echo Size: $(shell du -h ../build/kernel/kernel.bin)

$(CODEDIRS):
	@$(MAKE) -C $@ --no-print-directory
.PHONY: $(CODEDIRS)

