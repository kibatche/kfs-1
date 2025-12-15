NAME = libk.a
RM = rm -rf

INCLUDE_DIRS = drivers/video fs drivers/tty

SRCS = itoa.c uitoa.c uitoa_base.c
SRCS += bzero.c memchr.c memcpm.c memcpy.c memmove.c memset.c strchr.c \
	strcmp.c strcpy.c strlen.c
SRCS += putchar.c puts.c printf.c

OBJ_DIR = obj
OBJ_FILES = ${SRCS:.c=.o}
OBJS = $(addprefix $(OBJ_DIR)/, $(OBJ_FILES))

VPATH = itoa string stdio

AR = i386-elf-ar
ARFLAGS = -rcs
CC = i386-elf-gcc
CFLAGS = -c -Wall -Wextra -std=gnu99 -ffreestanding -nostdlib -nodefaultlibs
CPPFLAGS = -I./include $(foreach dir, $(addprefix ../include/, $(INCLUDE_DIRS)), -I$(dir))

all: ${NAME}

${OBJ_DIR}:
	@mkdir -p $@

$(NAME): ${OBJ_DIR} ${OBJS}
	${AR} ${ARFLAGS} ${NAME} ${OBJS}

${OBJ_DIR}/%.o: %.c
	${CC} ${CFLAGS} ${CPPFLAGS} $< -o $@

bonus: ${NAME}

clean:
	${RM} ${OBJ_DIR}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
