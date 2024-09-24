



NAME = fdf

CC = cc
RM = rm -rf

MLX_DIR = MLX42
MLX_BUILD_DIR = $(MLX_DIR)/build
MLX_TARGET = $(MLX_BUILD_DIR)/libmlx42.a
CFLAGS = -Wall -Wextra -Werror
MLXFLAGS = -Iinclude -lglfw
GLFW_DIR = -L"/usr/lib/x86_64-linux-gnu"
FRAMEWORKS = -ldl -pthread -lm $(GLFW_DIR) -lglfw
LIBFT =	libft/libft.a
SRC_DIR = src/
BONUS_DIR = bonus/

SRCS	=	fdf.c \
			parse_map.c \
			draw_map.c \
			utils1.c \
			free_and_exit.c \
			rotate_and_center.c \
			draw_utils.c \
			key_hooks.c \

BSRCS	=	fdf_bonus.c \
			parse_map_bonus.c \
			draw_map_bonus.c \
			utils1_bonus.c \
			free_and_exit_bonus.c \
			rotate_and_center_bonus.c \
			draw_utils_bonus.c \
			key_hooks_bonus.c \
			hook_utils_bonus.c

OBJS	= $(SRCS:%.c=$(OBJ_DIR)/%.o)
BOBJS	= $(BSRCS:%.c=$(BOBJ_DIR)/%.o)

OBJ_DIR			= obj
BOBJ_DIR		= bobj

all:	$(NAME)

bonus: $(BONUS)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(BOBJ_DIR):
	@mkdir -p $(BOBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)%.c
	@$(CC) -c $< -o $@
	@echo "\033[0;36mObject $@ [\033[0;32mOK\033[0;36m]\033[0m"

$(BOBJ_DIR)/%.o: $(BONUS_DIR)%.c
	@$(CC) -c $< -o $@
	@echo "\033[0;36mBonus Object $@ [\033[0;32mOK\033[0;36m]\033[0m"

$(MLX_TARGET):
	@mkdir -p $(MLX_BUILD_DIR)
	@cd $(MLX_BUILD_DIR) && cmake ..
	@cmake -B build
	@cmake --build $(MLX_BUILD_DIR) -j4

$(LIBFT):
			@make -C "libft"

$(NAME):	$(OBJ_DIR) $(OBJS) $(LIBFT) $(MLX_TARGET) libft/*.c
			@$(CC) $(OBJS) $(LIBFT) $(MLX_TARGET) $(MLXFLAGS) $(GLFW_DIR) $(FRAMEWORKS) -o $(NAME)
			@echo "\033[1;32mLibft library ready!\n\033[0m"
			@echo "\033[1;32mMLX42 library ready!\n\033[0m"
			@echo "\033[1;32mFdF compile success!\n\033[0m"

.bonus:		$(BOBJ_DIR) $(BOBJS) $(LIBFT) $(MLX_TARGET) libft/*.c
			@$(CC) $(BOBJS) $(LIBFT) $(MLX_TARGET) $(MLXFLAGS) $(GLFW_DIR) $(FRAMEWORKS) -o $(NAME)
			@touch .bonus
			@echo "\033[1;32mLibft library ready!\n\033[0m"
			@echo "\033[1;32mMLX42 library ready!\n\033[0m"
			@echo "\033[1;32mFdF Bonus objects compiled!\n\033[0m"

bonus:		$(BOBJ_DIR) .bonus

clean:
			@$(RM) $(OBJ_DIR) $(BOBJ_DIR) .bonus
			@make clean -C "libft"
			@echo "\033[0;36mClean FdF [\033[0;32mDONE\033[0;36m]\033[0m"

fclean:		clean
			@$(RM) $(NAME) $(OBJ_DIR) $(BOBJ_DIR)
			@echo "\033[0;36mFClean FdF [\033[0;32mDONE\033[0;36m]\033[0m"

re:			fclean all

rebonus:	fclean bonus

.PHONY:		all clean fclean re