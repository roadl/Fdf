# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yojin <yojin@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/25 13:02:18 by yojin             #+#    #+#              #
#    Updated: 2024/03/11 16:36:59 by yojin            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR)
MLXFLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit
FT_PRINTF_DIR = ./ft_printf
FT_PRINTF = libftprintf.a
INC_DIR = ./include
SRC_DIR = ./src
MLX_DIR = ./mlx
MLX = libmlx.a
HEADER = $(INC_DIR)/fdf.h
SRCS =	src/fdf.c src/fdf_util.c src/fdf_parse.c src/fdf_draw.c src/fdf_color.c \
		src/fdf_event.c gnl/get_next_line.c gnl/get_next_line_utils.c
OBJS = $(SRCS:.c=.o)
NAME = fdf

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(FT_PRINTF_DIR) -j 8
	make -C $(MLX_DIR) -j 8
	$(CC) $(CFLAGS) $(MLXFLAGS) $^ -o $(NAME) $(FT_PRINTF_DIR)/$(FT_PRINTF) $(MLX_DIR)/$(MLX)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

re: fclean all

clean:
	make -C $(FT_PRINTF_DIR) clean
	make -C $(MLX_DIR) clean
	rm -f $(OBJS)

fclean: clean
	make -C $(FT_PRINTF_DIR) fclean
	rm -f $(NAME)

.PHONY: all re clean fclean
