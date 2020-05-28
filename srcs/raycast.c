/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 15:25:24 by eassouli          #+#    #+#             */
/*   Updated: 2020/05/29 00:50:45 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

void	rc_dir(t_a *a)
{
	a->dir.cam_x = 2 * a->mlx.x / (double)a->res.w - 1;
	a->dir.raydir_y = a->plr.dir_y + a->dir.plane_y * a->dir.cam_x;
	a->dir.raydir_x = a->plr.dir_x + a->dir.plane_x * a->dir.cam_x;
	a->map.y = (int)a->plr.pos_y;
	a->map.x = (int)a->plr.pos_x;
	if (a->dir.raydir_x == 0)
		a->dst.deltadst_y = 0;
	else if (a->dir.raydir_y == 0)
		a->dst.deltadst_y = 1;
	else
		a->dst.deltadst_y = fabs(1 / a->dir.raydir_y);
	if (a->dir.raydir_y == 0)
		a->dst.deltadst_x = 0;
	else if (a->dir.raydir_x == 0)
		a->dst.deltadst_x = 1;
	else
		a->dst.deltadst_x = fabs(1 / a->dir.raydir_x);
}

void	rc_dst(t_a *a)
{
	if (a->dir.raydir_y < 0)
	{
		a->dst.step_y = -1;
		a->dst.sidedst_y = a->plr.pos_y - (double)a->map.y;
		a->dst.sidedst_y *= a->dst.deltadst_y;
	}
	else
	{
		a->dst.step_y = 1;
		a->dst.sidedst_y = (double)a->map.y + 1.0 - a->plr.pos_y;
		a->dst.sidedst_y *= a->dst.deltadst_y;
	}
	if (a->dir.raydir_x < 0)
	{
		a->dst.step_x = -1;
		a->dst.sidedst_x = a->plr.pos_x - (double)a->map.x;
		a->dst.sidedst_x *= a->dst.deltadst_x;
	}
	else
	{
		a->dst.step_x = 1;
		a->dst.sidedst_x = (double)a->map.x + 1.0 - a->plr.pos_x;
		a->dst.sidedst_x *= a->dst.deltadst_x;
	}
}

void	rc_hit(t_a *a)
{
	a->map.hit = 0;
	while (a->map.hit == 0)
	{
		if (a->dst.sidedst_y < a->dst.sidedst_x)
		{
			a->dst.sidedst_y += a->dst.deltadst_y;
			a->map.y += a->dst.step_y;
			a->map.side = 0;
		}
		else
		{
			a->dst.sidedst_x += a->dst.deltadst_x;
			a->map.x += a->dst.step_x;
			a->map.side = 1;
		}
		if (a->map.map[a->map.y][a->map.x] == '1')
			a->map.hit = 1;
	}
}

void	rc_line(t_a *a)
{
	if (a->map.side == 0)
		a->dst.wa_dst = ((double)a->map.y - a->plr.pos_y + (1.0 - a->dst.step_y) / 2) / a->dir.raydir_y;
	else
		a->dst.wa_dst = ((double)a->map.x - a->plr.pos_x + (1.0 - a->dst.step_x) / 2) / a->dir.raydir_x;
	a->img.line_h = (int)(a->res.h / a->dst.wa_dst);
	a->img.px_start = -a->img.line_h / 2 + a->res.h / 2;
	if (a->img.px_start < 0)
		a->img.px_start = 0;
	a->img.px_end = a->img.line_h / 2 + a->res.h / 2;
	if (a->img.px_end >= a->res.h)
		a->img.px_end = a->res.h - 1;
	a->img.color = (a->map.side == 0) ? 0xFF7F50 : 0xFF6347;
}

void	px_vline(t_a	*a)
{
	int y;
	int pos;

	y = 0;
	while (y < a->img.px_start)
	{
		pos = (y * a->img.size_l + a->mlx.x * (a->img.bpp / 8));
		*(unsigned int *)(a->img.img + pos) = a->txr.c_rgb;
		y++;
	}
	while (a->img.px_start <= a->img.px_end)
	{
		pos = (a->img.px_start * a->img.size_l + a->mlx.x * (a->img.bpp / 8));
		*(unsigned int *)(a->img.img + pos) = a->img.color;
		a->img.px_start++;
	}
	y = a->img.px_start;
	while (y < a->res.h)
	{
		pos = (y * a->img.size_l + a->mlx.x * (a->img.bpp / 8));
		*(unsigned int *)(a->img.img + pos) = a->txr.f_rgb;
		y++;
	}
}

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
	if (a->mov.mov[FW] == OK)
	{
		if (a->map.map[(int)a->plr.pos_y][(int)(a->plr.pos_x + a->plr.dir_x * a->plr.move_spd)] != '1')
			a->plr.pos_x += a->plr.dir_x * a->plr.move_spd;
		if (a->map.map[(int)(a->plr.pos_y + a->plr.dir_y * a->plr.move_spd)][(int)a->plr.pos_x] != '1')
			a->plr.pos_y += a->plr.dir_y * a->plr.move_spd;
	}
	if (a->mov.mov[BW] == OK)
	{
		if (a->map.map[(int)a->plr.pos_y][(int)(a->plr.pos_x - a->plr.dir_x * a->plr.move_spd)] != '1')
			a->plr.pos_x -= a->plr.dir_x * a->plr.move_spd;
		if (a->map.map[(int)(a->plr.pos_y - a->plr.dir_y * a->plr.move_spd)][(int)a->plr.pos_x] != '1')
			a->plr.pos_y -= a->plr.dir_y * a->plr.move_spd;
	}
	if (a->mov.mov[LR] == OK)
	{
		a->plr.olddir_y = a->plr.dir_y;
		a->plr.dir_y = a->plr.dir_y * cos(a->plr.rot_spd) - a->plr.dir_x * sin(a->plr.rot_spd);
		a->plr.dir_x = a->plr.olddir_y * sin(a->plr.rot_spd) + a->plr.dir_x * cos(a->plr.rot_spd);
		a->dir.oldplane_y = a->dir.plane_y;
		a->dir.plane_y = a->dir.plane_y * cos(a->plr.rot_spd) - a->dir.plane_x * sin(a->plr.rot_spd);
		a->dir.plane_x = a->dir.oldplane_y * sin(a->plr.rot_spd) + a->dir.plane_x * cos(a->plr.rot_spd);
	}
	if (a->mov.mov[RR] == OK)
	{
		a->plr.olddir_y = a->plr.dir_y;
		a->plr.dir_y = a->plr.dir_y * cos(-a->plr.rot_spd) - a->plr.dir_x * sin(-a->plr.rot_spd);
		a->plr.dir_x = a->plr.olddir_y * sin(-a->plr.rot_spd) + a->plr.dir_x * cos(-a->plr.rot_spd);
		a->dir.oldplane_y = a->dir.plane_y;
		a->dir.plane_y = a->dir.plane_y * cos(-a->plr.rot_spd) - a->dir.plane_x * sin(-a->plr.rot_spd);
		a->dir.plane_x = a->dir.oldplane_y * sin(-a->plr.rot_spd) + a->dir.plane_x * cos(-a->plr.rot_spd);
	}
	return (OK);
}

int		rc_loop(t_a *a)
{
	key_move(a);
	a->mlx.x = 0;
	while (a->mlx.x < a->res.w)
	{
		// printf("%f\n", a->dst.sidedst_x);
		// printf("%c\n", a->map->map[(int)a->plr.pos_y][(int)a->plr.pos_x]);
		// printf("x = %d start = %d end = %d color %d\n", x, a->img.px_start, a->img.px_end, a->img.color);
		
		rc_dir(a);
		rc_dst(a);
		rc_hit(a);
		rc_line(a);
		px_vline(a);
		a->mlx.x++;
	}
	mlx_put_image_to_window(a->mlx.mlx, a->mlx.win, a->img.img_ptr, 0, 0);
	mlx_string_put(a->mlx.mlx, a->mlx.win, 20, 20, 0xFFFFFF, ft_itoa(1 / a->mlx.frame_time));
	return (OK);
}

int		raycast(t_a *a)
{
	a->mlx.win = mlx_new_window(a->mlx.mlx, a->res.w, a->res.h, "cub3d");
	a->img.img_ptr = mlx_new_image(a->mlx.mlx, a->res.w, a->res.h);
	a->img.img = mlx_get_data_addr(a->img.img_ptr, &a->img.bpp, &a->img.size_l, &a->img.endian);
	mlx_hook(a->mlx.win, 2, (1L<<0), key_press, a);
	mlx_hook(a->mlx.win, 3, (1L<<1), key_release, a);
	mlx_loop_hook(a->mlx.mlx, rc_loop, a);
	mlx_loop(a->mlx.mlx);
	return (OK);
}
