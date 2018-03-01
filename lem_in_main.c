#include "lem_in.h"
#include <stdio.h>



void	lem_in_findShortest(t_farm *farm)
{
	t_list *ptr;
	int	*arr;
	int	min;

	min = 999999;
	if (farm->paths)
	{
		ptr = farm->paths;
		while (ptr)
		{
			arr = (int *)ptr->content;
			arr[farm->room_num + 1] < min ? min = arr[farm->room_num + 1] : 0;
			ptr = ptr->next;
		}
		if (min <= farm->room_num)
		{
			farm->path_len = min;
			lem_in_getShortest(farm, min);
		}
	}
}


void	lem_in_getShortest(t_farm *farm, int min)
{
	t_list *ptr;
	t_list *new;
	int	*arr;

	new = 0;
	if (farm->paths)
	{
		ptr = farm->paths;
		while (ptr)
		{
			arr = (int *)ptr->content;
			if (arr[farm->room_num + 1] == min)
			{
				ft_lstadd(&new,
				ft_lstnew(arr, (size_t)(farm->room_num + 2) * sizeof(int)));
				farm->path_num += 1;
			}
			ptr = ptr->next;
		}
	ft_lstdel(&farm->paths, &ft_del_lst);
	farm->paths = new;
	}
}


void	lem_in_printFirst(t_farm *farm)
{
	t_node *node;

	ft_putnbr_64t(farm->ant_num);
	ft_putchar('\n');
	if (farm->graph)
	{
		node = farm->graph;
		while (node)
		{
			if (!ft_strcmp(node->name, farm->start_room))
				ft_putstr("##start\n");
			if (!ft_strcmp(node->name, farm->end_room))
				ft_putstr("##end\n");
			ft_putstr(node->name);
			ft_putchar(' ');
			ft_putnbr(node->coord_x);
			ft_putchar(' ');
			ft_putnbr(node->coord_y);
			ft_putchar('\n');
			node = node->next;
		}
	}
}

			
void	lem_in_printFarm(t_farm *farm)
{
	t_node *node;
	t_list	*list;

	lem_in_printFirst(farm);
	if (farm->graph)
	{
		node = farm->graph;
		while (node)
		{
			if (node->links)
			{
				list = node->links;
				while (list)
				{
					ft_putstr((char*)node->name);
					ft_putstr("-");
					ft_putendl((char*)list->content);
					list = list->next;
				}
			}
			node = node->next;
		}
	}
	ft_putchar('\n');
}

char	*lem_in_getNameById(t_farm *farm, int id)
{
	t_node *ptr;

	ptr = farm->graph;
	while (ptr)
	{
		if (ptr->id == id)
			break ;
		ptr = ptr->next;
	}
	return (ptr->name);
}

void	lem_in_printPaths(t_farm *farm)
{
	t_list *ptr;
	int 	i;
	int	*arr;

	ptr = farm->paths;
	while (ptr)
	{
		i = 0;
		arr = (int *)ptr->content;
		while (arr[i] != -1)
		{
			ft_putstr((lem_in_getNameById(farm, arr[i])));
			i++;
			arr[i] != -1 ? ft_putchar('-') : 0;
		}
		printf("\n");
		ptr = ptr->next;
	}
}



void	lem_in_init(t_farm *farm)
{
	farm->ant_num = 0;
	farm->room_num = 0;
	farm->start_room = 0;
	farm->end_room = 0;
	farm->graph = 0;
	farm->path_num = 0;
	farm->paths = 0;
	farm->path_by_id = 0;
}

int	main(void)
{
	t_farm farm;
	t_print	print;

	lem_in_init(&farm);
	lem_in_fileValidation(&farm);
//	lem_in_printFarm(&farm);
	lem_in_DFS(lem_in_getNodeByName(&farm, farm.start_room), 0, &farm);
	lem_in_findShortest(&farm);
	if (!farm.path_num)
	{
		ft_putstr("No paths\n");
		return (0);
	}
	lem_in_printFarm(&farm);
//	lem_in_printPaths(&farm);
        lem_in_print(&farm, &print);
	return (0);
}
