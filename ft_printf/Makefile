NAME = libftprintf.a

SRCS = ft_printf.c \
		ft_check.c \
		ft_itoa.c \
		ft_putnbr.c \
		ft_strlen.c \
		ft_atoi.c \
		ft_isdigit.c \
		ft_itoabase.c \
		ft_printf_utils.c \
		ft_putstr.c \
		ft_substr.c \
		ft_calloc.c \
		ft_islowalpha.c \
		ft_print.c \
		ft_putchar.c \
		ft_strdup.c \
		ft_printf_utils2.c \

OBJS = *.o

all:		$(NAME)

$(NAME):
			gcc -Wall -Werror -Wextra -c $(SRCS)
			ar rc $(NAME) $(OBJS)

clean:
			rm -rf $(OBJS)

fclean:		clean
			rm -rf $(NAME)

re:			fclean all
