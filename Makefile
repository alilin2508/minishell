NAME = minishell
OS = $(shell uname)

SRCDIR = ./srcs
INCDIR = ./includes
OBJDIR = ./obj

SRC = main.c \
				signal.c \
				command.c \
				splitcmd.c \
				get_path.c \
				pipe.c \
				checkerror.c \
				env.c \
				utilsexport.c \
				ft_checkerror.c \
				ft_chevron.c

OBJ		= $(addprefix $(OBJDIR)/,$(SRC:.c=.o))

CC		= gcc
CFLAGS = -Wall -Wextra -Werror -g

FTDIR = ./libft
FT_LIB = $(addprefix $(FTDIR)/,libft.a)
FT_INC = -I $(FTDIR)
FT_LNK = -L $(FTDIR) -l ft

all: obj $(FT_LIB) $(NAME)

obj:
		@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o:$(SRCDIR)/%.c
		@$(CC) $(CFLAGS) $(FT_INC) -I $(INCDIR) -o $@ -c $<

$(FT_LIB):
		@make -C $(FTDIR)

$(NAME): $(OBJ)
		@$(CC) $(OBJ) $(FT_LNK) -lm -o $(NAME)

clean:
		rm -rf $(OBJDIR)
		make -C $(FTDIR) clean

fclean: clean
		rm -f $(NAME)
		make -C $(FTDIR) fclean

re: fclean all
