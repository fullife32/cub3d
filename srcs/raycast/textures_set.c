/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 14:06:41 by eassouli          #+#    #+#             */
/*   Updated: 2021/01/12 22:24:01 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	wall_set2(t_a *a)
{
	a->north_txr.img = (int *)mlx_get_data_addr(a->north_txr.ptr,
			&a->north_txr.bpp, &a->north_txr.size_l, &a->north_txr.endian);
	if (a->north_txr.img == NULL)
		error(MALLOC_FAIL_NO, a);
	a->south_txr.img = (int *)mlx_get_data_addr(a->south_txr.ptr,
			&a->south_txr.bpp, &a->south_txr.size_l, &a->south_txr.endian);
	if (a->south_txr.img == NULL)
		error(MALLOC_FAIL_SO, a);
	a->east_txr.img = (int *)mlx_get_data_addr(a->east_txr.ptr,
			&a->east_txr.bpp, &a->west_txr.size_l, &a->east_txr.endian);
	if (a->east_txr.img == NULL)
		error(MALLOC_FAIL_EA, a);
	a->west_txr.img = (int *)mlx_get_data_addr(a->west_txr.ptr,
			&a->west_txr.bpp, &a->east_txr.size_l, &a->west_txr.endian);
	if (a->west_txr.img == NULL)
		error(MALLOC_FAIL_WE, a);
}

void	wall_set(t_a *a)
{
	a->tex.dim = 64;
	a->north_txr.ptr = mlx_xpm_file_to_image(a->mlx.ptr, a->txr.north,
			&a->tex.dim, &a->tex.dim);
	if (a->north_txr.ptr == NULL)
		error(MALLOC_FAIL_NO, a);
	a->south_txr.ptr = mlx_xpm_file_to_image(a->mlx.ptr, a->txr.south,
			&a->tex.dim, &a->tex.dim);
	if (a->south_txr.ptr == NULL)
		error(MALLOC_FAIL_SO, a);
	a->east_txr.ptr = mlx_xpm_file_to_image(a->mlx.ptr, a->txr.east,
			&a->tex.dim, &a->tex.dim);
	if (a->east_txr.ptr == NULL)
		error(MALLOC_FAIL_EA, a);
	a->west_txr.ptr = mlx_xpm_file_to_image(a->mlx.ptr, a->txr.west,
			&a->tex.dim, &a->tex.dim);
	if (a->west_txr.ptr == NULL)
		error(MALLOC_FAIL_WE, a);
	wall_set2(a);
}

void	sprite_set(t_a *a)
{
	a->spr.z_buff = malloc(sizeof(double) * (a->res.w + 1));
	if (a->spr.z_buff == NULL)
		error(MALLOC_FAIL_SPR, a);
	a->spr.dist = malloc(sizeof(double) * (a->spr.amount + 1));
	if (a->spr.dist == NULL)
		error(MALLOC_FAIL_SPR, a);
	a->spr.dist = ft_memset(a->spr.dist, '\0', a->spr.amount);
	a->spr.order = malloc(sizeof(int) * a->spr.amount + 1);
	if (a->spr.order == NULL)
		error(MALLOC_FAIL_SPR, a);
	a->spr.order = ft_memset(a->spr.order, '\0', a->spr.amount);
	a->spr_txr.ptr = mlx_xpm_file_to_image(a->mlx.ptr, a->txr.sprite,
			&a->tex.dim, &a->tex.dim);
	if (a->spr_txr.ptr == NULL)
		error(MALLOC_FAIL_SPRITE, a);
	a->spr_txr.img = (int *)mlx_get_data_addr(a->spr_txr.ptr,
			&a->spr_txr.bpp, &a->spr_txr.size_l, &a->spr_txr.endian);
	if (a->spr_txr.img == NULL)
		error(MALLOC_FAIL_SPRITE, a);
}
