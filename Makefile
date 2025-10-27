# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/31 07:51:02 by nistanoj          #+#    #+#              #
#    Updated: 2025/10/27 08:16:08 by nistanoj         ###   ########.fr        #
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
DEPFLAGS	=	-MMD -MP
COMPILE		=	$(CC) $(CFLAGS) $(DEPFLAGS)
RM			=	rm -rf
# CFLAGS 		+=	-fsanitize=address -g

SRCS_DIR	=	srcs/
CORE_DIR	=	core/
PARSE_DIR	=	parse/
DRAW_DIR	=	draw/
HOOKS_DIR	=	hooks/
PROJECT_DIR	=	project/
VIEW_DIR	=	view/
UTILS_DIR	=	utils/
OBJS_DIR	=	obj/

CORE_SRC	=	main.c \
				init.c
DRAW_SRC	=	image.c \
				line.c \
				render.c
HOOKS_SRC	=	hooks.c \
				hooks_mouse.c \
				hooks_release.c \
				hooks_rotation.c
PROJECT_SRC	=	project.c \
				project2.c \
				project3.c \
				project4.c
PARSE_SRC	=	parse.c \
				parse_utils.c
UTILS_SRC	=	utils_1.c \
				utils_2.c \
				utils_color.c \
				utils_loop.c
VIEW_SRC	=	view.c \
				hud.c \
				hud_keys.c \
				hud_status.c

SRCS		=	$(addprefix $(CORE_DIR), $(CORE_SRC)) \
				$(addprefix $(DRAW_DIR), $(DRAW_SRC)) \
				$(addprefix $(HOOKS_DIR), $(HOOKS_SRC)) \
				$(addprefix $(PROJECT_DIR), $(PROJECT_SRC)) \
				$(addprefix $(PARSE_DIR), $(PARSE_SRC)) \
				$(addprefix $(UTILS_DIR), $(UTILS_SRC)) \
				$(addprefix $(VIEW_DIR), $(VIEW_SRC))
OBJS		=	$(SRCS:%.c=$(OBJS_DIR)%.o)
DEPS 		=	$(OBJS:.o=.d)

RED			=	\033[0;31m
GREEN		=	\033[0;32m
L_GREEN		=	\033[1;32m
YELLOW		=	\033[0;33m
BLUE		=	\033[0;34m
MAGENTA		=	\033[0;35m
CYAN		=	\033[0;36m
BOLD		=	\033[1m
RESET		=	\033[0m

all:			$(NAME)
	@echo "$(GREEN)[ ✓ ] Everything is up to date.$(RESET)"

$(LIBFT_A): FORCE
	@$(MAKE) -s -C $(LIBFT)

$(MLX_A): FORCE
	@$(MAKE) -s -C $(MLX) 2> /dev/null || echo \
	"$(YELLOW)[ ! ] MiniLibX build skipped (not found).$(RESET)"

FORCE:

$(NAME):		$(OBJS) $(LIBFT_A) $(MLX_A)
	@echo "$(CYAN)[ ℹ ] Building $(BOLD)$(NAME)...$(RESET)"
	@$(COMPILE) $(OBJS) $(LIBFT_A) $(MLX_A) -lXext -lX11 -lm -o $(NAME)
	@echo "$(GREEN)[ ✓ ] Build successful.$(RESET)"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)[ ℹ ] Compiling $(BOLD)$<...$(RESET)"
	@$(COMPILE) -I$(INCLUDE) -c $< -o $@

-include $(DEPS)

mlx:
	@if [ -d "$(MLX)" ]; then \
		echo "$(GREEN)[ ✓ ] MiniLibX already exists.$(RESET)"; \
	else \
		echo "$(CYAN)[ ℹ ] Downloading mlx from 42paris REPO...$(RESET)"; \
		git clone https://github.com/42paris/minilibx-linux.git; \
		cd $(MLX) && bash configure | tail -3 && cd ..; \
		make -s re; \
	fi

norminette:
	@echo "$(CYAN)[ ℹ ] Running norminette $(BOLD)BY NISTANOJ...$(RESET)"
	@if command -v norminette > /dev/null 2>&1; then \
		NORM_CMD="norminette"; \
	elif command -v python3 -m norminette > /dev/null 2>&1; then \
		NORM_CMD="python3 -m norminette"; \
	else \
		echo "$(RED)[ ✗ ] Norminette is not installed.$(RESET)"; \
		echo "$(CYAN)[ ℹ ] Norminette check uncompleted.$(RESET)"; \
		exit 1; \
	fi; \
	TARGET="$(filter-out $@,$(MAKECMDGOALS))"; \
	if [ -z "$$TARGET" ]; then \
		TARGET="."; \
	else \
		echo "$(YELLOW)[ ℹ ] Checking target(s): $(BOLD)$$TARGET$(RESET)"; \
	fi; \
	OUTPUT=$$($$NORM_CMD $$TARGET 2>&1) ; \
	OUTPUT=$$(echo "$$OUTPUT" | sed '/Setting locale/d'); \
	FILTERED=$$(echo "$$OUTPUT" | grep -v ": OK!"); \
	if [ -n "$${FILTERED}" ]; then \
		echo "$$OUTPUT" | grep -v ": OK!"; \
		echo "$(RED)[ ✗ ] Norminette found errors !$(RESET)"; \
		exit 1; \
	else \
		echo "$(GREEN)[ ✓ ] Norminette $(BOLD)passed !$(RESET)"; \
		exit 0; \
	fi; \
	exit 0;

test:
	@echo "$(CYAN)[ ℹ ] Running tests...$(RESET)"
	@LIBX="/home/niko/42/Cursus-42/fdf/minilibx-linux/" ; \
	if [ ! -d "$$LIBX" ]; then \
		echo "$(YELLOW)[ ! ] MiniLibX not found at '$$LIBX'.$(RESET)"; \
		make -s mlx; \
	else \
		echo "$(GREEN)[ ✓ ] MiniLibX found at '$$LIBX'.$(RESET)"; \
	fi
	@echo ""
	@echo "$(CYAN)=== CHECK-UP FINAL ===$(RESET)"
	@echo ""
	@echo "$(CYAN)[ 1 ] Compilation:$(RESET)"
	@$(MAKE) -s re 2>&1 | tail -3
	@echo ""
	@echo "$(CYAN)[ 2 ] Norminette (fichiers critiques):$(RESET)"
	@$(MAKE) -s norminette srcs includes libft 2>&1 | tail -1
	@echo ""
	@echo "$(CYAN)[ 3 ] Test fonctionnel:$(RESET)"
	@if [ -d "maps/" ]; then \
		TOTAL=$$(ls maps/*.fdf 2>/dev/null | wc -l); \
		COUNT=0; \
		ESC_COUNT=0; \
		echo "$(CYAN)[ ℹ ] Testing $$TOTAL maps...$(RESET)"; \
		for file in maps/*.fdf; do \
			if [ -f "$$file" ]; then \
				COUNT=$$((COUNT + 1)); \
				echo "$(YELLOW)[ ℹ ] $$file... [$$COUNT/$$TOTAL]$(RESET)"; \
				timeout 2 ./fdf $$file > /dev/null 2>&1; \
				EXIT_CODE=$$?; \
				if [ $$EXIT_CODE -eq 0 ]; then \
					echo "$(GREEN)[ ✓ ] OK Exit code : $$EXIT_CODE $(RESET)"; \
					ESC_COUNT=$$((ESC_COUNT + 1)); \
				elif [ $$EXIT_CODE -eq 124 ]; then \
					echo "$(GREEN)[ ✓ ] OK Exit code : $$EXIT_CODE (timeout after 2s)$(RESET)"; \
				else \
					echo "$(RED)[ ✗ ] KO Exit code : $$EXIT_CODE Error$(RESET)"; \
					COUNT=$$((COUNT - 1)); \
				fi; \
			fi; \
		done; \
		echo ""; \
		if [ $$COUNT -eq $$TOTAL ]; then \
			if [ $$ESC_COUNT -gt 0 ]; then \
				echo "$(YELLOW)[ ! ] Escaped tests: $(BOLD)[$$ESC_COUNT/$$TOTAL]$(RESET)"; \
				echo ""; \
			fi; \
			echo "$(GREEN)[ ✓ ] All tests completed: $(BOLD)[$$COUNT/$$TOTAL]$(RESET)"; \
		else \
			echo "$(YELLOW)[ ! ] Escaped tests: $(BOLD)[$$ESC_COUNT/$$TOTAL]$(RESET)"; \
			echo "$(RED)[ ✗ ] Tests completed: $(BOLD)[$$COUNT/$$TOTAL]$(RESET)"; \
		fi; \
	else \
		echo "$(RED)[ ✗ ] Directory maps/ not found!$(RESET)"; \
	fi
	@echo ""
	@echo "$(CYAN)=== FIN DU CHECK-UP ===$(RESET)"

# Règle catch-all pour les arguments de norminette
%:
	@:

clean:
	@echo "$(RED)[🧹 ] Removing object files...$(RESET)"
	@$(MAKE) clean -s -C $(LIBFT)
	@$(MAKE) clean -s -C $(MLX)
	@$(RM) $(OBJS_DIR)

fclean:			clean
	@$(MAKE) fclean -s -C $(LIBFT)
	@echo "$(RED)[🧹 ] Removing $(BOLD)$(NAME)...$(RESET)"
	@$(RM) $(NAME)

mlx_clean:
	@echo "$(RED)[🧹 ] Removing $(BOLD)$(MLX)...$(RESET)"
	@${RM} $(MLX)
	@echo "$(YELLOW)[ ! ] Run 'make mlx' to build again ...$(RESET)"

re:				fclean all

bonus:			all

.PHONY:			all mlx norminette test clean fclean mlx_clean re bonus

# Règle silencieuse pour les arguments passés après une règle make
ifeq (norminette,$(firstword $(MAKECMDGOALS)))
  NORM_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  .PHONY: $(NORM_ARGS)
  $(NORM_ARGS):
	@:
endif
