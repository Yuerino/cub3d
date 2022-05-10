NAME	= cub3d

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

MINILIBX_DIR	= minilibx-linux
LIBFT_DIR		= libft
X11_INC			= /usr/X11/include
X11_LIB			= /usr/X11/lib

LFLAGS	= -L$(LIBFT_DIR) -L$(MINILIBX_DIR) -L$(X11_LIB) -lft -lmlx -lXext -lX11 -lm

IDIR	= includes
IFLAGS	= -I$(IDIR) -I$(LIBFT_DIR) -I$(MINILIBX_DIR) -I$(X11_INC)

SRCS	= cub3d.c \
		$(addprefix $(IH_PATH),$(IH_SRCS)) \
		$(addprefix $(UTIL_PATH),$(UTIL_SRCS))

IH_PATH	= srcs/input_handler/
IH_SRCS	= read.c init.c

UTIL_PATH		= utils/
UTIL_SRCS		= error.c free_carray.c

RM		= rm -f

.PHONY: all clean fclean re

$(NAME): $(SRCS)
		@make -C $(MINILIBX_DIR)
		@make extra -C $(LIBFT_DIR)
		$(CC) $(CFLAGS) $(SRCS) $(IFLAGS) $(LFLAGS) -o $(NAME)

all: $(NAME)

clean:
		@$(RM) $(NAME)
		@$(RM) -r $(NAME).dSYM
		@make clean -C $(LIBFT_DIR)
		@make clean -C $(MINILIBX_DIR)

fclean: clean
		@make fclean -C $(LIBFT_DIR)

re: fclean all
