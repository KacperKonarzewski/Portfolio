# Define the compiler
CC = gcc

# Compiler flags (you can modify this as needed)
CFLAGS = -Wall -Wextra -Werror

# Executable name
EXEC = rush-02

# Source files
SRC = conditions.c filereader.c ft_strstr.c main.c check_set.c write_line.c

# Object files (derived from the source files)
OBJ = $(SRC:.c=.o)

# Default rule (usually called 'all')
all: $(EXEC)

# Rule to compile the executable from object files
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

# Rule to compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule to remove object files
clean:
	rm -f $(OBJ)

# Full clean rule to remove both object files and the executable
fclean: clean
	rm -f $(EXEC)

# Rebuild everything by cleaning and recompiling
re: fclean all
