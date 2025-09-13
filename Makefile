CC = gcc
LD = ld
AS = nasm

CFLAGS = -m32 -ffreestanding -Wall -Wextra
LDFLAGS = -m elf_i386 -T link.ld

BUILD_DIR = build
SRC_DIRS = cpu drivers kernel misc
SRC_C = $(wildcard $(addsuffix /*.c, $(SRC_DIRS)))
SRC_ASM = $(wildcard $(addsuffix /*.asm, $(SRC_DIRS)))
OBJ = $(addprefix $(BUILD_DIR)/, $(SRC_C:.c=.o) $(SRC_ASM:.asm=.o))

all: moss

$(BUILD_DIR):
	mkdir -p build/

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.asm
	mkdir -p $(dir $@)
	$(AS) -f elf32 $< -o $@

moss: $(OBJ)
	$(LD) $(LDFLAGS) -o $@ $(OBJ)

run: moss
	qemu-system-x86_64 -vga std -kernel moss -d int

clean:
	rm -rf $(BUILD_DIR)

