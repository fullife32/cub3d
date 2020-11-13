/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 16:15:09 by eassouli          #+#    #+#             */
/*   Updated: 2020/11/13 17:03:16 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"
#include "parse.h"
#include "raycast.h"

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

void	map_parse(t_a *a)
{
	t_list	*first;
	t_list	*lst;
	int		y;

	first = NULL;
	lst = NULL;
	if (add_line(a->mlx.line, &first, &lst) == ERR)
		error(-1, a);
	while (get_next_line(a->mlx.fd, &a->mlx.line) > 0)
	{
		if (add_line(a->mlx.line, &first, &lst) == ERR)
		error(-1, a);
	}
	if (add_line(a->mlx.line, &first, &lst) == ERR)
		error(-1, a);
	y = 0;
	if ((a->map.map = malloc(sizeof(char *) * (ft_lstsize(first) + 1))) == NULL)
		error(-1, a);
	lst = first;
	while (lst != NULL)
	{
		a->map.map[y] = lst->content;
		if (start_p(y, a->map.map[y], &(a->plr), &(a->dir)) == ERR)
			error(-1, a);
		lst = lst->next;
		y++;
	}
	a->map.map[y] = NULL;
	if (a->plr.pos_y == -1)
		error(-1, a);  // ajouter error position introuvable
	// ft_lstclear(&first, (void *)ft_lstdelone);
	if (map_leak(&(a->map), &(a->plr)) == ERR)
		error(-1, a);
}
