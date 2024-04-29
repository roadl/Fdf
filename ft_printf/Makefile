# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yojin <yojin@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/08 19:36:06 by yojin             #+#    #+#              #
#    Updated: 2024/01/07 16:30:07 by yojin            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
LDIR = ./
LIBFT = libft.a
LIBFTDIR = ./libft
HEADER = ./ft_printf.h ./libft/libft.h
SRCS = ft_printf.c ft_putptr.c ft_putunbr.c ft_puthex.c ft_putstr.c
OBJS = $(SRCS:.c=.o)
NAME = libftprintf.a

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFTDIR)
	cp $(LIBFTDIR)/$(LIBFT) $(NAME)
	ar rc $(NAME) $(OBJS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(LDIR)

re: fclean all

clean:
	make -C $(LIBFTDIR) clean
	rm -f $(OBJS)

fclean: clean
	make -C $(LIBFTDIR) fclean
	rm -f $(NAME)

.PHONY: all re clean fclean
