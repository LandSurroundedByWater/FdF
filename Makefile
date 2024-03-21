NAME = fdf

CC = cc
RM = rm -rf

MLX_DIR = MLX42
MLX_BUILD_DIR = $(MLX_DIR)/build
MLX_TARGET = $(MLX_BUILD_DIR)/libmlx42.a
CFLAGS = -Wall -Wextra -Werror
MLXFLAGS = -Iinclude -lglfw
HBFLAGS = -L"/Users/tsaari/.brew/opt/glfw/lib/"
FRAMEWORKS = -framework Cocoa -framework OpenGL -framework IOKit
LIBFT =	libft/libft.a

SRCS		= fdf.c \
			parse_map.c \
			draw_map.c \
			utils1.c \
			free_and_exit.c \
			rotate_and_center.c \
			draw_utils.c \
			key_hooks.c \
			hook_utils.c

OBJ_DIR		= obj
OBJS		= $(SRCS:%.c=$(OBJ_DIR)/%.o)

all:		$(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS)  -o $@ -c $<
	@echo "\033[0;36mObject $@ [\033[0;32mOK\033[0;36m]\033[0m"

$(MLX_TARGET):
	@mkdir -p $(MLX_BUILD_DIR)
	@cd $(MLX_BUILD_DIR) && cmake ..
	@cmake --build $(MLX_BUILD_DIR) -j4


$(LIBFT):
			@make -C "libft"

$(OBJ_DIR):
			@mkdir -p $(OBJ_DIR)

$(NAME):	$(OBJ_DIR) $(OBJS) $(LIBFT) $(MLX_TARGET) libft/*.c
			@$(CC) $(OBJS) $(LIBFT) $(MLX_TARGET) $(MLXFLAGS) $(HBFLAGS) $(FRAMEWORKS) $(LDLFLAGS) -o $(NAME)
			@echo "\033[1;32mMLX42 library ready!\n\033[0m"
			@echo "\033[1;32mFdF compile success!\n\033[0m"

clean:
			@$(RM) $(OBJ_DIR)
			@make clean -C "libft"
			@echo "\033[0;36mClean FdF [\033[0;32mDONE\033[0;36m]\033[0m"

fclean:		clean
			@$(RM) $(NAME) $(OBJ_DIR)
			@make fclean -C "libft"
			@echo "\033[0;36mFClean FdF [\033[0;32mDONE\033[0;36m]\033[0m"

re:			fclean all

.PHONY:		all clean fclean re