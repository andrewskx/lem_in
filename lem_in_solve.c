/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_solve.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboscan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 18:52:28 by anboscan          #+#    #+#             */
/*   Updated: 2018/03/02 19:22:47 by anboscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_node	*lem_in_getNodeByName(t_farm *farm, char *nodeName)
{
	t_node *ptr;

	ptr = farm->graph;
	while (ptr)
	{
		if (!ft_strcmp(ptr->name, nodeName))
			break ;
		ptr = ptr->next;
	}
	return (ptr);
}

void	lem_in_getNewPath(t_farm *farm, int index)
{
	farm->path_by_id[index] = -1;
	farm->path_by_id[farm->room_num + 1] = index;
	ft_lstadd(&farm->paths,
	ft_lstnew(farm->path_by_id, (size_t)((farm->room_num + 2) * sizeof(int))));
}

void	lem_in_DFS(t_node *node, int index, t_farm *farm)
{
	t_list *aux;

	if (!ft_strcmp(node->name, farm->end_room))
	{
		farm->path_by_id[index] = node->id;
		lem_in_getNewPath(farm, index + 1);
		return ;
	}
	if (node->visited)
		return ;
	node->visited = 1;
	farm->path_by_id[index] = node->id;
	aux = node->links;
	while (aux)
	{
		lem_in_DFS(lem_in_getNodeByName(farm,
				(char*)aux->content), index + 1, farm);
		aux = aux->next;
	}
	farm->path_by_id[index] = 0;
	node->visited = 0;
}
