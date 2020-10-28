/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_dist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 17:56:41 by eassouli          #+#    #+#             */
/*   Updated: 2020/10/28 16:37:50 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "raycast.h"

void	sprite_swap(t_spr *spr, int min, int i)
{
	double	dist_tmp;
	int		order_tmp;

	dist_tmp = spr->dist[min];
	spr->dist[min] = spr->dist[i];
	spr->dist[i] = dist_tmp;
	order_tmp = spr->order[min];
	spr->order[min] = spr->order[i];
	spr->order[i] = order_tmp;
}

void	sprite_sort(t_spr *spr)
{
	int	i;
	int	j;
	int	max;

	i = 0;
	while (i < spr->amount - 1)
	{
		j = i + 1;
		max = i;
		while (j < spr->amount)
		{
			if (spr->dist[j] > spr->dist[max])
				max = j;
			j++;
		}
		sprite_swap(spr, max, i);
		i++;
	}
}

void	sprite_dist(t_a *a)
{
	int		i;

	i = 0;
	while (i < a->spr.amount)
	{
		a->spr.dist[i] = (a->plr.pos_x - a->spr.pos_x[i])
		* (a->plr.pos_x - a->spr.pos_x[i]) + (a->plr.pos_y - a->spr.pos_y[i])
		* (a->plr.pos_y - a->spr.pos_y[i]);
		a->spr.order[i] = i;
		i++;
	}
}

void	sprite_free(t_spr *spr)
{
	if (spr->pos_x)
		free(spr->pos_x);
	spr->pos_x = 0;
	if (spr->pos_y)
		free(spr->pos_y);
	spr->pos_y = 0;
	if (spr->z_buff)
		free(spr->z_buff);
	spr->z_buff = 0;
	if (spr->dist)
		free(spr->dist);
	spr->dist = 0;
	if (spr->order)
		free(spr->order);
	spr->order = 0;
}
