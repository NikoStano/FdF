# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/26 16:35:06 by nistanoj          #+#    #+#              #
#    Updated: 2025/10/26 15:49:17 by nistanoj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	libft.a

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror -ggdb
DEPFLAGS	=	-MMD -MP
COMPILE		=	$(CC) $(CFLAGS) $(DEPFLAGS)
RM			=	rm -rf

SRCS			=	ft_atoi.c \
					ft_bzero.c \
					ft_calloc.c \
					ft_isalnum.c \
					ft_isalpha.c \
					ft_isascii.c \
					ft_isdigit.c \
					ft_isprint.c \
					ft_strchr.c \
					ft_strdup.c \
					ft_strlcat.c \
					ft_strlcpy.c \
					ft_strlen.c \
					ft_strncmp.c \
					ft_strnstr.c \
					ft_strrchr.c \
					ft_tolower.c \
					ft_toupper.c \
					ft_memset.c \
					ft_putchar_fd.c \
					ft_putstr_fd.c \
					ft_putendl_fd.c \
					ft_putnbr_fd.c \
					ft_memcpy.c \
					ft_memmove.c \
					ft_memchr.c \
					ft_memcmp.c \
					ft_strjoin.c \
					ft_split.c \
					ft_itoa.c \
					ft_substr.c \
					ft_strtrim.c \
					ft_strmapi.c \
					ft_striteri.c \
					ft_lstnew_bonus.c \
					ft_lstadd_front_bonus.c \
					ft_atoi_base.c \
					ft_lstsize_bonus.c \
					ft_lstlast_bonus.c \
					ft_isspace.c\
					ft_lstadd_back_bonus.c \
					ft_lstdelone_bonus.c \
					ft_strtol.c \
					ft_lstclear_bonus.c \
					ft_lstiter_bonus.c \
					ft_lstmap_bonus.c \
					get_next_line.c \
					get_next_line_utils.c \
					ft_print_char.c \
					ft_print_str.c \
					ft_print_nbr.c \
					ft_print_hex.c \
					ft_print_ptr.c \
					ft_printf.c \

DIR_OBJ			=	obj/
OBJS				=	$(SRCS:%.c=$(DIR_OBJ)%.o)
DEPS		=	$(OBJ:.o=.d)

RED			=	\033[0;31m
GREEN		=	\033[0;32m
L_GREEN		=	\033[1;32m
YELLOW		=	\033[0;33m
BLUE		=	\033[0;34m
MAGENTA		=	\033[0;35m
CYAN		=	\033[0;36m
BOLD		=	\033[1m
RESET		=	\033[0m

all:	$(NAME)

$(NAME):	$(OBJS)
	@echo "$(CYAN)[ ℹ ] Creating $(BOLD)$(NAME)...$(RESET)"
	@ar rcs $@ $^
	@echo "$(GREEN)[ ✓ ]$(BOLD) $(NAME) $(GREEN)created successfully.$(RESET)"

$(DIR_OBJ)%.o:	%.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)[ ℹ ] Compiling $(BOLD)$< ...$(RESET)"
	@$(COMPILE) -o $@ -c $<

-include $(DEPS)

clean:
	@$(RM) $(DIR_OBJ)

fclean:	clean
	@echo "$(RED)[🧹 ] Removing $(BOLD)$(NAME)...$(RESET)"
	@$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
