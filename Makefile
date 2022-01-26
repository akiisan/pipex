NAME = pipex
CC = gcc
CCFLAGS = -Wall -Wextra -Werror
SRC = main.c ft_split.c ft_calloc.c ft_strjoin.c utils.c ft_getenv.c ft_execve.c
OBJ=$(SRC:%.c=%.o)


all: $(NAME)

$(NAME): $(OBJ) 
	gcc -o $(NAME) $(OBJ)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f $(OBJ) 

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all