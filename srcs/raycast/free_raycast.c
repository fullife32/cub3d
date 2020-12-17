/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 14:17:49 by eassouli          #+#    #+#             */
/*   Updated: 2020/12/17 16:51:35 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "raycast.h"

void	txr_free(t_a *a)
{
	if (a->txr.north)
		free(a->txr.north);
	if (a->txr.south)
		free(a->txr.south);
	if (a->txr.west)
		free(a->txr.west);
	if (a->txr.east)
		free(a->txr.east);
	if (a->txr.sprite)
		free(a->txr.sprite);
	if (a->txr.floor)
		free(a->txr.floor);
	if (a->txr.ceiling)
		free(a->txr.ceiling);
	if (a->north_txr.ptr)
		mlx_destroy_image(a->mlx.ptr, a->north_txr.ptr);
	if (a->south_txr.ptr)
		mlx_destroy_image(a->mlx.ptr, a->south_txr.ptr);
	if (a->east_txr.ptr)
		mlx_destroy_image(a->mlx.ptr, a->east_txr.ptr);
	if (a->west_txr.ptr)
		mlx_destroy_image(a->mlx.ptr, a->west_txr.ptr);
}

void	sprite_free(t_a *a)
{
	if (a->spr.pos_x)
		free(a->spr.pos_x);
	a->spr.pos_x = 0;
	if (a->spr.pos_y)
		free(a->spr.pos_y);
	a->spr.pos_y = 0;
	if (a->spr.z_buff)
		free(a->spr.z_buff);
	a->spr.z_buff = 0;
	if (a->spr.dist)
		free(a->spr.dist);
	a->spr.dist = 0;
	if (a->spr.order)
		free(a->spr.order);
	a->spr.order = 0;
	if (a->spr_txr.ptr)
		mlx_destroy_image(a->mlx.ptr, a->spr_txr.ptr);
}