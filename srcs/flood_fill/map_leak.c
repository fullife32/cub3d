/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_leak.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 10:56:41 by eassouli          #+#    #+#             */
/*   Updated: 2021/01/13 16:24:00 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_dim(t_map *map)
{
	int	x;

	x = 0;
	while (map->map[map->y])
	{
		x = (int)ft_strlen(map->map[map->y]);
		if (x > map->x)
			map->x = x;
		map->y++;
	}
}

void	map_cpy(t_a *a)
{
	int		line;

	map_dim(&a->map);
	a->map.m_cp = malloc(sizeof(char *) * (a->map.y + 1));
	if (a->map.m_cp == NULL)
		error(MALLOC_FAIL_FILL, a);
	a->map.m_cp = ft_memset(a->map.m_cp, 0, sizeof(char *) * (a->map.y + 1));
	line = 0;
	while (line < a->map.y)
	{
		a->map.m_cp[line] = ft_strdup(a->map.map[line]);
		if (a->map.m_cp[line] == NULL)
			error(MALLOC_FAIL_FILL, a);
		line++;
	}
	a->map.m_cp[line] = NULL;
}

void	map_vfy_print(t_a *a)
{
	t_vec	pos;
	int		is_closed;

	pos = (t_vec){a->plr.pos_x, a->plr.pos_y};
	map_cpy(a);
	is_closed = flood_fill(a->map.m_cp, pos, (t_vec){a->map.x, a->map.y}, &a->stk);
	if (a->map.m_cp)
	{
		map_free(a->map.m_cp);
		free(a->map.m_cp);
	}
	a->map.m_cp = NULL;
	if (is_closed == FALSE)
		error(MAP_NOT_CLOSE, a);
}
