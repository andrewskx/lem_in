/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboscan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 19:23:35 by anboscan          #+#    #+#             */
/*   Updated: 2018/03/02 19:27:17 by anboscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	lem_in_print(t_farm *farm, t_print *print)
{
	int ant;

	if (farm->ant_num < farm->path_len * farm->path_num)
		ant = farm->ant_num;
	else
		ant = farm->path_len * farm->path_num;
	lem_in_alloc(farm, print, ant);
	lem_in_pathArr(farm, print);
	lem_in_fillAnts(farm, print, ant, farm->path_num);
	lem_in_move(farm, ant, print, 0);
}

void	lem_in_fillAnts(t_farm *farm, t_print *print, int ant, int path_num)
{
	int i;

	i = 0;
	while (i < ant)
	{
		print->ant[i].pos = 0;
		print->ant[i].num = i + 1;
		print->ant[i].path_num = i % path_num;
		i++;
	}
}

void	lem_in_pathArr(t_farm *farm, t_print *print)
{
	int		i;
	int		j;
	t_list	*node;

	i = 0;
	node = farm->paths;
	while (i < farm->path_num)
	{
		j = 0;
		while (j < farm->path_len)
		{
			print->paths[i][j] = 0;
			j++;
		}
		print->paths[i][farm->path_len] = -1;
		print->paths_id[i] = (int*)node->content;
		node = node->next;
		i++;
	}
}

void	lem_in_alloc(t_farm *farm, t_print *print, int ant)
{
	int i;

	i = 0;
	print->ant = (t_ant *)malloc(sizeof(t_ant) * ant);
	print->paths = (int**)malloc(sizeof(int *) * farm->path_num);
	print->paths_id = (int**)malloc(sizeof(int *) * farm->path_num);
	while (i < farm->path_num)
	{
		print->paths[i] = (int*)malloc(sizeof(int) * (farm->path_len + 1));
		i++;
	}
}

void	lem_in_move(t_farm *farm, int ant, t_print *p, int j)
{
	while (1)
	{
		j = 0;
		while (j < ant)
		{
			if (p->paths[p->ant[j].path_num][p->ant[j].pos + 1] == -1)
			{
				if (p->ant[j].num == farm->ant_num &&
					p->paths[p->ant[j].path_num][p->ant[j].pos + 1] == -1)
					return ;
				p->paths[p->ant[j].path_num][p->ant[j].pos] = 0;
				p->ant[j].pos = 0;
				p->ant[j].num += ant;
			}
			else if (p->paths[p->ant[j].path_num][p->ant[j].pos + 1] == 0)
			{
				ft_putstr("L");
				ft_putnbr_64t(p->ant[j].num);
				ft_putstr("-");
				ft_putstr(lem_in_getNameById(farm,
						p->paths_id[p->ant[j].path_num][p->ant[j].pos + 1]));
				ft_putstr(" ");
				p->paths[p->ant[j].path_num][p->ant[j].pos] = 0;
				p->paths[p->ant[j].path_num][p->ant[j].pos + 1] = 1;
				p->ant[j].pos += 1;
			}
			j++;
		}
		ft_putstr("\n");
	}
}
