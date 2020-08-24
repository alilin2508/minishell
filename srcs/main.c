#include "minishell.h"

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
		char *line;
		line = NULL;
		while (1)
		{
				write(1, "&> ", 3);
				get_next_line(0, &line);

		}
		return (0);
}
