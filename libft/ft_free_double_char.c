#include "libft.h"

void	ft_free_double_char(char **str)
{
	int i;

	if (str)
	{
		i = 0;
		while (str[i])
		{
			free(str[i]);
			i++;
		}
		free(str);
	}
}
