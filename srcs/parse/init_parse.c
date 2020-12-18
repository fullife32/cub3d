/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 17:17:42 by eassouli          #+#    #+#             */
/*   Updated: 2020/12/18 15:24:28 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	txr_init(t_a *a)
{
	a->txr.f_rgb = -1;
	a->txr.c_rgb = -1;
	a->txr.north = 0;
	a->txr.south = 0;
	a->txr.west = 0;
	a->txr.east = 0;
	a->txr.sprite = 0;
	a->txr.floor = 0;
	a->txr.ceiling = 0;
}

void	plr_init(t_a *a)
{
	a->plr.pos_x = -1;
	a->plr.pos_y = -1;
	a->plr.move_spd = 0.04;
	a->plr.rot_spd = 0.024;
}

void	init(t_a *a)
{
	if ((a->mlx.ptr = mlx_init()) == NULL)
		error(MLX_INIT_FAIL, a);
	if ((a->mlx.line = malloc(sizeof(char **))) == NULL)
		error(MALLOC_FAIL_LINE, a);
	a->res.h = 0;
	a->res.w = 0;
	txr_init(a);
	plr_init(a);
	a->map.map = 0;
	a->map.first = NULL;
	a->map.lst = NULL;
	dir_init(a);
	mov_init(a);
	wall_init(a);
	sprite_init(a);
	a->bmp.fd = 0;
}
