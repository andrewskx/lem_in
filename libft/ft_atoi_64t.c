/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboscan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 13:57:04 by anboscan          #+#    #+#             */
/*   Updated: 2017/11/29 17:09:37 by anboscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_get_index(const char *str, int *is_neg)
{
	int i;

	i = 0;
	*is_neg = 0;
	while ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n')
			|| (str[i] == '\v') || (str[i] == '\f') || (str[i] == '\r'))
		i++;
	if (str[i] == 45)
		*is_neg = 1;
	if ((str[i] == 45) || (str[i] == 43))
		i++;
	while (str[i] == 48)
		i++;
	return (i);
}

static int	ft_return(int *is_neg)
{
	if (*is_neg)
		return (-1);
	else
		return (1);
	return (0);
}

int64_t			ft_atoi_64t(const char *str)
{
	int				i;
	int				is_neg;
	int64_t				number;
	int				len;

	len = 0;
	number = 0;
	i = ft_get_index(str, &is_neg);
	while ((str[i] >= 48) && (str[i] <= 57))
	{
		if (len > 10)
		{
			if (is_neg)
				number = 0;
			else
				number = -1;
			break ;
		}
		number *= 10;
		number += ((int)str[i] - 48);
		i++;
		len++;
	}
	return (number * ft_return(&is_neg));
}
