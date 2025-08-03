# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/31 07:51:02 by nistanoj          #+#    #+#              #
#    Updated: 2025/08/03 02:31:48 by nistanoj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	FdF

INCLUDE		=	includes
LIBFT		=	libft/
GNL			=	gnl/
PRINTF		=	printf/
MLX			=	minilibx/
LIBFT_A		=	$(addprefix $(LIBFT), libft.a)
GNL_A		=	$(addprefix $(GNL), libgnl.a)
PRINTF_A	=	$(addprefix $(PRINTF), libprintf.a)
MLX_A		=	$(addprefix $(MLX), libmlx.a)

CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra -I$(INCLUDE)
COMPILE		=	$(CC) $(CFLAGS)
RM			=	rm -f

SRCS		=	main.c
OBJS		=	$(SRCS:%.c=%.o)

all:			$(NAME)

$(NAME):		$(OBJS) $(LIBFT_A) $(GNL_A) $(PRINTF_A) $(MLX_A)		
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT) -lft -L$(PRINTF) -lprintf -L$(GNL) \
	-lgnl -L$(MLX) -lmlx -lXext -lX11 -lm -o $(NAME)
	@echo "Linked into executable \033[0;32mfdf\033[0m."

$(LIBFT_A):
	@make -s -C $(LIBFT)
	@echo "Compiled $(LIBFT_A)."

$(GNL_A):
	@make -s -C $(GNL)
	@echo "Compiled $(GNL_A)."

$(PRINTF_A):
	@make -s -C $(PRINTF)
	@echo "Compiled $(PRINTF_A_A)."

$(MLX_A):
	@make -s -C $(MLX)
	@echo "Compiled $(MLX_A)."

bonus:			all

.c.o:
	@$(COMPILE) -c $< -o $(<:.c=.o)
	@echo "Compiling $<."

localclean:
	@$(RM) $(OBJS)
	@echo "Removed object files."

clean:			localclean
	@make clean -s -C $(LIBFT)
	@echo "Clean libft."
	@make clean -s -C $(GNL)
	@echo "Clean gnl."
	@make clean -s -C $(PRINTF)
	@echo "Clean printf."
	@make clean -s -C $(MLX)
	@echo "Clean mlx."

fclean:			clean
	@make fclean -s -C $(LIBFT)
	@echo "Full clean libft."
	@make fclean -s -C $(GNL)
	@echo "Full clean gnl."
	@make fclean -s -C $(PRINTF)
	@echo "Full clean printf."
	@make clean -s -C $(MLX)
	@echo "Clean mlx."
	@$(RM) $(NAME)
	@echo "Removed executable."

re:				fclean all

.PHONY:			all clean fclean re localclean bonus
