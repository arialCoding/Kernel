C_SOURCES = $(wildcard src/C/*.c)
C_HEADERS = $(wildcard src/C/include/*.h)

bin_DIR = build/bin
obj_DIR = build/obj

C_src_DIR = src/c
ASM_src_DIR = src/x86_64

OBJ = $(addprefix $(obj_DIR)/, $(notdir $(C_SOURCES:.c=.o)))

C_FLAGS = -g -I $(C_src_DIR)/include

build/os-image.bin: $(bin_DIR)/bootSector.bin $(bin_DIR)/kernel.bin
	cat $(bin_DIR)/bootSector.bin $(bin_DIR)/kernel.bin > build/os-image.bin

$(bin_DIR)/kernel.bin: $(obj_DIR)/kernelEntry.o $(OBJ)
	x86_64-elf-ld -m elf_i386 -o $(bin_DIR)/kernel.bin -T link.lds $(OBJ) $(obj_DIR)/kernelEntry.o --oformat binary

#FOR DEBUGGING
kernel.elf: $(obj_DIR)/kernelEntry.o $(OBJ)
	x86_64-elf-ld -m elf_i386 -o build/DBG/kernel.elf -T link.lds $(OBJ) $(obj_DIR)/kernelEntry.o

Drun:
	qemu-system-x86_64 -gdb tcp::1234 -S -fda build/os-image.bin

run:
	qemu-system-x86_64 -fda build/os-image.bin

debug:
	gdb -ex "target remote host.docker.internal:1234" -ex "symbol-file build/DBG/kernel.elf"
#GENERIC
$(obj_DIR)/%.o: $(C_src_DIR)/%.c ${C_HEADERS}
	x86_64-elf-gcc -m32 -ffreestanding -c $< -o $@ $(C_FLAGS)

$(obj_DIR)/%.o: $(ASM_src_DIR)/%.asm
	nasm $< -f elf -o $@

$(bin_DIR)/%.bin: $(ASM_src_DIR)/%.asm
	nasm $< -f bin -o $@

clean:
	rm -rf build/* && mkdir build/obj build/bin build/DBG