/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 16:15:09 by eassouli          #+#    #+#             */
/*   Updated: 2020/11/05 17:47:07 by eassouli         ###   ########.fr       */
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

int	add_line(char *line, t_list **first, t_list **lst)
{
	if ((*lst = ft_lstnew(line)) == NULL)
		return (ERR);
	ft_lstadd_back(first, *lst);
	return (OK);
}

int	start_p(int y, char *line, t_plr *plr, t_dir *dir)
{
	int		x;

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
		dir->y = (line[x] == 'N') ? -1 : dir->y;
		dir->plane_x = (line[x] == 'N') ? 1 : dir->plane_x;
		dir->y = (line[x] == 'S') ? 1 : dir->y;
		dir->plane_x = (line[x] == 'S') ? -1 : dir->plane_x;
		dir->x = (line[x] == 'W') ? -1 : dir->x;
		dir->plane_y = (line[x] == 'W') ? -1 : dir->plane_y;
		dir->x = (line[x] == 'E') ? 1 : dir->x;
		dir->plane_y = (line[x] == 'E') ? 1 : dir->plane_y;
		x++;
	}
	return (OK);
}

int	map_parse(int fd, char *line, t_a *a)
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
	if ((a->map.map = malloc(sizeof(char *) * (ft_lstsize(first) + 1))) == NULL)
		return (ERR);
	lst = first;
	while (lst != NULL)
	{
		a->map.map[y] = lst->content;
		if (start_p(y, a->map.map[y], &(a->plr), &(a->dir)) == ERR)
			return (ERR);
		lst = lst->next;
		y++;
	}
	a->map.map[y] = NULL;
	if (a->plr.pos_y == -1)
		return (ERR);  // ajouter error position introuvable
	// ft_lstclear(&first, (void *)ft_lstdelone);
	if (map_leak(&(a->map), &(a->plr)) == ERR)
		return (ERR);
	return (OK);
}
