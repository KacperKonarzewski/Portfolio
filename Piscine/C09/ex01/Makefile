CC = cc

FLAGS = -Wall -Wextra -Werror

SRC = ./srcs/ft_putchar.c ./srcs/ft_swap.c ./srcs/ft_putstr.c ./srcs/ft_strlen.c ./srcs/ft_strcmp.c

HEAD = ./includes/

EXEC = libft.a

OBJ = $(SRC:.c=.o)

AR = ar rc

LIB = ranlib

all: ${EXEC}

$(EXEC): $(OBJ)
	$(AR) $(EXEC) $(OBJ)
	$(LIB) $(EXEC)

.c.o:
	$(CC) $(FLAGS) -c -I $(HEAD) $< -o $@

clean:
	rm -f ${OBJ}

fclean: clean
	rm -f ${EXEC}

re: fclean all
