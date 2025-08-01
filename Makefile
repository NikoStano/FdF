# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/31 07:51:02 by nistanoj          #+#    #+#              #
#    Updated: 2025/07/31 09:47:44 by nistanoj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	FdF
INCLUDE		=	includes
LIBFT		=	libft/
PRINTF		=	printf/
GNL			=	gnl/
MLX			=	minilibx/
LIBFT_A		=	$(addprefix $(LIBFT), libft.a)
PRINTF_A	=	$(addprefix $(PRINTF), libftprintf.a)
GNL_A		=	$(addprefix $(GNL), libgnl.a)
MLX_A		=	$(addprefix $(MLX), libmlx.a)

CC			=	cc
CFLAGS		=	-Wall-Werror-Wextra -I$(INCLUDE)
COMPILE		=	$(CC) $(CFLAGS)
RM			=	rm -f

SRCS		=	fdf.c main.c

OBJS		=	$(SRCS:%.c=%.o)

all:			$(NAME)

$(NAME):		$(OBJS) $(LIBFT_A) $(PRINTF_A) $(GNL_A) $(MLX_A)		
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT) -lft -L$(PRINTF) -lftprintf -L$(GNL) \
	-lgnl -L$(MLX) -lmlx -lm -o $(NAME) -framework OpenGL -framework AppKit
	@echo "Linked into executable \033[0;32mfdf\033[0m."

$(LIBFT_A):
	@$(MAKE) -s -C $(LIBFT)
	@echo "Compiled $(LIBFT_A)."

$(PRINTF_A):
	@$(MAKE) -s -C $(PRINTF)
	@echo "Compiled $(PRINTF_A)."

$(GNL_A):
	@$(MAKE) -s -C $(GNL)
	@echo "Compiled $(GNL_A)."

$(MLX_A):
	@$(MAKE) -s -C $(MLX)
	@echo "Compiled $(MLX_A)."

bonus:			all

.c.o:
	@$(COMPILE) -c $< -o $(<:.c=.o)
	@echo "Compiling $<."

localclean:
	@$(RM) $(OBJS)
	@echo "Removed object files."

clean:			localclean
	@$(MAKE) clean -s -C $(LIBFT)
	@echo "Clean libft."
	@$(MAKE) clean -s -C $(GNL)
	@echo "Clean gnl."
	@$(MAKE) clean -s -C $(MLX)
	@echo "Clean mlx."

fclean:			clean
	@$(MAKE) fclean -s -C $(LIBFT)
	@echo "Full clean libft."
	@$(MAKE) fclean -s -C $(GNL)
	@echo "Full clean gnl."
	@$(MAKE) clean -s -C $(MLX)
	@echo "Clean mlx."
	@$(RM) $(NAME)
	@echo "Removed executable."

re:				fclean all

.PHONY:			all clean fclean re localclean bonus