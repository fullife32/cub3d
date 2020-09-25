/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 16:15:09 by eassouli          #+#    #+#             */
/*   Updated: 2020/09/15 11:20:16 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"
#include "parse.h"
#include "raycast.h"

// static int	error(int error)
// {
// 	write(1, "Error\n", 6);
// 	if (error == -2)
// 		write(1, "\n", 21);
// 	else if (error == -3)
// 		write(1, "\n", 21);
// 	return (ERR);
// }

int	add_line(char *line, t_list	**first, t_list	**lst)
{
	if ((*lst = ft_lstnew(line)) == NULL)
		return (ERR);
	ft_lstadd_back(first, *lst);
	return (OK);
}

int	start_p(int y, char *line, t_plr *plr, t_dir *dir)
{
	int x;

	x = 0;
	while (line[x] != '\0')
	{
		if (line[x] == 'N' || line[x] == 'S'
		|| line[x] == 'W' || line[x] == 'E')
		{
			if (plr->pos_y != -1)
				return (ERR);
			plr->pos_x = x + 0.5;
			plr->pos_y = y + 0.5;
		}
		if (line[x] == 'N')
		{
			dir->y = -1;
			dir->plane_x = 1;
		}
		else if (line[x] == 'S')
		{
			dir->y = 1;
			dir->plane_x = -1;
		}
		else if (line[x] == 'W')
		{
			dir->x = -1;
			dir->plane_y = -1;
		}
		else if (line[x] == 'E')
		{
			dir->x = 1;
			dir->plane_y = 1;
		}
		x++;
	}
	return (OK);
}

int	map_parse(int fd, char *line, t_map *map, t_plr *plr, t_dir *dir)
{
	t_list	*first;
	t_list	*lst;
	int		y;

	first = NULL;
	lst = NULL;
	if (add_line(line, &first, &lst) == ERR)
		return (ERR);
	while (get_next_line(fd, &line) > 0)
	{
		if (add_line(line, &first, &lst) == ERR)
		return (ERR);
	}
	if (add_line(line, &first, &lst) == ERR)
		return (ERR);
	y = 0;
	if ((map->map = malloc(sizeof(char *) * (ft_lstsize(first) + 1))) == NULL)
		return (ERR);
	lst = first;
	while (lst != NULL)
	{
		map->map[y] = lst->content;
		if (start_p(y, map->map[y], plr, dir) == ERR)
			return (ERR);
		lst = lst->next;
		y++;
	}
	map->map[y] = NULL;
	if (plr->pos_y == -1)
		return (ERR);  // ajouter error position introuvable
	// ft_lstclear(&first, (void *)ft_lstdelone);
	if (map_leak(map, plr) == ERR)
		return (ERR);
	return (OK);
}
