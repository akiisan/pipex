NAME = pipex
CC = gcc
CCFLAGS = -Wall -Wextra -Werror
SRC = main.c
OBJ=$(SRC:%.c=%.o)


all: $(NAME)

$(NAME): $(OBJ) 
	gcc -o $(NAME) $(OBJ) Libft/libft.a

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f $(OBJ) 

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all libft