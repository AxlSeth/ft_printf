NAME = libprintf.a

CC = cc

CFLAGS = -Wall -Werror -Wextra

SOURCE = ft_printf.c\
	 ft_putstr.c\
	 ft_putnbr.c

OBJECTS = $(SOURCE:.c=.o)

all : $(NAME)

$(NAME) : $(OBJECTS)
	ar -rcs $(NAME) $(OBJECTS)

clean :
	rm -f $(OBJECTS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
