/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboscan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 19:28:04 by anboscan          #+#    #+#             */
/*   Updated: 2018/03/02 19:37:00 by anboscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft/libft.h"

typedef	struct		s_ant
{
	int				pos;
	int				num;
	int				path_num;
}					t_ant;

typedef struct		s_node
{
	int				coord_x;
	int				coord_y;
	int				visited;
	int				id;
	char			*name;
	t_list			*links;
	struct s_node	*next;
}					t_node;

typedef	struct		s_farm
{
	int64_t			ant_num;
	int				room_num;
	int				path_num;
	int				path_len;
	int				*path_by_id;
	char			*start_room;
	char			*end_room;
	t_node			*graph;
	t_list			*paths;

}					t_farm;

typedef	struct		s_print
{
	t_ant			*ant;
	int				**paths;
	int				**paths_id;
}					t_print;
void				lem_in_move(t_farm *farm, int ant, t_print *print, int j);
void				lem_in_alloc(t_farm *farm, t_print *print, int ant);
void				lem_in_pathArr(t_farm *farm, t_print *print);
void				lem_in_fillAnts(t_farm *farm, t_print *print,
									int ant, int path_num);
void				lem_in_print(t_farm *farm, t_print *print);
void				lem_in_printFirst(t_farm *farm);
void				lem_in_getShortest(t_farm *farm, int min);
void				lem_in_error(char const *str);
void				lem_in_fileValidation(t_farm *farm, int start, int end);
void				lem_in_deleteList(t_node **head);
void				lem_in_addToList(t_node **head, t_node *new);
void				lem_in_deleteNode(t_node *ptr);
t_node				*lem_in_newNode(char *name, int x, int y, int id);
void				lem_in_addRoom(t_farm *farm, char *line, int *room);
void				lem_in_ifStart(t_farm *farm, char *line, int *s, int *room);
void				lem_in_ifEnd(t_farm *farm, char *line, int *end, int *room);
void				lem_in_addLink(t_farm *farm, char *line, int *room);
int					lem_in_ifLinkExists(t_node *node, char *linkName);
t_node				*lem_in_ifRoomExists(t_farm *farm, char *nodeName);
int					lem_in_isAComment(char *line_to_check);
void				lem_in_getAntNumber(t_farm *farm);
void				lem_in_checkCoordinates(t_farm *farm);
t_node				*lem_in_getNodeByName(t_farm *farm, char *nodeName);
char				*lem_in_getNameById(t_farm *farm, int id);
void				lem_in_getNewPath(t_farm *farm, int index);
void				lem_in_DFS(t_node *node, int index, t_farm *farm);
#endif
