/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 14:06:41 by eassouli          #+#    #+#             */
/*   Updated: 2020/12/18 15:30:08 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	wall_set(t_a *a)
{
	a->tex.dim = 64;
	a->north_txr.ptr = mlx_xpm_file_to_image(a->mlx.ptr, a->txr.north,
	&a->tex.dim, &a->tex.dim);
	a->south_txr.ptr = mlx_xpm_file_to_image(a->mlx.ptr, a->txr.south,
	&a->tex.dim, &a->tex.dim);
	a->east_txr.ptr = mlx_xpm_file_to_image(a->mlx.ptr, a->txr.east,
	&a->tex.dim, &a->tex.dim);
	a->west_txr.ptr = mlx_xpm_file_to_image(a->mlx.ptr, a->txr.west,
	&a->tex.dim, &a->tex.dim);
	if (a->north_txr.ptr == 0 || a->south_txr.ptr == 0 || a->east_txr.ptr == 0
	|| a->west_txr.ptr == 0)
		error(-1, a);
	a->north_txr.img = (int *)mlx_get_data_addr(a->north_txr.ptr,
	&a->north_txr.bpp, &a->north_txr.size_l, &a->north_txr.endian);
	a->south_txr.img = (int *)mlx_get_data_addr(a->south_txr.ptr,
	&a->south_txr.bpp, &a->south_txr.size_l, &a->south_txr.endian);
	a->east_txr.img = (int *)mlx_get_data_addr(a->east_txr.ptr,
	&a->east_txr.bpp, &a->west_txr.size_l, &a->east_txr.endian);
	a->west_txr.img = (int *)mlx_get_data_addr(a->west_txr.ptr,
	&a->west_txr.bpp, &a->east_txr.size_l, &a->west_txr.endian);
	if (a->north_txr.img == 0 || a->south_txr.img == 0 || a->east_txr.img == 0
	|| a->west_txr.img == 0)
		error(-1, a);
}

void	sprite_set(t_a *a)
{
	if ((a->spr.z_buff = malloc(sizeof(double) * (a->res.w + 1))) == NULL)
		error(-1, a);
	if ((a->spr.dist = malloc(sizeof(double) * (a->spr.amount + 1))) == NULL)
		error(-1, a);
	a->spr.dist[a->spr.amount] = '\0';
	if ((a->spr.order = malloc(sizeof(int) * a->spr.amount + 1)) == NULL)
		error(-1, a);
	a->spr.order[a->spr.amount] = '\0';
	if ((a->spr_txr.ptr = mlx_xpm_file_to_image(a->mlx.ptr, a->txr.sprite,
	&a->tex.dim, &a->tex.dim)) == NULL)
		error(-1, a);
	if ((a->spr_txr.img = (int *)mlx_get_data_addr(a->spr_txr.ptr,
	&a->spr_txr.bpp, &a->spr_txr.size_l, &a->spr_txr.endian)) == NULL)
		error(-1, a);
}
