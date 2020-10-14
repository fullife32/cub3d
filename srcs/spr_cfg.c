/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spr_cfg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 17:56:41 by eassouli          #+#    #+#             */
/*   Updated: 2020/10/14 19:24:22 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int		sprite_init(t_a *a)
{
	a->spr_txr.ptr = mlx_xpm_file_to_image(a->mlx.ptr, a->txr.sprite,
	&a->tex.dim, &a->tex.dim);
	if (a->spr_txr.ptr == 0)
		return (ERR);
	a->spr_txr.img = (int *)mlx_get_data_addr(a->spr_txr.ptr,
	&a->spr_txr.bpp, &a->spr_txr.size_l, &a->spr_txr.endian);
	if (a->spr_txr.img == 0)
		return (ERR);
	if ((a->spr.z_buff = malloc(sizeof(double) * (a->res.w + 1))) == 0)
		return (ERR);
	a->spr.amount = 0; //maybe change place
	return (OK);
}

int		sprite_add(t_spr *spr, double new_dist)
{
	int		i;
	double	*dist_tmp;

	spr->amount++;
	if (spr->dist)
	{
		if ((dist_tmp = malloc(sizeof(double) * (spr->amount + 1))) == 0)
			return (ERR);
		while (i < spr->amount - 1)
		{
			dist_tmp[i] = spr->dist[i];
			i++;
		}
		free(spr->dist);
	}
	else
	{
		if ((dist_tmp = malloc(sizeof(double) * (spr->amount + 1))) == 0)
			return (ERR);
	}
	dist_tmp[i++] = new_dist;
	dist_tmp[i] = '\0';
	spr->dist = dist_tmp;
	return (OK);
}

void	sprite_sort(t_spr *spr) // create order
{
	int		i;
	int		order_tmp;
	double	dist_tmp;

	i = 0;
	while (i < spr->amount)
	{
		if (spr->dist[i] > spr->dist[i + 1])
		{
			dist_tmp = spr->dist[i];
			spr->dist[i] = spr->dist[i + 1];
			spr->dist[i + 1] = dist_tmp;
			order_tmp = spr->order[i];
			spr->order[i] = spr->order[i + 1];
			spr->order[i + 1] = order_tmp;
			i = 0;
		}
		i++;
	}
}

void	sprite_free(t_spr *spr)
{
	if (spr->z_buff)
		free(spr->z_buff);
	if (spr->dist)
		free(spr->dist);
	if (spr->order)
		free(spr->order);
}