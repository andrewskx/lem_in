#include "libft.h"

void	ft_del_lst(void *content, size_t content_size)
{
	if (content)
		free(content);
	content_size = 0;
}
