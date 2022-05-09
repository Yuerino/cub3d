SHELL	= /bin/sh

NAME	= libft.a

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

IDIR	= .
IFLAGS	= -I${IDIR}

SRCS	= ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_striteri.c \
			ft_memchr.c ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strlcat.c \
			ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_atoi.c \
			ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
			ft_toupper.c ft_tolower.c ft_calloc.c ft_strdup.c ft_substr.c \
			ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
OBJS	= ${SRCS:.c=.o}

BSRCS	= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
			ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
			ft_lstmap.c
BOBJS	= ${BSRCS:.c=.o}

ESRCS	= get_next_line.c ft_abs.c ft_swap_int.c ft_max.c ft_min.c
EOBJS	= ${ESRCS:.c=.o}

AR		= ar rcs
RM		= rm -f

.PHONY: all clean fclean re bonus extra

%.o : %.c
		${CC} ${CFLAGS} ${IFLAGS} -c $< -o $@

${NAME}: ${OBJS}
		${AR} ${NAME} ${OBJS}

all: ${NAME}

clean:
		${RM} ${OBJS} ${BOBJS} ${EOBJS}

fclean: clean
		${RM} ${NAME}

re: fclean all

bonus: ${OBJS} ${BOBJS}
		${AR} ${NAME} ${OBJS} ${BOBJS}

extra: ${OBJS} ${BOBJS} ${EOBJS}
		${AR} ${NAME} ${OBJS} ${BOBJS} ${EOBJS}
