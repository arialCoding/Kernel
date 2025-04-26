C_SOURCES = $(wildcard src/C/*/*.c) $(wildcard src/C/*/*/*.c)
C_HEADERS = $(wildcard src/C/include/*.h)

bin_DIR = build/bin
obj_DIR = build/obj

C_src_DIR = src/C
ASM_src_DIR = src/x86

INCLUDE_DIRS = -I $(C_src_DIR)/include -I $(C_src_DIR)/libc/include -I $(C_src_DIR)/ARCH/x86/include -I $(C_src_DIR)/drivers/include -I $(C_src_DIR)/kernel/include

OBJ = $(addprefix $(obj_DIR)/, $(notdir $(C_SOURCES:.c=.o))) $(addprefix $(obj_DIR)/, $(notdir $(LIBC_SOURCES:.c=.o)))

C_FLAGS = -g -m32 -Wall -Wextra -Werror -fno-exceptions $(INCLUDE_DIRS) 

build/os-image.bin: $(bin_DIR)/bootSector.bin $(bin_DIR)/kernel.bin
	cat $(bin_DIR)/bootSector.bin $(bin_DIR)/kernel.bin > build/os-image.bin

$(bin_DIR)/kernel.bin: $(obj_DIR)/kernelEntry.o $(OBJ) $(obj_DIR)/interrupt.o
	i386-elf-ld -o $(bin_DIR)/kernel.bin -Ttext 0x1000 $(obj_DIR)/kernelEntry.o $(OBJ) $(obj_DIR)/interrupt.o --oformat binary

#FOR DEBUGGING
build/DBG/kernel.elf: $(obj_DIR)/kernelEntry.o $(OBJ) $(obj_DIR)/interrupt.o
	i386-elf-ld -o build/DBG/kernel.elf -Ttext 0x1000 $(obj_DIR)/kernelEntry.o $(OBJ) $(obj_DIR)/interrupt.o

run: build/os-image.bin
	qemu-system-i386 -fda build/os-image.bin

debug: build/os-image.bin build/DBG/kernel.elf
	qemu-system-i386 -gdb tcp::1234 -S -fda build/os-image.bin &
	i386-elf-gdb -ex "target remote localhost:1234" -ex "symbol-file build/DBG/kernel.elf"

#GENERIC
$(obj_DIR)/%.o: $(C_src_DIR)/%.c ${C_HEADERS}
	i386-elf-gcc $(C_FLAGS) -ffreestanding -c $< -o $@

$(obj_DIR)/%.o: $(C_src_DIR)/libc/%.c ${C_HEADERS}
	i386-elf-gcc $(C_FLAGS) -ffreestanding -c $< -o $@

$(obj_DIR)/%.o: $(C_src_DIR)/kernel/%.c ${C_HEADERS}
	i386-elf-gcc $(C_FLAGS) -ffreestanding -c $< -o $@

$(obj_DIR)/%.o: $(C_src_DIR)/ARCH/x86/%.c ${C_HEADERS}
	i386-elf-gcc $(C_FLAGS) -ffreestanding -c $< -o $@

$(obj_DIR)/%.o: $(C_src_DIR)/drivers/%.c ${C_HEADERS}
	i386-elf-gcc $(C_FLAGS) -ffreestanding -c $< -o $@

$(obj_DIR)/%.o: $(ASM_src_DIR)/%.asm
	nasm $< -f elf -o $@

$(bin_DIR)/%.bin: $(ASM_src_DIR)/%.asm
	nasm $< -f bin -o $@

clean:
	rm -rf build/* && mkdir -p build/obj build/bin build/DBG
