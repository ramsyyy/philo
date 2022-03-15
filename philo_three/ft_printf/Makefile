NAME = libftprintf.a

SRC = ft_putchar.c 			\
	ft_putstr.c 			\
	ft_putnbr.c 			\
	ft_putnbr_base.c 		\
	ft_putnbr_unsigned.c 	\
	ft_strdup.c 			\
	ft_printf.c 			\
	ft_strlen.c				\
	ft_putnbr_base_long.c	\

OBJ = $(SRC:.c=.o)
RM = rm -f
CFLAGS = -Wall -Werror -Wextra

.PHONY = all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $?

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

