/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_leak.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 10:56:41 by eassouli          #+#    #+#             */
/*   Updated: 2020/09/25 15:02:26 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"
#include "parse.h"
#include "raycast.h"

void	free_map(char **cmap)
{
	int	i;

	i = 0;
	while (cmap[i])
		free(cmap[i++]);
	free(cmap);
}

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
	if ((cmap = malloc(sizeof(char **) * map->y + 1)) == NULL)
		return (NULL);
	while (line < map->y)
	{
		cmap[line] = ft_strdup(map->map[line]);
		line++;
	}
	cmap[line] = NULL;
	return (cmap);
	
}

int	map_leak(t_map *map, t_plr *plr)
{
	char	**cmap;
	int		closed;
	t_vec	vpos;

	if ((cmap = map_cpy(map)) == NULL)
		return (ERR);
	vpos = (t_vec){plr->pos_x - 0.5, plr->pos_y - 0.5};
	closed = flood_fill(cmap, vpos, map->x, map->y);

	if (closed == ERR)
	{
		ft_putstr_fd("--- MAP IS NOT PROPERLY CLOSED ---\n", 1);
		return (ERR);
	}
	for (int z = 0; z < map->y; z++)
		printf("%s\n", cmap[z]);
	ft_putstr_fd("--- MAP IS CLOSED ---\n", 1);
	free_map(cmap);
	return (OK);
}