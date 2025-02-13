# Variables

EXEC        = minishell
SRC_DIR     = src/
OBJ_DIR     = obj/
LIBFT_DIR   = libft
LIBFT       = $(LIBFT_DIR)/libft.a
CC          = cc
CFLAGS      = -Wall -Werror -Wextra -I include
RM          = rm -f

# Colors

DEF_COLOR   = \033[0;39m
YELLOW      = \033[0;93m
GREEN       = \033[0;92m
BLUE        = \033[0;94m
CYAN        = \033[0;96m

# Sources

SRC_FILES   = wildcards/realloc_split.c wildcards/wildcards.c wildcards/wildcards2.c \
logic_operators/parser_logic.c logic_operators/parser_logic2.c logic_operators/parser_logic3.c logic_operators/tokens.c logic_operators/tokens2.c \
builtins/builtins.c builtins/handle_env.c builtins/handle_env2.c \
execute/executor.c execute/parser.c execute/parser2.c \
utils/utils2.c utils/utils.c utils/signals.c \
main.c
SRC         = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ         = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

###

OBJF        = .cache_exists

all: $(LIBFT) $(EXEC)

$(EXEC): $(OBJ)
		@echo "$(YELLOW)Linking executable: $(EXEC)$(DEF_COLOR)"
		@$(CC) $(OBJ) $(LIBFT) -o $(EXEC) -lreadline
		@echo "$(GREEN)Executable $(EXEC) created!$(DEF_COLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJF)
		@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
		@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
		@echo "$(CYAN)Building libft library...$(DEF_COLOR)"
		@make -C $(LIBFT_DIR)

$(OBJF):
		@mkdir -p $(OBJ_DIR)
		@mkdir -p $(OBJ_DIR)/wildcards
		@mkdir -p $(OBJ_DIR)/logic_operators
		@mkdir -p $(OBJ_DIR)/builtins
		@mkdir -p $(OBJ_DIR)/execute
		@mkdir -p $(OBJ_DIR)/utils

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
