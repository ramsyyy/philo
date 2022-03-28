CC = gcc

NAME = philo

PRINTFPATH = ./ft_printf/

PRINTFNAME = libftprintf.a

CFLAGS = -Wall -Wextra -Werror

OBJ := $(.c=.o)

SRC = ./main.c

UTILS = ./utils/*

all : $(NAME)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

$(NAME): $(OBJ)
		${CC} -g3 -pthread ${SRC} $(UTILS) -o ${NAME}

clean:
		rm -rf *.o

fclean: clean
		rm -f ${OBJS} $(NAME)

re: fclean all