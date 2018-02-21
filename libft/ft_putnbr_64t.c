/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboscan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 18:54:49 by anboscan          #+#    #+#             */
/*   Updated: 2017/11/27 18:26:15 by anboscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_check(int64_t n)
{
	if (n == -9223372036854775807 - 1)
	{
		ft_putstr("-9223372036854775808");
		return (1);
	}
	if (n == 9223372036854775806 + 1)
	{
		ft_putstr("9223372036854775807");
		return (1);
	}
	return (0);
}

void			ft_putnbr_64t(int64_t n)
{
	int64_t	var;
	int64_t	size;

	if (ft_check(n))
		return ;
	if (n < 0)
	{
		ft_putchar('-');
		n = -n;
	}
	var = n;
	size = 1;
	while ((n / 10) > 0)
	{
		n = n / 10;
		size = size * 10;
	}
	while (size != 0)
	{
		ft_putchar((char)((var / size) + 48));
		var = var % size;
		size = size / 10;
	}
}
