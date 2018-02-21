#include "lem_in.h"

t_node *lem_in_getNodeByName(t_farm *farm, char *nodeName)
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
//	int *arr;

	farm->path_by_id[index] = -1;
//	for (int i = 0; i < index; i++)
//		printf("%s -> ", lem_in_getNameById(farm, farm->path_by_id[i]));
//	printf("\n");
//	t_list *new_lst = ft_lstnew(farm->path_by_id, (size_t)((farm->room_num + 1) * sizeof(int)));
	farm->path_by_id[farm->room_num + 1] = index;
	ft_lstadd(&farm->paths,
		ft_lstnew(farm->path_by_id, (size_t)((farm->room_num + 2) * sizeof(int))));
	//arr = (int *)farm->paths->content;
	//`new_lst->content = ft_memcpy(farm->path_by_id, sizeof(int) * 
//	arr = (int*)new_lst->content;
	//arr = farm->path_by_id;
//	for (int i = 0; arr[i] != -1; i++)
//		printf("%i -> ", arr[i]);
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
		lem_in_DFS(lem_in_getNodeByName(farm, (char*)aux->content), index + 1, farm);
		aux = aux->next;
	}
	farm->path_by_id[index] = 0;
	node->visited = 0;
}
