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

INCLUDE = -I ./kernel/include -I ./libc/include


LIB = -L./libc -lk -lgcc

PREFIX = kernel/kernel
PREFIX_ASM = ${PREFIX}/assembly

SRCS_C = ${PREFIX}/kernel.c kernel/tty/tty.c
SRCS_ASM = ${PREFIX_ASM}/boot.asm

OBJS_C=${SRCS_C:.c=.o}
OBJS_ASM=${SRCS_ASM:.asm=.o}

LINK=-T ./kernel/linker.ld

NAME=kernel.bin

LIB_EXE=libk.a

all: ${LIB_EXE} ${NAME}

${LIB_EXE}:
	${MAKE} -C libc

${NAME}: ${OBJS_C} ${OBJS_ASM}
	${GCC} ${CFLAGS}  ${OBJS_C} ${OBJS_ASM} ${LINK} -o ${NAME} ${INCLUDE} ${LIB}
%.o: %.c
	${GCC} ${CFLAGS} -c $< -o $@ ${INCLUDE}


%.o: %.asm
	${NASM} ${NASM_FLAGS} $< -o $@

clean:
	${RM} ${OBJS_C} ${OBJS_ASM}
	${MAKE} -C libc clean

fclean: clean
	${RM} ${NAME}
	${MAKE} -C libc fclean

re: fclean all
.PHONY: fclean clean all re
