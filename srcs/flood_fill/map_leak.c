/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_leak.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 10:56:41 by eassouli          #+#    #+#             */
/*   Updated: 2020/12/16 09:52:11 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"
#include "parse.h"
#include "raycast.h"

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

char	**map_cpy(t_map *map)
{
	char	**m_cp;
	int		line;

	map_dim(map);
	if (!(m_cp = malloc(sizeof(char **) * map->y + 1)))
		return (FALSE);
	line = 0;
	while (line < map->y)
	{
		m_cp[line] = ft_strdup(map->map[line]);
		line++;
	}
	m_cp[line] = NULL;
	return (m_cp);
}

t_vec	detect_start(t_map *map)
{
	t_vec		i;

	i = (t_vec){0, 0};
	while (i.y < map->y)
	{
		i.x = 0;
		while (i.x < map->x)
		{
			if (ft_strchr("NSWE", map->map[i.y][i.x]))
				return (i);
			i.x++;
		}
		i.y++;
	}
	return (i);
}

void	free_map(char **cpy)
{
	int	i;

	i = 0;
	while (cpy[i])
		free(cpy[i++]);
	free(cpy);
}

int		map_vfy_print(t_map *map)
{
	char	**m_cpy;
	int		is_closed;

	m_cpy = map_cpy(map);
	is_closed = flood_fill(m_cpy, detect_start(map), (t_vec){map->x, map->y});
	free_map(m_cpy);
	if (is_closed)
	{
		ft_putstr_fd("MAP IS CLOSED\n", 1);
		return (OK);
	}
	else
	{
		ft_putstr_fd("MAP ISN'T CLOSED PROPERLY\n", 1);
		return (ERR);
	}
}
