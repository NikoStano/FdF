# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/31 07:51:02 by nistanoj          #+#    #+#              #
#    Updated: 2025/08/13 12:54:40 by nistanoj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	FdF

INCLUDE		=	includes

LIBFT		=	lib/libft/
GNL			=	lib/gnl/
PRINTF		=	lib/printf/
MLX			=	lib/minilibx/
LIBFT_A		=	$(addprefix $(LIBFT), libft.a)
GNL_A		=	$(addprefix $(GNL), libgnl.a)
PRINTF_A	=	$(addprefix $(PRINTF), libprintf.a)
MLX_A		=	$(addprefix $(MLX), libmlx.a)

CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra -I$(INCLUDE)
COMPILE		=	$(CC) $(CFLAGS)
RM			=	rm -f

SRCS_DIR	=	srcs/
# SRCS		=	test.c
SRCS		=	$(SRCS_DIR)fdf.c \
				$(SRCS_DIR)fdf_utils.c \
 				$(SRCS_DIR)draw_map.c \
				$(SRCS_DIR)parse.c \
				$(SRCS_DIR)hook_check.c \
				$(SRCS_DIR)points.c \
				$(SRCS_DIR)view.c

OBJS		=	$(SRCS:%.c=%.o)

all:			$(NAME)

$(NAME):		$(OBJS) $(LIBFT_A) $(GNL_A) $(PRINTF_A) $(MLX_A)		
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT) -lft -L$(PRINTF) -lprintf -L$(GNL) \
	-lgnl -L$(MLX) -lmlx -lXext -lX11 -lm -o $(NAME)
	@echo "Linked into executable \033[0;32mFdF\033[0m."

$(LIBFT_A):
	@make -s -C $(LIBFT)

$(GNL_A):
	@make -s -C $(GNL)

$(PRINTF_A):
	@make -s -C $(PRINTF)

$(MLX_A):
	@make -s -C $(MLX)

bonus:			all

.c.o:
	@$(COMPILE) -c $< -o $(<:.c=.o)
	@echo "Compiling $<."

localclean:
	@$(RM) $(OBJS)
	@echo "Removed object files."

clean:			localclean
	@make clean -s -C $(LIBFT)
	@make clean -s -C $(GNL)
	@make clean -s -C $(PRINTF)
	@make clean -s -C $(MLX)

fclean:			clean
	@make fclean -s -C $(LIBFT)
	@make fclean -s -C $(GNL)
	@make fclean -s -C $(PRINTF)
	@$(RM) $(NAME)
	@echo "Removed executable."

re:				fclean all

.PHONY:			all clean fclean re localclean bonus
