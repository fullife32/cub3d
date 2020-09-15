/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_leak.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 10:56:41 by eassouli          #+#    #+#             */
/*   Updated: 2020/09/15 11:37:22 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "raycast.h"

void	map_dim(t_map *map)
{
	int	x;

	while (map->map[map->y])
	{
		x = (int)ft_strlen(map->map[map->y]);
		map->x = x > map->x ? x : map->x;
		map->y++;
	}
}

char	**map_cpy(t_map *map)
{
	char	**cmap;
	int		line;

	line = 0;
	map_dim(map);
	cmap = malloc(sizeof(char **) * map->y + 1);
	if (cmap == NULL)
		return (NULL);
	
}

int	map_leak(t_map *map, t_plr *plr)
{
	char	**cmap;
	int		closed;

	cmap = map_cpy(map);
	if (cmap == NULL)
		return (ERR);
}