NAME = libftprintf.a

SRCS = ft_printf.c \
		ft_check.c \
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

OBJ = $(SRCS:.c=.o)
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

all:		$(NAME)

%.o:%.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
			rm -rf $(OBJ)

fclean:		clean
			rm -rf $(NAME)

re:			fclean all
