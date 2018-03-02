/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboscan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 18:59:49 by anboscan          #+#    #+#             */
/*   Updated: 2018/03/02 19:14:35 by anboscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*=========  Validation =========
  - No empty lines
  - Only one number is excepted only on first line
  - A comment starts with #
  - end && start starts with ##
  - No double (##end || ##start)
  - 2 rooms can't have same coordinates
  - end room has to have path
  - every room should have at least 1 link
*/

void	lem_in_getAntNumber(t_farm *farm)
{
	char	*line;

	get_next_line(0, &line);
	if (!ft_isChar(line, &ft_isdigit))
		lem_in_error("Wrong Number of Ants\n");
	if ((farm->ant_num = ft_atoi_64t(line)) <= 0)
		lem_in_error("Wrong Number Of Ants\n");
}

int		lem_in_isAComment(char *line_to_check)
{
	if (ft_strlen(line_to_check) > 1)
		if (line_to_check[0] == '#' && line_to_check[1] != '#')
			return (1);
	return (0);
}

t_node	*lem_in_ifRoomExists(t_farm *farm, char *nodeName)
{
	t_node *ptr;

	if (farm->graph)
	{
		ptr = farm->graph;
		while (ptr)
		{
			if (!ft_strcmp(ptr->name, nodeName))
				return (ptr);
			ptr = ptr->next;
		}
	}
	return (0);
}

int		lem_in_ifLinkExists(t_node *node, char *linkName)
{
	t_list	*link;

	if (node->links)
	{
		link = node->links;
		while (link)
		{
			if (!ft_strcmp((const char *)link->content,
						(const char *)linkName) && link)
				return (1);
			link = link->next;
		}
	}
	return (0);
}

void	lem_in_addLink(t_farm *farm, char *line, int *room_link_signal)
{
	char	**tab;
	t_node	*node;

	if (*room_link_signal == 0)
		if ((tab = ft_strsplit(line, '-')))
		{
			if ((ft_count_words(tab)) == 2)
			{
				if ((node = lem_in_ifRoomExists(farm, tab[0])))
				{
					if (lem_in_ifLinkExists(node, tab[1]) ||
							!ft_strcmp(tab[1], (const char *)node->name))
						lem_in_error("Duplicated link Or Pipe to itself\n");
					ft_lstadd(&node->links, ft_lstnew((void const *)tab[1],
								ft_strlen((const char*)tab[1])));
				}
				else
				{
					ft_free_double_char(tab);
					lem_in_error("Room does not exist, can not link\n");
				}
			}
			else
				lem_in_error("Invalid line\n");
		}
}

void	lem_in_ifEnd(t_farm *farm, char *line, int *end, int *room_link_signal)
{
	if (line)
	{
		if (!ft_strcmp(line, "##end"))
		{
			if (*end == 0)
			{
				*end = 1;
				free(line);
				if (get_next_line(0, &line))
				{
					lem_in_addRoom(farm, line, room_link_signal);
					farm->end_room = ft_strdup(farm->graph->name);
				}
			}
			else
				lem_in_error("Duplicated ##end\n");
		}
	}
}

void	lem_in_ifStart(t_farm *farm, char *line, int *start, int *room_signal)
{
	if (line)
	{
		if (!ft_strcmp(line, "##start"))
		{
			if (*start == 0)
			{
				*start = 1;
				free(line);
				if (get_next_line(0, &line))
				{
					lem_in_addRoom(farm, line, room_signal);
					farm->start_room = ft_strdup(farm->graph->name);
				}
			}
			else
				lem_in_error("Duplicated ##start\n");
		}
	}
}

void	lem_in_addRoom(t_farm *farm, char *line, int *room_link_signal)
{
	char	**tab;
	t_node	*ptr;

	if ((tab = ft_strsplit(line, ' ')))
	{
		if ((ft_count_words(tab) == 3))
		{
			if (!(ptr = lem_in_ifRoomExists(farm, tab[0])))
			{
				if (ft_isChar(tab[1], &ft_isdigit) &&
						ft_isChar(tab[2], &ft_isdigit))
				{
					lem_in_addToList(&farm->graph, lem_in_newNode(tab[0],
							ft_atoi(tab[1]), ft_atoi(tab[2]), farm->room_num));
					*room_link_signal = 1;
					(farm->room_num)++;
				}
			}
			else
			{
				ft_free_double_char(tab);
				lem_in_error("Duplicated room\n");
			}
		}
	}
}

void	lem_in_checkCoordinates(t_farm *farm)
{
	t_node *ptr;
	t_node *aux;

	if (farm->graph)
	{
		ptr = farm->graph;
		while (ptr)
		{
			aux = farm->graph;
			if (!ptr->links &&
					ft_strcmp((const char*)ptr->name, farm->end_room))
				lem_in_error("Room has no links\n");
			while (aux)
			{
				if (aux != ptr)
					if (aux->coord_x == ptr->coord_x
							&& aux->coord_y == ptr->coord_y)
						lem_in_error("Same coordinates\n");
				aux = aux->next;
			}
			ptr = ptr->next;
		}
	}
}

void	lem_in_fileValidation(t_farm *farm, int start, int end)
{
	char	*line;
	int		room_link_signal;

	room_link_signal = 0;
	lem_in_getAntNumber(farm);
	while (get_next_line(0, &line))
	{
		if (!lem_in_isAComment(line))
		{
			lem_in_ifStart(farm, line, &start, &room_link_signal);
			lem_in_ifEnd(farm, line, &end, &room_link_signal);
			lem_in_addRoom(farm, line, &room_link_signal);
			lem_in_addLink(farm, line, &room_link_signal);
			room_link_signal = 0;
		}
	}
	if (end == 0)
		lem_in_error("##end not found\n");
	if (start == 0)
		lem_in_error("##start not found\n");
	lem_in_checkCoordinates(farm);
	farm->path_by_id = (int*)malloc(sizeof(int) * (farm->room_num + 2));
	ft_bzero(farm->path_by_id, (farm->room_num + 2) * sizeof(int));
}
