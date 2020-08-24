#include "../includes/minishell.h"
#include "../libft/libft.h"

void 	ft_putstr(char *str)
{
		int i = 0;
		while (str[i])
		{
			write(1, &str[i], 1);
			i++;
		}
}

int 	main()
{
		while (1)
		{
				ft_putstr(">> ");
				get_next_line(0, 0);
		}
		return (0);
}
