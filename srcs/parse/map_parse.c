/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 16:15:09 by eassouli          #+#    #+#             */
/*   Updated: 2021/01/07 15:11:31 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		add_line(char *line, t_list **first, t_list **lst) // free liste en cas d'erreur avant error
{
	if ((*lst = ft_lstnew(line)) == NULL)
		return (ERR);
	ft_lstadd_back(first, *lst);
	return (OK);
}

int		map_char(char *line)
{
	int		x;

	x = 0;
	while (line[x] != '\0')
	{
		if (ft_strchr("NSWE012 ", line[x]) == NULL)
			return (ERR);
		x++;
	}
	return (OK);
}

int		start_p(int y, char *line, t_plr *plr, t_dir *dir)
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

void	map_create(t_a *a)
{
	if (add_line(*a->mlx.line, &a->map.first, &a->map.lst) == ERR)
		error(MALLOC_FAIL_MAP, a);
	while (get_next_line(a->mlx.fd, a->mlx.line) > 0)
	{
		if (add_line(*a->mlx.line, &a->map.first, &a->map.lst) == ERR)
			error(MALLOC_FAIL_MAP, a);
	}
	if (add_line(*a->mlx.line, &a->map.first, &a->map.lst) == ERR)
		error(MALLOC_FAIL_MAP, a);
	if ((a->map.map = malloc(sizeof(char *)
	* (ft_lstsize(a->map.first) + 1))) == NULL) //verif free
		error(MALLOC_FAIL_MAP, a);
	a->map.map = ft_memset(a->map.map, 0, sizeof(char *)
	* (ft_lstsize(a->map.first) + 1));
	a->map.lst = a->map.first;
}

void	map_parse(t_a *a)
{
	int		y;

	y = 0;
	map_create(a);
	while (a->map.lst != NULL)
	{
		a->map.map[y] = a->map.lst->content;
		if (start_p(y, a->map.map[y], &(a->plr), &(a->dir)) == ERR)
			error(TOO_MANY_START, a);
		if (map_char(a->map.map[y]) == ERR)
			error(NOT_VALID_CHAR_MAP, a);
		a->map.lst = a->map.lst->next;
		y++;
	}
	a->map.map[y] = NULL;
	if (a->plr.pos_y == -1)
		error(NO_START, a);
	a->map.map[(int)a->plr.pos_y][(int)a->plr.pos_x] = '0';
	map_vfy_print(a);
}
