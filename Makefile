NAME	= cub3d

WIN_WIDTH	= 1920
WIN_HEIGHT	= 1080

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror $(DFLAGS) -g
DFLAGS	= -D WIN_WIDTH=$(WIN_WIDTH) -D WIN_HEIGHT=$(WIN_HEIGHT)

MINILIBX_DIR	= minilibx-linux
LIBFT_DIR		= libft
X11_INC			= /usr/X11/include
X11_LIB			= /usr/X11/lib

LFLAGS	= -L$(LIBFT_DIR) -L$(MINILIBX_DIR) -L$(X11_LIB) -lft -lmlx -lXext -lX11 -lm

HEADERS	= cub3d.h input_handler.h utils.h controls.h rendering.h
IDIR	= includes/
IFLAGS	= -I$(IDIR) -I$(LIBFT_DIR) -I$(MINILIBX_DIR) -I$(X11_INC)

SRCS	= cub3d.c srcs/controls.c srcs/mouse_controls.c \
		$(addprefix $(IH_PATH),$(IH_SRCS)) \
		$(addprefix $(UTIL_PATH),$(UTIL_SRCS)) \
		$(addprefix $(RD_PATH),$(RD_SRCS))

IH_PATH	= srcs/input_handler/
IH_SRCS	= init.c read.c read_map.c validate_map.c free.c read_texture.c

RD_PATH	= srcs/rendering/
RD_SRCS	= putimg.c minimap.c cast_rays.c

UTIL_PATH		= utils/
UTIL_SRCS		= error.c carray.c image.c color.c is_ext_valid.c \
					is_nbr.c put_pixel.c

RM		= rm -f

.PHONY: all clean fclean re norm

$(NAME): $(SRCS) $(addprefix $(IDIR),$(HEADERS)) Makefile
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

norm:
		@norminette $(SRCS) $(addprefix $(IDIR),$(HEADERS))
