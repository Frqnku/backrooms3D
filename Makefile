# Program
NAME = cub3D

# Colors
RED     = \033[31m
GREEN   = \033[32m
YELLOW  = \033[33m
BLUE    = \033[34m
MAGENTA = \033[35m
CYAN    = \033[36m
RESET   = \033[0m

# Files
UTILS = $(addprefix utils/, handle_errors.c cleanup.c)
PARSING = $(addprefix parsing/, check_args.c check_map.c check_textures.c initialize_textures_paths.c check_file_chars.c)
RENDER = 
GAMEPLAY = 
SRCS = $(addprefix src/, main.c $(UTILS) $(PARSING) $(RENDER) $(GAMEPLAY))
OBJS = $(SRCS:.c=.o)

# Archive
LIBFT = libft/libft.a
MLX = mlx/libmlx_Linux.a

# Flags
CFLAGS = -Wall -Wextra -Werror
MLXFLAGS = -lXext -lX11 -lm -lbsd

# Rules	
all: $(LIBFT) $(MLX) $(NAME)

$(NAME): $(OBJS)
	@gcc $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) $(MLXFLAGS) -o $(NAME)
	@echo "Be careful you will no clip into the backrooms"

$(LIBFT):
	@echo "\n\n--------------------------\n"
	@echo "$(YELLOW)Compiling libft...\n$(RESET)"
	@$(MAKE) -C libft
	@echo "$(GREEN)\nDone\n\n$(RESET)"

$(MLX):
	@echo "--------------------------\n"
	@echo "$(YELLOW)Compiling minilibx...\n$(RESET)"
	@$(MAKE) -C mlx
	@echo "$(GREEN)\nDone\n$(RESET)"
	@echo "--------------------------\n"

%.o: %.c
	@gcc $(CFLAGS) -I . -Imlx -c $< -o $@

clean:
	@$(MAKE) -C libft clean
	@$(MAKE) -C mlx clean
	@rm -f $(OBJS)

fclean: clean
	@$(MAKE) -C libft fclean
	@$(MAKE) clean -C mlx
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re