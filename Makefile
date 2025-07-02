# Object and source path directories
OBJ_PATH = obj/
LIBFT_PATH = libft/
MLX_DIR = ./mlx
BONUS_DIR = bonus/
BONUS_OBJ_PATH = $(OBJ_PATH)

# Program & build names
NAME = so_long
BONUS_NAME = so_long_bonus
LIBFT = $(LIBFT_PATH)libft.a
MLX_LIB = $(MLX_DIR)/libmlx.a

# Program sauce files
SRC = ./so_long.c map_parser.c error_handler.c map_validator.c map_path_validator.c map_utils.c \
hooks_setup_and_events.c map_drawer.c \

SRC_BONUS = ./so_long_bonus.c map_parser.c error_handler.c map_validator.c map_path_validator.c map_utils.c \
$(BONUS_DIR)hooks_setup_and_events_bonus.c $(BONUS_DIR)animation_bonus.c map_drawer.c \

# Object files
OBJ = $(SRC:%.c=$(OBJ_PATH)%.o)
OBJ_BONUS = $(patsubst %.c,$(OBJ_PATH)%.o,$(notdir $(SRC_BONUS)))

# Compiler n flags
CC		=		cc
CFLAGS	= -Wall -Werror -Wextra -I. -I$(MLX_DIR) -I$(BONUS_DIR)

ifeq ($(shell uname), Linux)
	MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11
	SRC += cleanup_linux.c
	SRC_BONUS += $(BONUS_DIR)cleanup_linux_bonus.c
else
	MLX_FLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit
	SRC += cleanup_mac.c
	SRC_BONUS += $(BONUS_DIR)cleanup_mac_bonus.c
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
SPINNERBONUS = \
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
			printf "\r$(WHITE)$(BONUS_NAME) Make on the way... $$c"; \
			i=$$(expr $$i + 1); \
			sleep 0.1; \
		done; \
		printf "\r\033[K$(WHITE)$(BONUS_NAME) program is $(BGREEN)ready! ✅\033[0m\n"; \
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

bonus: $(BONUS_OBJ_PATH) $(LIBFT) $(MLX_LIB) $(BONUS_NAME)

$(BONUS_NAME): $(OBJ_BONUS) $(LIBFT) $(MLX_LIB)
	@{ \
		$(CC) $(CFLAGS) $(OBJ_BONUS) $(MLX_FLAGS) $(LIBFT) -o $(BONUS_NAME); \
	} & \
	$(SPINNERBONUS)

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

$(BONUS_OBJ_PATH)%.o : $(BONUS_DIR)%.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJ_PATH)
	@make clean -C $(LIBFT_PATH)
	@make clean -C $(MLX_DIR)
	@echo "$(BGREEN)cleaned like the blackhole you're getting if you DON'T GET TO COOKING$(WHITE)"

fclean: clean
	@rm -f $(NAME) $(BONUS_NAME)
	@rm -f $(LIBFT)

re: fclean all

.PHONY: all clean fclean re