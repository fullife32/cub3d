/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 15:25:24 by eassouli          #+#    #+#             */
/*   Updated: 2020/05/24 16:09:59 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

void	rc_dir(t_all *all)
{
	all->dir.cam_x = 2 * all->mlx.x / (double)all->res.w - 1;
	all->dir.raydir_y = all->plr.dir_y + all->dir.plane_y * all->dir.cam_x;
	all->dir.raydir_x = all->plr.dir_x + all->dir.plane_x * all->dir.cam_x;
	all->map.y = (int)all->plr.pos_y;
	all->map.x = (int)all->plr.pos_x;
	if (all->dir.raydir_x == 0)
		all->dst.deltadst_y = 0;
	else if (all->dir.raydir_y == 0)
		all->dst.deltadst_y = 1;
	else
		all->dst.deltadst_y = fabs(1 / all->dir.raydir_y);
	if (all->dir.raydir_y == 0)
		all->dst.deltadst_x = 0;
	else if (all->dir.raydir_x == 0)
		all->dst.deltadst_x = 1;
	else
		all->dst.deltadst_x = fabs(1 / all->dir.raydir_x);
}

void	rc_dst(t_all *all)
{
	if (all->dir.raydir_y < 0)
	{
		all->dst.step_y = -1;
		all->dst.sidedst_y = all->plr.pos_y - (double)all->map.y;
		all->dst.sidedst_y *= all->dst.deltadst_y;
	}
	else
	{
		all->dst.step_y = 1;
		all->dst.sidedst_y = (double)all->map.y + 1.0 - all->plr.pos_y;
		all->dst.sidedst_y *= all->dst.deltadst_y;
	}
	if (all->dir.raydir_x < 0)
	{
		all->dst.step_x = -1;
		all->dst.sidedst_x = all->plr.pos_x - (double)all->map.x;
		all->dst.sidedst_x *= all->dst.deltadst_x;
	}
	else
	{
		all->dst.step_x = 1;
		all->dst.sidedst_x = (double)all->map.x + 1.0 - all->plr.pos_x;
		all->dst.sidedst_x *= all->dst.deltadst_x;
	}
}

void	rc_hit(t_all *all)
{
	all->map.hit = 0;
	while (all->map.hit == 0)
	{
		if (all->dst.sidedst_y < all->dst.sidedst_x)
		{
			all->dst.sidedst_y += all->dst.deltadst_y;
			all->map.y += all->dst.step_y;
			all->map.side = 0;
		}
		else
		{
			all->dst.sidedst_x += all->dst.deltadst_x;
			all->map.x += all->dst.step_x;
			all->map.side = 1;
		}
		if (all->map.map[all->map.y][all->map.x] == '1')
			all->map.hit = 1;
	}
}

void	rc_line(t_all *all)
{
	if (all->map.side == 0)
		all->dst.wall_dst = ((double)all->map.y - all->plr.pos_y + (1.0 - all->dst.step_y) / 2) / all->dir.raydir_y;
	else
		all->dst.wall_dst = ((double)all->map.x - all->plr.pos_x + (1.0 - all->dst.step_x) / 2) / all->dir.raydir_x;
	all->img.line_h = (int)(all->res.h / all->dst.wall_dst);
	all->img.px_start = -all->img.line_h / 2 + all->res.h / 2;
	if (all->img.px_start < 0)
		all->img.px_start = 0;
	all->img.px_end = all->img.line_h / 2 + all->res.h / 2;
	if (all->img.px_end >= all->res.h)
		all->img.px_end = all->res.h - 1;
	all->img.color = (all->map.side == 0) ? 0xFF7F50 : 0xFF6347;
}

void	px_vline(t_all	*all)
{
	int y;
	int pos;

	y = 0;
	while (y < all->img.px_start)
	{
		pos = (y * all->img.size_l + all->mlx.x * (all->img.bpp / 8));
		*(unsigned int *)(all->img.img + pos) = all->txr.c_rgb;
		y++;
	}
	while (all->img.px_start <= all->img.px_end)
	{
		pos = (all->img.px_start * all->img.size_l + all->mlx.x * (all->img.bpp / 8));
		*(unsigned int *)(all->img.img + pos) = all->img.color;
		all->img.px_start++;
	}
	y = all->img.px_start;
	while (y < all->res.h)
	{
		pos = (y * all->img.size_l + all->mlx.x * (all->img.bpp / 8));
		*(unsigned int *)(all->img.img + pos) = all->txr.f_rgb;
		y++;
	}
}

int		key_press(int key, t_all *all)
{
	all->mov.mov[key] = OK;
	return (OK);
}

int		key_release(int key, t_all *all)
{
	all->mov.mov[key] = FALSE;
	return (OK);
}

int		key_move(t_all *all)
{
	if (all->mov.mov[FW] == OK)
	{
		if (all->map.map[(int)all->plr.pos_y][(int)(all->plr.pos_x + all->plr.dir_x * all->plr.move_spd)] != '1')
			all->plr.pos_x += all->plr.dir_x * all->plr.move_spd;
		if (all->map.map[(int)(all->plr.pos_y + all->plr.dir_y * all->plr.move_spd)][(int)all->plr.pos_x] != '1')
			all->plr.pos_y += all->plr.dir_y * all->plr.move_spd;
	}
	if (all->mov.mov[BW] == OK)
	{
		if (all->map.map[(int)all->plr.pos_y][(int)(all->plr.pos_x - all->plr.dir_x * all->plr.move_spd)] != '1')
			all->plr.pos_x -= all->plr.dir_x * all->plr.move_spd;
		if (all->map.map[(int)(all->plr.pos_y - all->plr.dir_y * all->plr.move_spd)][(int)all->plr.pos_x] != '1')
			all->plr.pos_y -= all->plr.dir_y * all->plr.move_spd;
	}
	if (all->mov.mov[LR] == OK)
	{
		all->plr.olddir_y = all->plr.dir_y;
		all->plr.dir_y = all->plr.dir_y * cos(all->plr.rot_spd) - all->plr.dir_x * sin(all->plr.rot_spd);
		all->plr.dir_x = all->plr.olddir_y * sin(all->plr.rot_spd) + all->plr.dir_x * cos(all->plr.rot_spd);
		all->dir.oldplane_y = all->dir.plane_y;
		all->dir.plane_y = all->dir.plane_y * cos(all->plr.rot_spd) - all->dir.plane_x * sin(all->plr.rot_spd);
		all->dir.plane_x = all->dir.oldplane_y * sin(all->plr.rot_spd) + all->dir.plane_x * cos(all->plr.rot_spd);
	}
	if (all->mov.mov[RR] == OK)
	{
		all->plr.olddir_y = all->plr.dir_y;
		all->plr.dir_y = all->plr.dir_y * cos(-all->plr.rot_spd) - all->plr.dir_x * sin(-all->plr.rot_spd);
		all->plr.dir_x = all->plr.olddir_y * sin(-all->plr.rot_spd) + all->plr.dir_x * cos(-all->plr.rot_spd);
		all->dir.oldplane_y = all->dir.plane_y;
		all->dir.plane_y = all->dir.plane_y * cos(-all->plr.rot_spd) - all->dir.plane_x * sin(-all->plr.rot_spd);
		all->dir.plane_x = all->dir.oldplane_y * sin(-all->plr.rot_spd) + all->dir.plane_x * cos(-all->plr.rot_spd);
	}
	if (all->mov.mov[RUN] == OK)
		all->plr.move_spd = all->mlx.frame_time * 10.0;
	if (all->mov.mov[RUN] == FALSE)
		all->plr.move_spd = all->mlx.frame_time * 5.0;
	return (OK);
}

int		rc_loop(t_all *all)
{
	key_move(all);
	all->mlx.x = 0;
	while (all->mlx.x < all->res.w)
	{
		// printf("%f\n", all->dst.sidedst_x);
		// printf("%c\n", all->map->map[(int)all->plr.pos_y][(int)all->plr.pos_x]);
		// printf("x = %d start = %d end = %d color %d\n", x, all->img.px_start, all->img.px_end, all->img.color);
		
		rc_dir(all);
		rc_dst(all);
		rc_hit(all);
		rc_line(all);
		px_vline(all);
		all->mlx.x++;
	}
	mlx_put_image_to_window(all->mlx.mlx, all->mlx.win, all->img.img_ptr, 0, 0);
	mlx_string_put(all->mlx.mlx, all->mlx.win, 20, 20, 0xFFFFFF, ft_itoa(1 / all->mlx.frame_time));
	return (OK);
}

int		raycast(t_all *all)
{
	all->mlx.mlx = mlx_init();
	all->mlx.win = mlx_new_window(all->mlx.mlx, all->res.w, all->res.h, "cub3d");
	all->img.img_ptr = mlx_new_image(all->mlx.mlx, all->res.w, all->res.h);
	all->img.img = mlx_get_data_addr(all->img.img_ptr, &all->img.bpp, &all->img.size_l, &all->img.endian);
	mlx_hook(all->mlx.win, 2, (1L<<0), key_press, all);
	mlx_hook(all->mlx.win, 3, (1L<<1), key_release, all);
	mlx_loop_hook(all->mlx.mlx, rc_loop, all);
	mlx_loop(all->mlx.mlx);
	return (OK);
}
