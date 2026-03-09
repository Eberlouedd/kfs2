KERNEL = kernel.bin
ISO = kernel.iso
GRUBDIR := /usr/lib/grub/i386-pc

SRCS   := \
	kernel/kernel.c \
	kernel/helpers.c \
	kernel/console.c \
	kernel/gdt.c \
	kernel/stack.c

OBJS   := $(SRCS:.c=.o) boot.o gdt_flush.o

all: $(ISO)

boot.o: boot/boot.asm
	nasm -f elf32 $< -o $@

gdt_flush.o: boot/gdt_flush.asm
	nasm -f elf32 $< -o $@

kernel/%.o: kernel/%.c
	gcc -m32 -O0 -ffreestanding -fno-builtin -fno-stack-protector -fno-omit-frame-pointer \
		-nostdlib -nodefaultlibs -c $< -o $@

$(KERNEL): $(OBJS) linker.ld
	ld -m elf_i386 -T linker.ld $(OBJS) -o $(KERNEL)

$(ISO): $(KERNEL) iso/boot/grub/grub.cfg
	cp $(KERNEL) iso/boot/kernel.bin
	grub-mkrescue -d $(GRUBDIR) -o $(ISO) iso

clean:
	rm -f kernel/*.o boot.o gdt_flush.o $(KERNEL)
	rm -f iso/boot/kernel.bin

fclean: clean
	rm -f $(ISO)

re: fclean all