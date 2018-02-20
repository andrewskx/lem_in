#include "libft.h"

int	ft_istabulator(int c)
{
	return (c == '\t' || c == ' ' || c == '\n' || c == '\r'
		|| c == '\v' || c == '\f');
}
