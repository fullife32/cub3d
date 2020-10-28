/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 15:05:04 by eassouli          #+#    #+#             */
/*   Updated: 2020/10/28 20:47:47 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "raycast.h"

int		key_press(int key, t_a *a)
{
	a->mov.mov[key] = OK;
	return (OK);
}

int		key_release(int key, t_a *a)
{
	a->mov.mov[key] = FALSE;
	return (OK);
}

int		key_move(t_a *a)
{
	if (a->mov.mov[ESC] == OK)
		destroy(a);
	if (a->mov.mov[FW] == OK)
	{
		if (a->map.map[(int)a->plr.pos_y][(int)(a->plr.pos_x + a->dir.x * a->plr.move_spd)] != '1'
		&& a->map.map[(int)a->plr.pos_y][(int)(a->plr.pos_x + a->dir.x * a->plr.move_spd)] != '2')
			a->plr.pos_x += a->dir.x * a->plr.move_spd;
		if (a->map.map[(int)(a->plr.pos_y + a->dir.y * a->plr.move_spd)][(int)a->plr.pos_x] != '1'
		&& a->map.map[(int)(a->plr.pos_y + a->dir.y * a->plr.move_spd)][(int)a->plr.pos_x] != '2')
			a->plr.pos_y += a->dir.y * a->plr.move_spd;
	}
	if (a->mov.mov[BW] == OK)
	{
		if (a->map.map[(int)a->plr.pos_y][(int)(a->plr.pos_x - a->dir.x * a->plr.move_spd)] != '1'
		&& a->map.map[(int)a->plr.pos_y][(int)(a->plr.pos_x - a->dir.x * a->plr.move_spd)] != '2')
			a->plr.pos_x -= a->dir.x * a->plr.move_spd;
		if (a->map.map[(int)(a->plr.pos_y - a->dir.y * a->plr.move_spd)][(int)a->plr.pos_x] != '1'
		&& a->map.map[(int)(a->plr.pos_y - a->dir.y * a->plr.move_spd)][(int)a->plr.pos_x] != '2')
			a->plr.pos_y -= a->dir.y * a->plr.move_spd;
	}
	if (a->mov.mov[L] == OK)
	{
		if (a->map.map[(int)a->plr.pos_y][(int)(a->plr.pos_x - a->dir.plane_x * a->plr.move_spd)] != '1'
		&& a->map.map[(int)a->plr.pos_y][(int)(a->plr.pos_x - a->dir.plane_x * a->plr.move_spd)] != '2')
			a->plr.pos_x -= a->dir.plane_x * a->plr.move_spd;
		if (a->map.map[(int)(a->plr.pos_y - a->dir.plane_y * a->plr.move_spd)][(int)a->plr.pos_x] != '1'
		&& a->map.map[(int)(a->plr.pos_y - a->dir.plane_y * a->plr.move_spd)][(int)a->plr.pos_x] != '2')
			a->plr.pos_y -= a->dir.plane_y * a->plr.move_spd;
	}
	if (a->mov.mov[R] == OK)
	{
		if (a->map.map[(int)a->plr.pos_y][(int)(a->plr.pos_x + a->dir.plane_x * a->plr.move_spd)] != '1'
		&& a->map.map[(int)a->plr.pos_y][(int)(a->plr.pos_x + a->dir.plane_x * a->plr.move_spd)] != '2')
			a->plr.pos_x += a->dir.plane_x * a->plr.move_spd;
		if (a->map.map[(int)(a->plr.pos_y + a->dir.plane_y * a->plr.move_spd)][(int)a->plr.pos_x] != '1'
		&& a->map.map[(int)(a->plr.pos_y + a->dir.plane_y * a->plr.move_spd)][(int)a->plr.pos_x] != '2')
			a->plr.pos_y += a->dir.plane_y * a->plr.move_spd;
	}
	if (a->mov.mov[LR] == OK)
	{
		a->dir.old_x = a->dir.x;
		a->dir.x = a->dir.x * cos(-a->plr.rot_spd) - a->dir.y * sin(-a->plr.rot_spd);
		a->dir.y = a->dir.old_x * sin(-a->plr.rot_spd) + a->dir.y * cos(-a->plr.rot_spd);
		a->dir.oldplane_x = a->dir.plane_x;
		a->dir.plane_x = a->dir.plane_x * cos(-a->plr.rot_spd) - a->dir.plane_y * sin(-a->plr.rot_spd);
		a->dir.plane_y = a->dir.oldplane_x * sin(-a->plr.rot_spd) + a->dir.plane_y * cos(-a->plr.rot_spd);
	}
	if (a->mov.mov[RR] == OK)
	{
		a->dir.old_x = a->dir.x;
		a->dir.x = a->dir.x * cos(a->plr.rot_spd) - a->dir.y * sin(a->plr.rot_spd);
		a->dir.y = a->dir.old_x * sin(a->plr.rot_spd) + a->dir.y * cos(a->plr.rot_spd);
		a->dir.oldplane_x = a->dir.plane_x;
		a->dir.plane_x = a->dir.plane_x * cos(a->plr.rot_spd) - a->dir.plane_y * sin(a->plr.rot_spd);
		a->dir.plane_y = a->dir.oldplane_x * sin(a->plr.rot_spd) + a->dir.plane_y * cos(a->plr.rot_spd);
	}
	return (OK);
}
