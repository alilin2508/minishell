NAME = libft.a
SRC = ft_bzero.c \
			ft_isalpha.c \
			ft_isdigit.c \
			ft_memccpy.c \
			ft_memcmp.c \
			ft_memmove.c \
			ft_strchr.c \
			ft_strlcpy.c \
			ft_strncmp.c \
			ft_strrchr.c \
			ft_toupper.c \
			ft_atoi.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isprint.c \
			ft_memchr.c \
			ft_memcpy.c \
			ft_memset.c \
			ft_strlcat.c \
			ft_strlen.c \
			ft_strnstr.c \
			ft_tolower.c \
			ft_strdup.c \
			ft_calloc.c \
			ft_strjoin.c \
			ft_substr.c \
			ft_putchar_fd.c \
			ft_putendl_fd.c \
			ft_putstr_fd.c \
			ft_putnbr_fd.c \
			ft_strmapi.c \
			ft_split.c \
			ft_itoa.c \
			ft_strtrim.c \
			ft_putendl.c \
			get_next_line.c \
			ft_lerpi.c \
			ft_memdel.c \
			ft_strnew.c \
			ft_lstnew.c \
			ft_lstadd.c \
			ft_strdel.c \
			ft_countwords.c \
			ft_lstrev.c \
			ft_splitdel.c \
			ft_lstcount.c \
			ft_strcat.c \
			ft_strcmp.c

OBJ		= $(SRC:.c=.o)
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

all: $(NAME)

%.o:%.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
