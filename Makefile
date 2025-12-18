.SUFFIXES:
.SUFFIXES: .asm .c .h .o .ld

RM = rm -rf

NAME = uselOS
NAME_BIN = ${NAME}.bin
NAME_ISO = ${NAME}.iso

ISO_DIR = iso
LIBS = k gcc
LIB_DIR = libk

SRCS_C = kernel.c tty.c write.c keyboard.c
SRCS_AS = boot.asm

OBJ_DIR = obj
OBJ_FILES = ${SRCS_C:.c=.o} ${SRCS_AS:.asm=.o}
OBJS = $(addprefix $(OBJ_DIR)/, $(OBJ_FILES))

VPATH = arch/i386/boot drivers/tty drivers/keyboard kernel fs

AS = nasm
ASFLAGS = -f elf

CC = i386-elf-gcc
#-02 : opitmisation; -g: debug
CFLAGS = -O2
CFLAGS += -Wall -Wextra -Werror
#-std=gnu99: standard C gnu99; -ffreestanding : pas de std et point d'entree pas forcement main
CFLAGS += -std=gnu99 -ffreestanding
#-fno-builtin: pas de remplacement de fonction par des versions GCC ; -fno-stack-protector: pas de protection de la stack
CFLAGS += -fno-builtin -fno-stack-protector
CFLAGS += -nostdlib -nodefaultlibs
CPPFLAGS =  -I ./include/drivers/video -I ./include/drivers/tty -I ./include/drivers/keyboard -I ./include/fs -I ./libk/include -I ./arch/i386/include

LDFLAGS = -T ./arch/i386/linker.ld -L./${LIB_DIR}
LDLIBS = $(foreach lib, $(LIBS), -l$(lib))

.PHONY: install
install:
	${MAKE} -C ${LIB_DIR}

${OBJ_DIR}:
	@mkdir -p $@

${OBJ_DIR}/%.o: %.c
	${CC} ${CPPFLAGS} ${CFLAGS} -c $< -o $@

${OBJ_DIR}/%.o: %.asm
	${AS} ${ASFLAGS} $< -o $@

${NAME_BIN}: ${OBJ_DIR} ${OBJS}
	${CC} ${CFLAGS} ${OBJS} ${LDFLAGS} ${LDLIBS} -o $@

${NAME_ISO}:
	@mkdir -p ${ISO_DIR}/boot/grub
	@cp grub.cfg ${ISO_DIR}/boot/grub
	@cp ${NAME_BIN} ${ISO_DIR}/boot
	@grub-mkrescue -o ${NAME_ISO} ${ISO_DIR}

.PHONY: run
run:
	@qemu-system-i386 -cdrom ${NAME_ISO}

.PHONY: all
all: install ${NAME_BIN} ${NAME_ISO}

.PHONY: clean
clean:
	${RM} ${OBJ_DIR}

.PHONY: fclean
fclean: clean
	${RM} ${NAME_BIN} ${NAME_ISO} ${ISO_DIR}
	${MAKE} -C ${LIB_DIR} fclean

.PHONY: re
re: fclean all
