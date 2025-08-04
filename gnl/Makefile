# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/31 08:34:28 by nistanoj          #+#    #+#              #
#    Updated: 2025/08/04 17:01:42 by nistanoj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libgnl.a

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
COMPILE		=	$(CC) $(CFLAGS)
RM			=	rm -f

SRCS		=	get_next_line.c get_next_line_utils.c
OBJS		=	$(SRCS:%.c=%.o)

all:			$(NAME)

$(NAME):		$(OBJS)
	@ar rc $(NAME) $(OBJS)

clean:
	@$(RM) $(OBJS)

fclean:			clean
	@$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re
