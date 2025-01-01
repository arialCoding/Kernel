C_SOURCES = $(wildcard src/C/*.c)
C_HEADERS = $(wildcard src/C/include/*.h)

bin_DIR = build/bin
obj_DIR = build/obj

C_src_DIR = src/c
ASM_src_DIR = src/asm

OBJ = $(addprefix $(obj_DIR)/, $(notdir $(C_SOURCES:.c=.o)))

C_FLAGS = -g -I $(C_src_DIR)/include

build/os-image.bin: $(bin_DIR)/bootSector.bin $(bin_DIR)/kernel.bin
	cat $(bin_DIR)/bootSector.bin $(bin_DIR)/kernel.bin > build/os-image.bin

$(bin_DIR)/kernel.bin: $(obj_DIR)/kernelEntry.o $(OBJ)
	i386-elf-ld -o $(bin_DIR)/kernel.bin -T link.lds $(OBJ) $(obj_DIR)/kernelEntry.o --oformat binary

#FOR DEBUGGING
build/DBG/kernel.elf: $(obj_DIR)/kernelEntry.o $(OBJ)
	i386-elf-ld -o build/DBG/kernel.elf -T link.lds $(OBJ) $(obj_DIR)/kernelEntry.o

run: os-image.bin
	qemu-system-i386 -fda build/os-image.bin

debug: build/os-image.bin build/DBG/kernel.elf
	qemu-system-i386 -gdb tcp::1234 -S -fda build/os-image.bin &
	i386-elf-gdb -ex "target remote localhost:1234" -ex "symbol-file build/DBG/kernel.elf"

#GENERIC
$(obj_DIR)/%.o: $(C_src_DIR)/%.c ${C_HEADERS}
	i386-elf-gcc -ffreestanding -c $< -o $@ $(C_FLAGS)

$(obj_DIR)/%.o: $(ASM_src_DIR)/%.asm
	nasm $< -f elf -o $@

$(bin_DIR)/%.bin: $(ASM_src_DIR)/%.asm
	nasm $< -f bin -o $@

clean:
	rm -rf build/* && mkdir build/obj build/bin build/DBG