CC = gcc -Wall -Wextra -Werror -g3 -fsanitize=thread 

NAME = philo

UTILS = ./utils/ft_atoi.c \
		./utils/ft_putnbr.c \
		./utils/ft_strlen.c \
		./utils/operation.c \
		./utils/parser.c \
		./utils/philo_init.c \
		./utils/time.c \
		./utils/main.c \
		./utils/ft_strcmp.c \

OBJ := $(UTILS:%.c=%.o) \
		philo.h		  \

all : $(NAME)

$(NAME): $(OBJ)
	@${CC} -pthread $(UTILS:%.c=%.o) -o ${NAME}

%.o: %.c
	@echo "compiling" $@
	@$(CC) -c $< -o $@

clean:
		@echo "deletion object" 
		@rm -rf $(UTILS:.c=.o)

fclean: clean
		@rm -rf $(NAME)

re: fclean all

.PHONY:		all clean fclean re