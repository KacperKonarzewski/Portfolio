CC = cc

FLAGS = -Wall -Wextra -Werror

SRC = ft_error.c ft_len.c handle_file.c main.c free_func.c read_info_input.c read_info.c read_map.c square_handler.c fill_map.c

EXEC = bsq

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
