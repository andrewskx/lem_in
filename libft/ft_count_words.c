#include "libft.h"

int	ft_count_words(char **str)
{
	int i;

	i = 0;
	if (str)
	{
		while (str[i])
			i++;
	}
	return (i);
}
