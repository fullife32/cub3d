/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 14:38:41 by eassouli          #+#    #+#             */
/*   Updated: 2021/01/08 13:15:39 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dir_init(t_a *a)
{
	a->dir.plane_x = 0;
	a->dir.plane_y = 0;
	a->dir.x = 0;
	a->dir.y = 0;
}

void	mov_init(t_a *a)
{
	a->mov.mov[ESC] = FALSE;
	a->mov.mov[FW] = FALSE;
	a->mov.mov[BW] = FALSE;
	a->mov.mov[L] = FALSE;
	a->mov.mov[R] = FALSE;
	a->mov.mov[LR] = FALSE;
	a->mov.mov[RR] = FALSE;
}

void	wall_init(t_a *a)
{
	a->north_txr.ptr = 0;
	a->south_txr.ptr = 0;
	a->east_txr.ptr = 0;
	a->west_txr.ptr = 0;
}

void	sprite_init(t_a *a)
{
	a->spr_txr.ptr = 0;
	a->spr.pos_x = 0;
	a->spr.pos_y = 0;
	a->spr.z_buff = 0;
	a->spr.dist = 0;
	a->spr.order = 0;
}
