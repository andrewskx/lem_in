#include "lem_in.h"

t_node	*lem_in_newNode(char *name, int x, int y, int id)
{
	t_node *ptr;

	if ((ptr = (t_node*)malloc(sizeof(t_node))))
	{
		ptr->coord_x = x;
		ptr->coord_y = y;
		ptr->visited = 0;
		ptr->id = id;
		ptr->name = ft_strdup(name);
		ptr->links = 0;
		ptr->next = 0;
	}
	return (ptr);
}

void	lem_in_deleteNode(t_node *ptr)
{
	if (ptr)
	{
		if (ptr->name)
			free(ptr->name);
		if (ptr->links)
			ft_lstdel(&ptr->links, &ft_del_lst);
		free(ptr);
	}
}

void	lem_in_addToList(t_node **head, t_node *new)
{
	t_node **ptr;

	if (head)
	{
		ptr = head;
		new->next = *head;
		*ptr = new;
	}
}

void	lem_in_deleteList(t_node **head)
{
	t_node *ptr;

	while (*head)
	{
		ptr = (*head)->next;
		lem_in_deleteNode(*head);
		*head = ptr;
	}
}
	
