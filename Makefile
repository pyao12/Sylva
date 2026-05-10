CFLAGS = -Iinclude -Ignu-efi/inc -ffreestanding -fno-stack-protector -fno-stack-check -fshort-wchar -mno-red-zone -std=c17 -Wwrite-strings
CXXFLAGS = -Iinclude -Ignu-efi/inc -ffreestanding -fno-stack-protector -fno-stack-check -fshort-wchar -mno-red-zone -maccumulate-outgoing-args -std=c++17 -Wwrite-strings
LDFLAGS = -shared -Bsymbolic -Lgnu-efi/x86_64/lib -Lgnu-efi/x86_64/gnuefi -Tgnu-efi/gnuefi/elf_x86_64_efi.lds
LDLIBS = -lgnuefi -lefi --no-undefined

SRC_C = $(wildcard *.c)
SRC_CPP = $(wildcard */*.cpp)
OBJ = $(SRC_C:%.c=build/%.o) $(SRC_CPP:%.cpp=build/%.o)

_bd:
	@mkdir -p build/graphics build/kernel build/fonts

all: _bd $(OBJ)
	@echo "* Linking EFI..."
	@ld $(LDFLAGS) gnu-efi/x86_64/gnuefi/crt0-efi-x86_64.o build/boot.o build/graphics/draw.o build/graphics/context.o build/kernel/main.o build/fonts/pixel_font.o -o build/boot.so $(LDLIBS)
	@objcopy -j .text -j .sdata -j .data -j .rodata -j .dynamic -j .dynsym -j .rel -j .rela -j .rel.* -j .rela.* -j .reloc --output-target efi-app-x86_64 --subsystem=10 build/boot.so build/BOOTX64.EFI

build/%.o: %.c
	@echo "Compile C File $< to $@"
	@gcc $(CFLAGS) -c $< -o $@

build/%.o: %.cpp
	@echo "Compile CPP File $< to $@"
	@g++ $(CXXFLAGS) -c $< -o $@

vdir: all
	@mkdir -p vdir/EFI/BOOT
	@cp build/BOOTX64.EFI vdir/EFI/BOOT

run: vdir
	@echo "Launching QEMU"
	@qemu-system-x86_64 -bios /usr/share/ovmf/OVMF.fd -net none -drive file=fat:rw:vdir,index=0,format=vvfat -serial file:serial.log -monitor stdio -s -S

clean:
	@echo "Cleaning old files"
	@rm -rf build vdir

.PHONY: all vdir run clean _bd