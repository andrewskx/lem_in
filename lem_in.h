#ifndef LEM_IN_H
# define LEM_IN_H

#include "libft/libft.h"
#include <stdio.h>
typedef	struct	s_node
{
	int	coord_x;
	int	coord_y;
	int	visited;
	int	id;
	char	*name;
	t_list	*links;
	struct	s_node	*next;
}		t_node;

typedef	struct	s_farm
{
	int64_t		ant_num;
	int		room_num;
	int		*path_by_id;
	char		*start_room;
	char		*end_room;
	t_node		*graph;
	t_list		*paths;

}		t_farm;
void	lem_in_error(char const *str);
void	lem_in_fileValidation(t_farm *farm);
void	lem_in_deleteList(t_node **head);
void	lem_in_addToList(t_node **head, t_node *new);
void	lem_in_deleteNode(t_node *ptr);
t_node	*lem_in_newNode(char *name, int x, int y, int id);
void	lem_in_fileValidation(t_farm *farm);
void	lem_in_addRoom(t_farm *farm, char *line, int *room_link_signal);
void	lem_in_ifStart(t_farm *farm, char *line, int *start, int *room_link_signal);
void	lem_in_ifEnd(t_farm *farm, char *line, int *end, int *room_link_signal);
void	lem_in_addLink(t_farm *farm, char *line, int *room_link_signal);
int	lem_in_ifLinkExists(t_node *node, char *linkName);
t_node	*lem_in_ifRoomExists(t_farm *farm, char *nodeName);
int	lem_in_isAComment(char *line_to_check);
void	lem_in_getAntNumber(t_farm *farm);
void	lem_in_checkCoordinates(t_farm *farm);
t_node *lem_in_getNodeByName(t_farm *farm, char *nodeName);
char	*lem_in_getNameById(t_farm *farm, int id);
void	lem_in_getNewPath(t_farm *farm, int index);
void	lem_in_DFS(t_node *node, int index, t_farm *farm);
#endif