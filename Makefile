MINGW_GCC = x86_64-w64-mingw32-gcc
QEMU = qemu-system-x86_64
MINGW_GCC_FLAGS = -Wall -Wextra -e efi_main -nostdinc -nostdlib  -fno-builtin -Wl,--subsystem,10

all: 
	mkdir -p build
	x86_64-w64-mingw32-gcc $(MINGW_GCC_FLAGS) -o build/BOOTX64.EFI boot.c

vdir: all
	mkdir -p vdir
	mkdir -p vdir/EFI/BOOT
	cp build/BOOTX64.EFI vdir/EFI/BOOT

run: vdir
	$(QEMU) -bios /usr/share/ovmf/OVMF.fd -net none -drive file=fat:rw:vdir,index=0,format=vvfat -serial stdio

clean:
	rm -rf build vdir