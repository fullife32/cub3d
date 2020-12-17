/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 14:17:32 by eassouli          #+#    #+#             */
/*   Updated: 2020/12/17 16:23:47 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	line_free(t_a *a)
{
	if (*a->mlx.line)
		free(*a->mlx.line);
	*a->mlx.line = NULL;
}

void	parse_free(t_a *a)
{
	if (*a->mlx.line)
		free(*a->mlx.line);
	*a->mlx.line = NULL;
	if (a->mlx.line)
		free(a->mlx.line);
	a->mlx.line = NULL;
}

void	map_free(char **map)
{
	int	i;

	i = 0;
	if (map)
	{
		while (map[i])
			free(map[i++]);
		free(map);
	}
}
