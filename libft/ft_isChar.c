#include "libft.h"

int	ft_isChar(char *str, int (*f)(int))
{
	int i;

	if (str)
	{
		i = 0;
		while (str[i])
		{
			if (!f(str[i]))
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}
