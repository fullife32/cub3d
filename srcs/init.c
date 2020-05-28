/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 17:17:42 by eassouli          #+#    #+#             */
/*   Updated: 2020/05/29 00:51:24 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	init(t_a *a)
{
	a->mlx.mlx = mlx_init();
	a->res.h = 0;
	a->res.w = 0;
	a->txr.f_rgb = -1;
	a->txr.c_rgb = -1;
	a->txr.n = 0;
	a->txr.s = 0;
	a->txr.w = 0;
	a->txr.e = 0;
	a->txr.spt = 0;
	a->txr.f = 0;
	a->txr.c = 0;
	a->map.map = 0;
	a->dir.plane_y = 0;
	a->dir.plane_x = 0.66;
	a->mlx.frame_time = 0.004;
	a->plr.pos_y = -1;
	a->plr.pos_x = -1;
	a->plr.move_spd = a->mlx.frame_time * 5.0;
	a->plr.rot_spd = a->mlx.frame_time * 3.0;
	a->mov.mov[FW] = FALSE;
	a->mov.mov[BW] = FALSE;
	a->mov.mov[L] = FALSE;
	a->mov.mov[R] = FALSE;
	a->mov.mov[LR] = FALSE;
	a->mov.mov[RR] = FALSE;
}
