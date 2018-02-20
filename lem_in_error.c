#include "lem_in.h"

void	lem_in_error(char const *str)
{
	ft_putstr_fd(str, 2);
	exit(0);
}
