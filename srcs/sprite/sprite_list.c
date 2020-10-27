/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 11:30:07 by eassouli          #+#    #+#             */
/*   Updated: 2020/10/27 11:46:38 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "raycast.h"

int		sprite_count(t_a *a)
{
	int	y;
	int	x;
	int	count;

	y = 0;
	count = 0;
	while (a->map.map[y])
	{
		x = 0;
		while (a->map.map[y][x])
		{
			if (a->map.map[y][x] == '2')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

void	sprite_pos(t_a *a)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	y = 0;
	while (a->map.map[y])
	{
		x = 0;
		while (a->map.map[y][x])
		{
			if (a->map.map[y][x] == '2')
			{
				a->spr.pos_x[i] = x;
				a->spr.pos_y[i] = y;
				i++;
			}
			x++;
		}
		y++;
	}
}

int		sprite_list(t_a *a)
{
	int	count;

	if ((count = sprite_count(a)) == 0)
		return (OK);
	if ((a->spr.pos_x = malloc(sizeof(int) * (count + 1))) == NULL)
		return (ERR);
	if ((a->spr.pos_y = malloc(sizeof(int) * (count + 1))) == NULL)
		return (ERR);
	sprite_pos(a);
	return (OK);
}
