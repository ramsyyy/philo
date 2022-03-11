CC = gcc

NAME = philo

CFLAGS = -Wall -Wextra -Werror 

OBJ := $(.c=.o)

SRC = ./main.c

UTILS = ./utils/*

all : $(NAME)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

$(NAME): $(OBJ)
		${CC} -pthread ${SRC} $(UTILS) $(PRINTFNAME) -o ${NAME}

clean:
		rm -rf *.o

fclean: clean
		rm -f ${OBJS} $(NAME)

re: fclean all