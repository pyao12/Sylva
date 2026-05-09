all:
	mkdir -p build
	gcc -Ignu-efi/inc -ffreestanding -fno-stack-protector -fno-stack-check -fshort-wchar -mno-red-zone -maccumulate-outgoing-args -std=c17 -c boot.c -o build/boot.o
	g++ -Iinclude -Ignu-efi/inc -ffreestanding -fno-stack-protector -fno-stack-check -fshort-wchar -mno-red-zone -maccumulate-outgoing-args -std=c++17 -c kernel/main.cpp -o build/kernel.o
	ld -shared -Bsymbolic -Lgnu-efi/x86_64/lib -Lgnu-efi/x86_64/gnuefi -Tgnu-efi/gnuefi/elf_x86_64_efi.lds gnu-efi/x86_64/gnuefi/crt0-efi-x86_64.o build/boot.o build/kernel.o -o build/boot.so -lgnuefi -lefi --no-undefined
	objcopy -j .text -j .sdata -j .data -j .rodata -j .dynamic -j .dynsym  -j .rel -j .rela -j .rel.* -j .rela.* -j .reloc --output-target efi-app-x86_64 --subsystem=10 build/boot.so build/BOOTX64.EFI

vdir: all
	mkdir -p vdir
	mkdir -p vdir/EFI/BOOT
	cp build/BOOTX64.EFI vdir/EFI/BOOT

run: vdir
	qemu-system-x86_64 -bios /usr/share/ovmf/OVMF.fd -net none -drive file=fat:rw:vdir,index=0,format=vvfat -serial file:serial.log -serial stdio -s -S

clean:
	rm -rf build vdir

.PHONY: all vdir run clean