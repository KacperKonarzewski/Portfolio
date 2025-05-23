# Variables

EXEC        = fdf
SRC_DIR     = src/
OBJ_DIR     = obj/
LIBFT_DIR   = libft
LIBFT       = $(LIBFT_DIR)/libft.a
MINILIBX    = minilibx-linux
CC          = gcc
CFLAGS      = -Wall -Werror -Wextra -lm -I include -I $(MINILIBX)
LDFLAGS     = -L$(MINILIBX) -lmlx_Linux -L/usr/lib -lX11 -lXext -lbsd -lm
RM          = rm -f

# Colors

DEF_COLOR   = \033[0;39m
YELLOW      = \033[0;93m
GREEN       = \033[0;92m
BLUE        = \033[0;94m
CYAN        = \033[0;96m

# Sources

SRC_FILES   = bresenham.c color_palette.c generate_map.c mlx_extension.c map.c map2.c hooks.c fdf_math2.c fdf_utils.c fdf_math.c main.c
SRC         = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ         = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

###

OBJF        = .cache_exists

all: $(LIBFT) $(EXEC)

$(EXEC): $(OBJ)
		@echo "$(YELLOW)Linking executable: $(EXEC)$(DEF_COLOR)"
		@$(CC) $(OBJ) $(LIBFT) $(LDFLAGS) -o $(EXEC)
		@echo "$(GREEN)Executable $(EXEC) created!$(DEF_COLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJF)
		@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
		@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
		@echo "$(CYAN)Building libft library...$(DEF_COLOR)"
		@make -C $(LIBFT_DIR)

$(OBJF):
		@mkdir -p $(OBJ_DIR)

clean:
		@$(RM) -rf $(OBJ_DIR)
		@make clean -C $(LIBFT_DIR)
		@echo "$(BLUE)Object files cleaned!$(DEF_COLOR)"

fclean: clean
		@$(RM) -f $(EXEC)
		@make fclean -C $(LIBFT_DIR)
		@echo "$(CYAN)Executable file cleaned!$(DEF_COLOR)"

re: fclean all
		@echo "$(GREEN)Cleaned and rebuilt everything!$(DEF_COLOR)"

.PHONY: all clean fclean re
