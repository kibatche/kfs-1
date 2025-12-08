GCC = i386-elf-gcc
AR = i386-elf-ar
CCFLAGS = -c -Wall -Wextra -std=gnu99 -ffreestanding -nostdlib -nodefaultlibs
RM = rm -f

SRCS_ITOA = _itoa/_itoa.c _itoa/_itoa_base.c

SRCS_STRING = string/bzero.c string/memchr.c string/memcpm.c string/memcpy.c string/memmove.c string/memset.c \
	      string/strchr.c string/strcmp.c string/strcpy.c string/strlen.c

SRCS_STDIO = stdio/putchar.c stdio/puts.c stdio/printf.c

SRCS_UNISTD = unistd/write.c

SRCS += ${SRCS_ITOA}
SRCS += ${SRCS_STRING}
SRCS += ${SRCS_STDIO}
SRCS += ${SRCS_UNISTD}

OBJS = ${SRCS:.c=.o}
NAME = libk.a

all: ${NAME}

$(NAME): ${OBJS}
	${AR} -rcs ${NAME} ${OBJS}

%.o: %.c
	${GCC} ${CCFLAGS} $< -o $@ -I ./include -I ../kernel/include/

bonus:	${NAME}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
