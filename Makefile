NAME = minishell
OS = $(shell uname)

SRCDIR = ./srcs
INCDIR = ./includes
OBJDIR = ./obj

SRC = main.c \

OBJ		= $(addprefix $(OBJDIR)/,$(SRC:.c=.o))

CC		= gcc
CFLAGS = -g -Wall -Wextra -Werror

FTDIR = ./libft
FT_LIB = $(addprefix $(FTDIR)/,libft.a)
FT_INC = -I $(FTDIR)
FT_LNK = -L $(FTDIR) -l ft

PRDIR = ./printf
PR_LIB = $(addprefix $(FTDIR)/,libftprintf.a)
PR_INC = -I $(PRDIR)
PR_LNK = -L $(PRDIR) -l ft

all: obj $(FT_LIB) $(PR_LIB) $(NAME)

obj:
		mkdir -p $(OBJDIR)

$(OBJDIR)/%.o:$(SRCDIR)/%.c
		@$(CC) $(CFLAGS) $(FT_INC) $(PR_INC) -I $(INCDIR) -o $@ -c $<

$(FT_LIB):
		@make -C $(FTDIR)

$(PR_LIB):
		@make -C $(PRDIR)

$(NAME): $(OBJ)
		@$(CC) $(OBJ) $(FT_LNK) $(PR_LNK) -lm -o $(NAME)

clean:
		rm -rf $(OBJDIR)
		make -C $(FTDIR) clean
		make -C $(PRDIR) clean

fclean: clean
		rm -f $(NAME)
		make -C $(FTDIR) fclean
		make -C $(PRDIR) fclean

re: fclean all
