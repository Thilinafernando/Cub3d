CC = cc
CFLAGS = -Wall -Wextra -Werror -g
MLX_FLAGS = mlx/libmlx.a -L/usr/lib/X11 -lXext -lX11

INCLUDES = -I/usr/include -Ilibft -Iget_next_line -Ilibprintf -Imlx

PRINTDIR = libprintf/
PRINT = $(PRINTDIR)libftprintf.a

LIBFTDIR = libft/
LIBFT = $(LIBFTDIR)libft.a

NAME = cub3d

MLXDIR = mlx/
MLX = $(MLXDIR)libmlx.a

mlx:
	@if [ ! -d "$(MLXDIR)" ]; then \
		echo "Cloning MLX..."; \
		git clone https://github.com/42Paris/minilibx-linux.git mlx; \
		rm -rf mlx/.git; \
		echo "Removed .git from mlx/"; \
	fi
	@$(MAKE) -C $(MLXDIR)
#	@clear

GNL = get_next_line/
GNL_SRC = get_next_line.c get_next_line_utils.c

EXECDIR = execution/
EXEC = execution/

UTILSDIR = Utils/
UTILS = Utils/

PARSDIR = parssing/
PRC = parssing/

BONUSDIR = bonus/
BONUS = bonus/

ALL_SRC = $(PRC) $(EXEC) $(UTILS) $(RED)

OBJ_DIR = obj

OBJECTS = $(addprefix $(OBJ_DIR)/, $(notdir $(ALL_SRC:.c=.o)))
OBJECT_BONUS = $(addprefix $(OBJ_DIR)/, $(notdir $(BONUS:.c=.o)))
GNL_OBJECTS = $(addprefix $(OBJ_DIR)/, $(notdir $(GNL_SRC:.c=.o)))

all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(LIBFT) mlx $(OBJECTS) $(GNL_OBJECTS) $(PRINT)
	@tput blink; echo -ne "Compiling Cub3d\r"; tput sgr0; sleep 1; echo "Cub3d ready to be played!"
	@$(CC) $(CFLAGS) $(OBJECTS) $(GNL_OBJECTS) -o $(NAME) $(MLX_FLAGS) $(LIBFT) $(PRINT)

#Bonus
$(NAME_BONUS): $(LIBFT) mlx $(OBJECT_BONUS)  $(GNL_OBJECTS) $(PRINT)
	$(CC) $(CFLAGS) $(OBJECT_BONUS)  $(GNL_OBJECTS) -o $(NAME_BONUS) $(PRINT) $(MLX_FLAGS) $(LIBFT)

#Bonus comp
$(OBJ_DIR)/%.o: $(BONUSDIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "Compiling $< ..."
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

# Libft compiling
$(LIBFT): $(LIBFTDIR)
	@$(MAKE) -C $(LIBFTDIR) bonus --quiet
	@$(MAKE) -C $(LIBFTDIR) --quiet

$(OBJ_DIR)/%.o: $(PARSDIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "Compiling $< ..."
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(OBJ_DIR)/%.o: $(EXECDIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "Compiling $< ..."
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(OBJ_DIR)/%.o: $(UTILSDIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "Compiling $< ..."
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

#PRINTF compiling
$(PRINT): $(PRINTDIR)
	@$(MAKE) -C $(PRINTDIR) --quiet

# GNL
$(OBJ_DIR)/%.o: $(GNL)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

clean:
	@$(MAKE) clean -C $(LIBFTDIR)
	@$(MAKE) clean -C $(PRINTDIR)
	@rm -rf $(OBJ_DIR)
	@clear

fclean:
	@$(MAKE) fclean -C $(LIBFTDIR)
	@$(MAKE) fclean -C $(PRINTDIR)
	@rm -rf $(OBJ_DIR)
	@rm -f $(MLXDIR)*.o $(MLXDIR)*.a
	@rm -rf $(NAME) $(NAME_BONUS)
	@clear

re: fclean all

clean_mlx:
	@tput blink; echo -ne "Cleaning MLX\r"; tput sgr0; sleep 1; echo "Cleaning MLX"
	@rm -rf $(MLXDIR)

vall: all clean
		valgrind --track-origins=yes -q --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes

.PHONY: all bonus clean fclean re clean_mlx mlx

