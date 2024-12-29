C_SOURCES = $(wildcard src/C/*.c)
C_HEADERS = $(wildcard src/C/include/*.h)

bin_DIR = build/bin
obj_DIR = build/obj

C_src_DIR = src/c
ASM_src_DIR = src/x86_64

OBJ = $(addprefix $(obj_DIR)/, $(notdir $(C_SOURCES:.c=.o)))

build/os-image.bin: $(bin_DIR)/bootSector.bin $(bin_DIR)/kernel.bin
	cat $(bin_DIR)/bootSector.bin $(bin_DIR)/kernel.bin > build/os-image.bin

$(bin_DIR)/kernel.bin: $(obj_DIR)/kernelEntry.o $(OBJ)
	x86_64-elf-ld -m elf_i386 -o $(bin_DIR)/kernel.bin -Ttext 0x1000 $(OBJ) $(obj_DIR)/kernelEntry.o --oformat binary

#FOR DEBUGGING
kernel.elf: $(obj_DIR)/kernelEntry.o $(OBJ)
	x86_64-elf-ld -m elf_i386 -o build/DBG/kernel.elf -Ttext 0x1000 $(OBJ) $(obj_DIR)/kernelEntry.o

debug:
	qemu-system-x86_64 -gdb tcp::1234 -S -fda build/os-image.bin &

#GENERIC
$(obj_DIR)/%.o: $(C_src_DIR)/%.c ${C_HEADERS}
	x86_64-elf-gcc -m32 -ffreestanding -c $< -o $@ -g

$(obj_DIR)/%.o: $(ASM_src_DIR)/%.asm
	nasm $< -f elf -o $@

$(bin_DIR)/%.bin: $(ASM_src_DIR)/%.asm
	nasm $< -f bin -o $@

clean:
	rm -rf build/* && mkdir build/obj build/bin build/DBG