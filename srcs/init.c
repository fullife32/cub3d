/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 17:17:42 by eassouli          #+#    #+#             */
/*   Updated: 2020/10/27 12:14:58 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "raycast.h"

void	init_txr(t_a *a)
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

void	init_dir(t_a *a)
{
	a->dir.plane_x = 0;
	a->dir.plane_y = 0;
	a->dir.x = 0;
	a->dir.y = 0;
}

void	init_plr(t_a *a)
{
	a->plr.pos_x = -1;
	a->plr.pos_y = -1;
	a->plr.move_spd = 0.04;
	a->plr.rot_spd = 0.024;
}

void	init_mov(t_a *a)
{
	a->mov.mov[ESC] = FALSE;
	a->mov.mov[FW] = FALSE;
	a->mov.mov[BW] = FALSE;
	a->mov.mov[L] = FALSE;
	a->mov.mov[R] = FALSE;
	a->mov.mov[LR] = FALSE;
	a->mov.mov[RR] = FALSE;
}

int	init(t_a *a)
{
	if ((a->mlx.ptr = mlx_init()) == NULL)
		return (ERR);
	a->res.h = 0;
	a->res.w = 0;
	init_txr(a);
	a->map.map = 0;
	init_dir(a);
	init_plr(a);
	init_mov(a);
	return (OK);
}
