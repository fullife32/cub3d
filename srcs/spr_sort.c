/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spr_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 16:37:40 by eassouli          #+#    #+#             */
/*   Updated: 2020/10/16 16:45:55 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** This is a useless comment
*/

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
	int	min;

	i = 0;
	while (i < spr->amount - 1)
	{
		j = i + 1;
		while (j < spr->amount)
		{
			if (spr->dist[j] < spr->dist[min])
				min = j;
		}
		sprite_swap(spr, min, i);
		i++;
	}
}
