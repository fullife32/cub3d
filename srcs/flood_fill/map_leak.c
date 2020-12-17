/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_leak.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 10:56:41 by eassouli          #+#    #+#             */
/*   Updated: 2020/12/17 16:23:54 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "raycast.h"
#include "stack.h"

void	map_dim(t_map *map)
{
	int	x;

	x = 0;
	while (map->map[map->y])
	{
		x = (int)ft_strlen(map->map[map->y]);
		map->x = x > map->x ? x : map->x;
		map->y++;
	}
}

void	map_cpy(t_a *a)
{
	int		line;

	map_dim(&a->map);
	if (!(a->map.m_cp = malloc(sizeof(char **) * a->map.y + 1)))
		error(MALLOC_FAIL_FILL, a);
	line = 0;
	while (line < a->map.y)
	{
		a->map.m_cp[line] = ft_strdup(a->map.map[line]);
		if (a->map.m_cp[line] == NULL)
			error(MALLOC_FAIL_FILL, a); //free map copy if error
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
	is_closed = flood_fill(a->map.m_cp, pos, (t_vec){a->map.x, a->map.y});
	map_free(a->map.m_cp);
	if (is_closed == FALSE)
		error(MAP_NOT_CLOSE, a);
}
