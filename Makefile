# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/31 07:51:02 by nistanoj          #+#    #+#              #
#    Updated: 2025/09/03 16:14:12 by nistanoj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	fdf

HEADER		=	includes

LIBFT		=	libft/
MLX			=	minilibx-linux/
LIBFT_A		=	$(addprefix $(LIBFT), libft.a)
MLX_A		=	$(addprefix $(MLX), libmlx.a)

INC_DIR		=	includes \
				libft \
				minilibx-linux
INCLUDE		=	$(addprefix -I, $(INC_DIR))

CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra -I$(INCLUDE) -ggdb
COMPILE		=	$(CC) $(CFLAGS)
RM			=	rm -rf
# CFLAGS 		+=	-fsanitize=address -g

SRCS_DIR	=	srcs/
SRCS		=	$(SRCS_DIR)main.c \
				$(SRCS_DIR)init.c \
				$(SRCS_DIR)parse/parse.c \
				$(SRCS_DIR)parse/parse_utils.c \
				$(SRCS_DIR)draw/image.c \
				$(SRCS_DIR)draw/line.c \
				$(SRCS_DIR)draw/project.c \
				$(SRCS_DIR)draw/render.c \
				$(SRCS_DIR)view/view.c \
				$(SRCS_DIR)view/hooks.c \
				$(SRCS_DIR)utils/utils_1.c \
				$(SRCS_DIR)utils/utils_2.c
OBJS		=	$(SRCS:%.c=%.o)

all:			$(NAME)

$(NAME):		$(OBJS) $(LIBFT_A) $(MLX_A)
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT) -lft -L$(MLX) -lmlx -lXext -lX11 \
	-lm -o $(NAME)
	@echo "Linked into executable \033[1;32m$(NAME)\033[0m."

$(LIBFT_A):
	@make -s -C $(LIBFT)

$(MLX_A):
	@make -s -C $(MLX)

.c.o:
	@$(COMPILE) -c $< -o $(<:.c=.o)
	@echo "Compiling \033[1;32m$<\033[0m."

norminette:
	@norminette $(SRCS) $(HEADER) $(LIBFT)
	@echo "\033[1;32mNorminette check completed.\033[0m"

clean:
	@make clean -s -C $(LIBFT)
	@make clean -s -C $(MLX)
	@$(RM) $(OBJS)
	@echo "\033[1;32mOBJ file removed.\033[0m"

fclean:			clean
	@make fclean -s -C $(LIBFT)
	@$(RM) $(NAME)
	@echo "\033[1;32mExecutable removed.\033[0m"

re:				fclean all

bonus:			all

.PHONY:			all norminette clean fclean re bonus
