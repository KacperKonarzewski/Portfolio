CC = cc

FLAGS = -Wall -Wextra -Werror

SRC = main.c

EXEC = ft_display_file

OBJ = $(SRC:.c=.o)

all: ${EXEC}

$(EXEC): $(OBJ)
	$(CC) $(FLAGS) -o $(EXEC) $(OBJ)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f ${OBJ}

fclean: clean
	rm -f ${EXEC}

re: fclean all
