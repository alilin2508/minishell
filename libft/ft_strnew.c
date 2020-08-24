#include "libft.h"

char	*ft_strnew(size_t size)
{
	return (malloc((size + 1) * sizeof(char)));
}
