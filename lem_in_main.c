#include "lem_in.h"
#include <stdio.h>


void	lem_in_printFarm(t_farm *farm)
{
	t_node *node;
	t_list	*list;

	if (farm->graph)
	{
		node = farm->graph;
		while (node)
		{
			printf("name->|%s|, coord_x->%i, coord_y->%i, id -> %i\n", node->name, node->coord_x, node->coord_y, node->id);
			if (node->links)
			{
				list = node->links;
				while (list)
				{
					printf("%s->%s\n", node->name, (char*)list->content);
					list = list->next;
				}
			}
			node = node->next;
		}
	}
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
			printf("%s", lem_in_getNameById(farm, arr[i]));
			i++;
			if (arr[i] != -1)
				printf("-");
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
	farm->paths = 0;
	farm->path_by_id = 0;
}

int	main(void)
{
	t_farm farm;

	lem_in_init(&farm);
	lem_in_fileValidation(&farm);
	printf("ants -> %lld\nrooms -> %i\n", farm.ant_num, farm.room_num);
	printf("start_room->%s\nend_room->%s\n", farm.start_room, farm.end_room);
	lem_in_printFarm(&farm);
	lem_in_DFS(lem_in_getNodeByName(&farm, farm.start_room), 0, &farm);
	lem_in_printPaths(&farm);
	if (!farm.paths)
		printf("No paths\n");
	return (0);
}
