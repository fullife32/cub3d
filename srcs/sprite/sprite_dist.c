/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_dist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 17:56:41 by eassouli          #+#    #+#             */
/*   Updated: 2020/12/18 15:30:12 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
