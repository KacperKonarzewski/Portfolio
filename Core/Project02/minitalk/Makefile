# Variables

EXEC        = client
EXEC2       = server
CLIENT_DIR  = client_src/
SERVER_DIR  = server_src/
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

CLIENT_FILES = client.c
SERVER_FILES = server.c
SRC_C        = $(addprefix $(CLIENT_DIR), $(CLIENT_FILES))
SRC_S        = $(addprefix $(SERVER_DIR), $(SERVER_FILES))
OBJ_C        = $(addprefix $(OBJ_DIR), $(CLIENT_FILES:.c=.o))
OBJ_S        = $(addprefix $(OBJ_DIR), $(SERVER_FILES:.c=.o))

# Object directory flag

OBJF        = .cache_exists

# Rules

all: $(LIBFT) $(EXEC) $(EXEC2)

$(EXEC): $(OBJ_C) $(LIBFT)
		@echo "$(YELLOW)Linking executable: $(EXEC)$(DEF_COLOR)"
		@$(CC) $(OBJ_C) $(LIBFT) -o $(EXEC)
		@echo "$(GREEN)Executable $(EXEC) created!$(DEF_COLOR)"

$(EXEC2): $(OBJ_S) $(LIBFT)
		@echo "$(YELLOW)Linking executable: $(EXEC2)$(DEF_COLOR)"
		@$(CC) $(OBJ_S) $(LIBFT) -o $(EXEC2)
		@echo "$(GREEN)Executable $(EXEC2) created!$(DEF_COLOR)"

$(OBJ_DIR)%.o: $(CLIENT_DIR)%.c | $(OBJF)
		@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
		@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)%.o: $(SERVER_DIR)%.c | $(OBJF)
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
		@$(RM) -f $(EXEC) $(EXEC2)
		@make fclean -C $(LIBFT_DIR)
		@echo "$(CYAN)Executables cleaned!$(DEF_COLOR)"

re: fclean all
		@echo "$(GREEN)Cleaned and rebuilt everything!$(DEF_COLOR)"

.PHONY: all clean fclean re
