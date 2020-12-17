/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 15:28:48 by eassouli          #+#    #+#             */
/*   Updated: 2020/12/17 17:19:36 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "raycast.h"

t_atx	wall_set(t_a *a)
{	
	if (a->map.side == 1 && a->dst.step_y == 1)
		return (a->north_txr); //NORD
	else if (a->map.side == 1 && a->dst.step_y == -1)
		return (a->south_txr); //SUD
	else if (a->map.side == 0 && a->dst.step_x == -1)
		return (a->east_txr); //EST
	return (a->west_txr); //OUEST
}

void	tx_set(t_a *a)
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
