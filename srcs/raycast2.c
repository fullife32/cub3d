/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 15:25:24 by eassouli          #+#    #+#             */
/*   Updated: 2020/10/28 12:52:11 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "raycast.h"

void	rc_dir(t_a *a)
{
	a->dir.cam_x = 2 * a->mlx.x / (double)a->res.w - 1;
	a->dir.ray_x = a->dir.x + a->dir.plane_x * a->dir.cam_x;
	a->dir.ray_y = a->dir.y + a->dir.plane_y * a->dir.cam_x;
	a->map.x = (int)a->plr.pos_x;
	a->map.y = (int)a->plr.pos_y;
	if (a->dir.ray_y == 0)
		a->dst.delta_x = 0;
	else if (a->dir.ray_x == 0)
		a->dst.delta_x = 1;
	else
		a->dst.delta_x = fabs(1 / a->dir.ray_x);
	if (a->dir.ray_x == 0)
		a->dst.delta_y = 0;
	else if (a->dir.ray_y == 0)
		a->dst.delta_y = 1;
	else
		a->dst.delta_y = fabs(1 / a->dir.ray_y);
}

void	rc_dst(t_a *a)
{
	if (a->dir.ray_x < 0)
	{
		a->dst.step_x = -1;
		a->dst.side_x = a->plr.pos_x - (double)a->map.x;
		a->dst.side_x *= a->dst.delta_x;
	}
	else
	{
		a->dst.step_x = 1;
		a->dst.side_x = (double)a->map.x + 1.0 - a->plr.pos_x;
		a->dst.side_x *= a->dst.delta_x;
	}
	if (a->dir.ray_y < 0)
	{
		a->dst.step_y = -1;
		a->dst.side_y = a->plr.pos_y - (double)a->map.y;
		a->dst.side_y *= a->dst.delta_y;
	}
	else
	{
		a->dst.step_y = 1;
		a->dst.side_y = (double)a->map.y + 1.0 - a->plr.pos_y;
		a->dst.side_y *= a->dst.delta_y;
	}
}

void	rc_hit(t_a *a)
{
	a->map.hit = 0;
	while (a->map.hit == 0)
	{
		if (a->dst.side_x < a->dst.side_y)
		{
			a->dst.side_x += a->dst.delta_x;
			a->map.x += a->dst.step_x;
			a->map.side = 0;
		}
		else
		{
			a->dst.side_y += a->dst.delta_y;
			a->map.y += a->dst.step_y;
			a->map.side = 1;
		}
		if (a->map.map[a->map.y][a->map.x] == '1')
			a->map.hit = 1;
	}
}

void	rc_line(t_a *a)
{
	if (a->map.side == 0)
		a->dst.wall = ((double)a->map.x - a->plr.pos_x + (1.0 - a->dst.step_x) / 2) / a->dir.ray_x;
	else
		a->dst.wall = ((double)a->map.y - a->plr.pos_y + (1.0 - a->dst.step_y) / 2) / a->dir.ray_y;
	a->img.line_h = (int)(a->res.h / a->dst.wall);
	a->img.px_start = -a->img.line_h / 2 + a->res.h / 2;
	if (a->img.px_start < 0)
		a->img.px_start = 0;
	a->img.px_end = a->img.line_h / 2 + a->res.h / 2;
	if (a->img.px_end >= a->res.h)
		a->img.px_end = a->res.h - 1;
}

void	rc_tex(t_a *a)
{
	a->tex.tx = wall_set(a);
	if (a->map.side == 0)
		a->tex.wall_x = a->plr.pos_y + a->dst.wall * a->dir.ray_y;
	else
		a->tex.wall_x = a->plr.pos_x + a->dst.wall * a->dir.ray_x;
	a->tex.wall_x -= floor(a->tex.wall_x);
	a->tex.x = (int)(a->tex.wall_x * (double)(a->tex.dim));
	if (a->map.side == 0 && a->dir.ray_x < 0)
		a->tex.x = a->tex.dim - a->tex.x - 1;
	if (a->map.side == 1 && a->dir.ray_y > 0)
		a->tex.x = a->tex.dim - a->tex.x - 1;
	a->tex.step = 1.0 * a->tex.dim / a->img.line_h;
	a->tex.pos = (a->img.px_start - a->res.h / 2 + a->img.line_h / 2) * a->tex.step;
	a->spr.z_buff[a->mlx.x] = a->dst.wall;
}

void	rc_spr(t_a *a)
{
	sprite_dist(a);
}
