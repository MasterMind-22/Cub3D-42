NAME = cub3D
LIB = cub3d.h
Minilibx = libmlx.a
Framework_linux = -Lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
Framework_macos = -lmlx -framework OpenGL -framework AppKit

SRCS =	parsing.c \
		./libft_utils/libft_utils.c \
		./libft_utils/libft_utils1.c \
		./libft_utils/ft_split.c \
		./libft_utils/get_next_line.c \
		./libft_utils/get_next_line_utils.c \
		cub3d.c \

OBJS = ${SRCS:.c=.o}
CC = cc
# CFLAGS = -Wall -Wextra -Werror+

all : ${NAME}

$(NAME) : $(OBJS)
		$(CC) $(OBJS) $(Framework_macos)  -o $(NAME)

clean :
	@ rm -f ${OBJS}

fclean : clean
	@ rm -f ${NAME}

re : fclean all