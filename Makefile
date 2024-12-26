
bin/os-image.bin: bin/bootSector.bin bin/kernel.bin
	cat bin/bootSector.bin bin/kernel.bin > bin/os-image.bin

bin/bootSector.bin: src/x86_64/bootSector.asm $(wildcard src/x86_64/include/*.asm)
	nasm -f bin -o bin/bootSector.bin src/x86_64/bootSector.asm

bin/kernel.bin: bin/kernel.o bin/kernelEntry.o
	x86_64-elf-ld -m elf_i386 -o bin/kernel.bin -Ttext 0x1000 bin/kernel.o bin/kernelEntry.o --oformat binary

bin/kernel.o: src/C/kernel.c
	x86_64-elf-gcc -m32 -ffreestanding -c src/C/kernel.c -o bin/kernel.o

bin/kernelEntry.o: src/x86_64/kernelEntry.asm
	nasm -f elf -o bin/kernelEntry.o src/x86_64/kernelEntry.asm

clean:
	rm -rf bin/*