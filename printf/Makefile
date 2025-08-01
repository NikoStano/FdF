# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/27 16:32:33 by nistanoj          #+#    #+#              #
#    Updated: 2025/07/31 09:38:38 by nistanoj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libftprintf.a

CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra
COMPILE		=	$(CC) $(CFLAGS)
RM			=	rm -f

SRCS		=	ft_printf.c ft_putchar.c ft_putstr.c ft_putnbr.c \
				ft_print_ptr.c ft_print_hex.c
OBJS		=	$(SRCS:%.c=%.o)

all		:	$(NAME)

$(NAME)	:	$(OBJS)
	@ar rc $@ $^

clean	:
	@$(RM) $(OBJS)

fclean	:	clean
	@$(RM) $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re
