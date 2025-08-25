# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/31 07:51:02 by nistanoj          #+#    #+#              #
#    Updated: 2025/08/25 12:03:59 by nistanoj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	fdf

HEADER		=	includes

LIBFT		=	lib/libft/
GNL			=	lib/get_next_line/
PRINTF		=	lib/ft_printf/
MLX			=	lib/minilibx/
LIBFT_A		=	$(addprefix $(LIBFT), libft.a)
GNL_A		=	$(addprefix $(GNL), libgnl.a)
PRINTF_A	=	$(addprefix $(PRINTF), libprintf.a)
MLX_A		=	$(addprefix $(MLX), libmlx.a)

INC_DIR		=	includes \
				lib/libft \
				lib/get_next_line \
				lib/ft_printf \
				lib/minilibx
INCLUDE		=	$(addprefix -I, $(INC_DIR))

CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra -I$(INCLUDE)
COMPILE		=	$(CC) $(CFLAGS)
RM			=	rm -rf
# CFLAGS 		+=	-fsanitize=address -g

SRCS_DIR	=	srcs/
SRCS		=	$(SRCS_DIR)/main.c \
				$(SRCS_DIR)/init.c \
				$(SRCS_DIR)/parse/parse.c \
				$(SRCS_DIR)/parse/parse_utils.c \
				$(SRCS_DIR)/draw/image.c \
				$(SRCS_DIR)/draw/line.c \
				$(SRCS_DIR)/draw/project.c \
				$(SRCS_DIR)/draw/render.c \
				$(SRCS_DIR)/view/view.c \
				$(SRCS_DIR)/view/hooks.c \
				$(SRCS_DIR)/utils/utils_1.c \
				$(SRCS_DIR)/utils/utils_2.c
OBJS		=	$(SRCS:%.c=%.o)

all:			$(NAME)

$(NAME):		$(OBJS) $(LIBFT_A) $(GNL_A) $(PRINTF_A) $(MLX_A)		
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT) -lft -L$(PRINTF) -lprintf -L$(GNL) \
	-lgnl -L$(MLX) -lmlx -lXext -lX11 -lm -o $(NAME)
	@echo "Linked into executable \033[1;32m$(NAME)\033[0m."

$(LIBFT_A):
	@make -s -C $(LIBFT)

$(GNL_A):
	@make -s -C $(GNL)

$(PRINTF_A):
	@make -s -C $(PRINTF)

$(MLX_A):
	@make -s -C $(MLX)

.c.o:
	@$(COMPILE) -c $< -o $(<:.c=.o)
	@echo "Compiling \033[1;32m$<\033[0m."

norminette:
	@norminette $(SRCS) $(HEADER) $(LIBFT) $(GNL) $(PRINTF)
# 	@python3 -m norminette $(SRCS) $(HEADER) $(LIBFT) $(GNL) $(PRINTF)
	@echo "\033[1;32mNorminette check completed.\033[0m"

clean:
	@make clean -s -C $(LIBFT)
	@make clean -s -C $(GNL)
	@make clean -s -C $(PRINTF)
	@make clean -s -C $(MLX)
	@$(RM) $(OBJS)
	@echo "\033[1;32mOBJ file removed.\033[0m"

fclean:			clean
	@make fclean -s -C $(LIBFT)
	@make fclean -s -C $(GNL)
	@make fclean -s -C $(PRINTF)
	@$(RM) $(NAME)
	@echo "\033[1;32mExecutable removed.\033[0m"

re:				fclean all

bonus:			all

.PHONY:			all norminette clean fclean re bonus
