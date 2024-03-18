# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: momihamm <momihamm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/16 05:01:03 by momihamm          #+#    #+#              #
#    Updated: 2024/03/16 05:01:18 by momihamm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
LIB = cub3d.h raycasting.h
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
		raycasting.c \
		raycasting_utils.c \
		general_utils_0.c \
		from_a_binary_to_a_game.c \
		keys_0.c \
		imgpix.c \
		dda.c \
		ddaUtils.c \
		binary_game.c \
		directions.c \
		init_my_vars.c \
		press_and_reless.c \
		special_moves.c \
		become_3D.c	\

OBJS = ${SRCS:.c=.o}
CC = cc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address

all : ${NAME}

%.o : %.c $(LIB)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) $(Framework_macos)  -o $(NAME)

clean :
	@ rm -f ${OBJS}

fclean : clean
	@ rm -f ${NAME}

re : fclean all