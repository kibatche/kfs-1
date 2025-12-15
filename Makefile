GCC = i386-elf-gcc
#-02 : opitmisation; -g: debug
CFLAGS=-O2 -g
CFLAGS += -Wall -Wextra
#-std=gnu99: standard C gnu99; -ffreestanding : pas de std et point d'entree pas forcement main
CFLAGS += -std=gnu99 -ffreestanding
#-fno-builtin: pas de remplacement de fonction par des version GCC ; -fno-stack-protector: pas de protection de la stack
CFLAGS += -fno-builtin -fno-stack-protector
CFLAGS += -nostdlib -nodefaultlibs

NASM=nasm
NASM_FLAGS=-f elf

RM=rm -rf

INCLUDE = -I ./include/drivers/video -I ./include/fs -I ./include/drivers/tty -I ./libk/include -I ./arch/i386/include


LIB = -L./libk -lk -lgcc

PREFIX_BOOT = arch/i386/boot
PREFIX_TTY = drivers/tty
PREFIX_KERNEL = kernel
PREFIX_FS = fs

SRCS_C = ${PREFIX_KERNEL}/kernel.c
SRCS_C += ${PREFIX_TTY}/tty.c
SRCS_C += ${PREFIX_FS}/write.c
SRCS_ASM = ${PREFIX_BOOT}/boot.asm

OBJS_C=${SRCS_C:.c=.o}
OBJS_ASM=${SRCS_ASM:.asm=.o}

LINK=-T ./arch/i386/linker.ld

NAME=kernel.bin

NAME_ISO = kernel.iso

LIB_EXE=libk.a

all: ${LIB_EXE} ${NAME} ${NAME_ISO}

${LIB_EXE}:
	${MAKE} -C libk

${NAME}: ${OBJS_C} ${OBJS_ASM}
	${GCC} ${CFLAGS}  ${OBJS_C} ${OBJS_ASM} ${LINK} -o ${NAME} ${INCLUDE} ${LIB}
%.o: %.c
	${GCC} ${CFLAGS} -c $< -o $@ ${INCLUDE}


%.o: %.asm
	${NASM} ${NASM_FLAGS} $< -o $@

${NAME_ISO}:
	@mkdir -p iso/boot/grub
	@cp grub.cfg iso/boot/grub
	@cp kernel.bin iso/boot
	@grub-mkrescue -o kernel.iso iso
	@qemu-system-i386 -cdrom kernel.iso
clean:
	${RM} ${OBJS_C} ${OBJS_ASM}
	${MAKE} -C libk clean

fclean: clean
	${RM} ${NAME} ${NAME_ISO} iso
	${MAKE} -C libk fclean

re: fclean all
.PHONY: fclean clean all re
