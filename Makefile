# Object and source path directories
OBJ_PATH = obj/
LIBFT_PATH = libft/
MLX_DIR = ./mlx

# Program & build names
NAME = so_long
LIBFT = $(LIBFT_PATH)libft.a
MLX_LIB = $(MLX_DIR)/libmlx.a

# Program sauce files
SRC = ./so_long.c map_parser.c error_handler.c map_validator.c map_path_validator.c map_utils.c \

# Object files
OBJ = $(SRC:%.c=$(OBJ_PATH)%.o)

# Compiler n flags
CC		=		cc
CFLAGS	= -Wall -Werror -Wextra -I. -I$(MLX_DIR)

ifeq ($(shell uname), Linux)
	MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11
else
	MLX_FLAGS = -Lmlx -lmlx -L/usr/X11/lib -lXext -lX11 -framework OpenGL -framework AppKit
endif

# Compiler colors ✨
RED=\033[0;31m
GREEN=\033[0;32m
BGREEN=\033[1;32m
YELLOW=\033[0;33m
WHITE=\033[0;37m

# hide directory check (linux thing)
MAKEFLAGS += --no-print-directory

# Compiler loading animation for $(NAME) (with a lil RGB magic ✨)
SPINNER = \
	( \
		i=0; \
		while kill -0 $$! 2>/dev/null; do \
			case $$((i % 6)) in \
				0) c="\033[0;31m|" ;; \
				1) c="\033[0;33m/" ;; \
				2) c="\033[0;32m-" ;; \
				3) c="\033[0;36m\\" ;; \
				4) c="\033[0;34m|" ;; \
				5) c="\033[0;35m/" ;; \
			esac; \
			printf "\r$(WHITE)$(NAME) Make on the way... $$c"; \
			i=$$(expr $$i + 1); \
			sleep 0.1; \
		done; \
		printf "\r\033[K$(WHITE)$(NAME) program is $(BGREEN)ready! ✅\033[0m\n"; \
	)
# Compiler loading animation for Libft
SPINNERLIB = \
	( \
		i=0; \
		while kill -0 $$! 2>/dev/null; do \
			case $$((i % 6)) in \
				0) c="\033[0;31m|" ;; \
				1) c="\033[0;33m/" ;; \
				2) c="\033[0;32m-" ;; \
				3) c="\033[0;36m\\" ;; \
				4) c="\033[0;34m|" ;; \
				5) c="\033[0;35m/" ;; \
			esac; \
			printf "\r$(WHITE)libft Make on the way... $$c"; \
			i=$$(expr $$i + 1); \
			sleep 0.1; \
		done; \
		printf "\r\033[K$(WHITE)libft is $(BGREEN)ready! ✅\033[0m\n"; \
	)
# Compiler loading animation for minilibx
SPINNERMLX = \
	( \
		i=0; \
		while kill -0 $$! 2>/dev/null; do \
			case $$((i % 6)) in \
				0) c="\033[0;31m|" ;; \
				1) c="\033[0;33m/" ;; \
				2) c="\033[0;32m-" ;; \
				3) c="\033[0;36m\\" ;; \
				4) c="\033[0;34m|" ;; \
				5) c="\033[0;35m/" ;; \
			esac; \
			printf "\r$(WHITE)minilibx Make on the way... $$c"; \
			i=$$(expr $$i + 1); \
			sleep 0.1; \
		done; \
		printf "\r\033[K$(WHITE)minilibx is $(BGREEN)ready! ✅\033[0m\n"; \
	)

# Build magicc
all: $(OBJ_PATH) $(LIBFT) $(MLX_LIB) $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX_LIB)
	@{ \
		$(CC) $(CFLAGS) $(OBJ) $(MLX_FLAGS) $(LIBFT) -o $(NAME); \
	} & \
	$(SPINNER)

$(LIBFT):
	@{ \
		make -C $(LIBFT_PATH); \
	} & \
	$(SPINNERLIB)

$(MLX_LIB):
	@{ \
		make -C $(MLX_DIR); \
	} & \
	$(SPINNERMLX)

$(OBJ_PATH)%.o : %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

clean:
	@rm -rf $(OBJ_PATH)
	@make clean -C $(LIBFT_PATH)
	@make clean -C $(MLX_DIR)
	@echo "$(BGREEN)cleaned like the blackhole you're getting if you DON'T GET TO COOKING$(WHITE)"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT)

re: fclean all

.PHONY: all clean fclean re