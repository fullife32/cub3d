/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 15:25:24 by eassouli          #+#    #+#             */
/*   Updated: 2020/04/26 01:33:35 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

void	raycast_dir(t_all *all)
{
	all->mlx.camera_x = 2 * all->mlx.x / (double)all->res.width - 1;
	all->mlx.raydir_y = all->plr.dir_y + all->mlx.plane_y * all->mlx.camera_x;
	all->mlx.raydir_x = all->plr.dir_x + all->mlx.plane_x * all->mlx.camera_x;
	all->mlx.map_y = (int)all->plr.pos_y;
	all->mlx.map_x = (int)all->plr.pos_x;
	if (all->mlx.raydir_x == 0)
		all->mlx.deltadst_y = 0;
	else if (all->mlx.raydir_y == 0)
		all->mlx.deltadst_y = 1;
	else
		all->mlx.deltadst_y = fabs(1 / all->mlx.raydir_y);
	if (all->mlx.raydir_y == 0)
		all->mlx.deltadst_x = 0;
	else if (all->mlx.raydir_x == 0)
		all->mlx.deltadst_x = 1;
	else
		all->mlx.deltadst_x = fabs(1 / all->mlx.raydir_x);
}

void	raycast_dst(t_all *all)
{
	if (all->mlx.raydir_y < 0)
	{
		all->mlx.step_y = -1;
		all->mlx.sidedst_y = all->plr.pos_y - (double)all->mlx.map_y;
		all->mlx.sidedst_y *= all->mlx.deltadst_y;
	}
	else
	{
		all->mlx.step_y = 1;
		all->mlx.sidedst_y = (double)all->mlx.map_y + 1.0 - all->plr.pos_y;
		all->mlx.sidedst_y *= all->mlx.deltadst_y;
	}
	if (all->mlx.raydir_x < 0)
	{
		all->mlx.step_x = -1;
		all->mlx.sidedst_x = all->plr.pos_x - (double)all->mlx.map_x;
		all->mlx.sidedst_x *= all->mlx.deltadst_x;
	}
	else
	{
		all->mlx.step_x = 1;
		all->mlx.sidedst_x = (double)all->mlx.map_x + 1.0 - all->plr.pos_x;
		all->mlx.sidedst_x *= all->mlx.deltadst_x;
	}
}

void	raycast_hit(t_all *all)
{
	all->mlx.hit = 0;
	while (all->mlx.hit == 0)
	{
		if (all->mlx.sidedst_y < all->mlx.sidedst_x)
		{
			all->mlx.sidedst_y += all->mlx.deltadst_y;
			all->mlx.map_y += all->mlx.step_y;
			all->mlx.side = 0;
		}
		else
		{
			all->mlx.sidedst_x += all->mlx.deltadst_x;
			all->mlx.map_x += all->mlx.step_x;
			all->mlx.side = 1;
		}
		if (all->map.map[all->mlx.map_y][all->mlx.map_x] == '1')
			all->mlx.hit = 1;
	}
}

void	raycast_line(t_all *all)
{
	if (all->mlx.side == 0)
		all->mlx.perp_wall_dist = ((double)all->mlx.map_y - all->plr.pos_y + (1.0 - all->mlx.step_y) / 2) / all->mlx.raydir_y;
	else
		all->mlx.perp_wall_dist = ((double)all->mlx.map_x - all->plr.pos_x + (1.0 - all->mlx.step_x) / 2) / all->mlx.raydir_x;
	all->mlx.line_h = (int)(all->res.height / all->mlx.perp_wall_dist);
	all->mlx.draw_start = -all->mlx.line_h / 2 + all->res.height / 2;
	if (all->mlx.draw_start < 0)
		all->mlx.draw_start = 0;
	all->mlx.draw_end = all->mlx.line_h / 2 + all->res.height / 2;
	if (all->mlx.draw_end >= all->res.height)
		all->mlx.draw_end = all->res.height - 1;
	all->mlx.color = (all->mlx.side == 0) ? 0xFF7F50 : 0xFF6347;
}

void	draw_vert_line(int x, t_mlx *mlx, t_res *res)
{
	// printf("x = %d start = %d end = %d color %d\n", x, mlx.draw_start, mlx.draw_end, color);
	int y;
	int pos;

	y = 0;
	while (y < mlx->draw_start)
	{
		pos = (y * mlx->size_line + x * (mlx->bpp / 8));
		*(unsigned int *)(mlx->img + pos) = 0x00BFFF;
		y++;
	}
	while (mlx->draw_start <= mlx->draw_end)
	{
		pos = (mlx->draw_start * mlx->size_line + x * (mlx->bpp / 8));
		*(unsigned int *)(mlx->img + pos) = mlx->color;
		mlx->draw_start++;
	}
	y = mlx->draw_start;
	while (y < res->height)
	{
		pos = (y * mlx->size_line + x * (mlx->bpp / 8));
		*(unsigned int *)(mlx->img + pos) = 0x708090;
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

int		movement(t_all *all)
{
	if (all->mov.mov[FW] == OK)
	{
		if (all->map.map[(int)all->plr.pos_y][(int)(all->plr.pos_x + all->plr.dir_x * all->plr.move_speed)] != '1')
			all->plr.pos_x += all->plr.dir_x * all->plr.move_speed;
		if (all->map.map[(int)(all->plr.pos_y + all->plr.dir_y * all->plr.move_speed)][(int)all->plr.pos_x] != '1')
			all->plr.pos_y += all->plr.dir_y * all->plr.move_speed;
	}
	if (all->mov.mov[BW] == OK)
	{
		if (all->map.map[(int)all->plr.pos_y][(int)(all->plr.pos_x - all->plr.dir_x * all->plr.move_speed)] != '1')
			all->plr.pos_x -= all->plr.dir_x * all->plr.move_speed;
		if (all->map.map[(int)(all->plr.pos_y - all->plr.dir_y * all->plr.move_speed)][(int)all->plr.pos_x] != '1')
			all->plr.pos_y -= all->plr.dir_y * all->plr.move_speed;
	}
	if (all->mov.mov[LR] == OK)
	{
		all->plr.olddir_y = all->plr.dir_y;
		all->plr.dir_y = all->plr.dir_y * cos(all->plr.rot_speed) - all->plr.dir_x * sin(all->plr.rot_speed);
		all->plr.dir_x = all->plr.olddir_y * sin(all->plr.rot_speed) + all->plr.dir_x * cos(all->plr.rot_speed);
		all->mlx.oldplane_y = all->mlx.plane_y;
		all->mlx.plane_y = all->mlx.plane_y * cos(all->plr.rot_speed) - all->mlx.plane_x * sin(all->plr.rot_speed);
		all->mlx.plane_x = all->mlx.oldplane_y * sin(all->plr.rot_speed) + all->mlx.plane_x * cos(all->plr.rot_speed);
	}
	if (all->mov.mov[RR] == OK)
	{
		all->plr.olddir_y = all->plr.dir_y;
		all->plr.dir_y = all->plr.dir_y * cos(-all->plr.rot_speed) - all->plr.dir_x * sin(-all->plr.rot_speed);
		all->plr.dir_x = all->plr.olddir_y * sin(-all->plr.rot_speed) + all->plr.dir_x * cos(-all->plr.rot_speed);
		all->mlx.oldplane_y = all->mlx.plane_y;
		all->mlx.plane_y = all->mlx.plane_y * cos(-all->plr.rot_speed) - all->mlx.plane_x * sin(-all->plr.rot_speed);
		all->mlx.plane_x = all->mlx.oldplane_y * sin(-all->plr.rot_speed) + all->mlx.plane_x * cos(-all->plr.rot_speed);
	}
	if (all->mov.mov[RUN] == OK)
		all->plr.move_speed = all->mlx.frame_time * 10.0;
	if (all->mov.mov[RUN] == FALSE)
		all->plr.move_speed = all->mlx.frame_time * 5.0;
	return (OK);
}

int		deal_key(t_all *all)
{
	movement(all);
	all->mlx.x = 0;
	while (all->mlx.x < all->res.width)
	{
		// printf("%f\n", all->mlx.sidedst_x);
		// printf("%c\n", all->map->map[(int)all->plr.pos_y][(int)all->plr.pos_x]);
		// printf("x = %d start = %d end = %d color %d\n", x, all->mlx.draw_start, all->mlx.draw_end, all->mlx.color);
		
		raycast_dir(all);
		raycast_dst(all);
		raycast_hit(all);
		raycast_line(all);
		draw_vert_line(all->mlx.x, &all->mlx, &all->res);
		all->mlx.x++;
	}
	mlx_put_image_to_window(all->mlx.mlx_ptr, all->mlx.win_ptr, all->mlx.img_ptr, 0, 0);
	mlx_string_put(all->mlx.mlx_ptr, all->mlx.win_ptr, 20, 20, 0xFFFFFF, ft_itoa(1 / all->mlx.frame_time));
	return (OK);
}

int		raycast(t_all *all)
{
	all->mlx.mlx_ptr = mlx_init();
	all->mlx.win_ptr = mlx_new_window(all->mlx.mlx_ptr, all->res.width, all->res.height, "cub3d");
	all->plr.pos_y = 9.5; all->plr.pos_x = 9.5;
	all->plr.dir_y = -1; all->plr.dir_x = 0;
	all->mlx.plane_y = 0; all->mlx.plane_x = 0.66;
	all->mlx.time = 0; all->mlx.old_time = 0;
	all->mlx.frame_time = 0.008;
	all->plr.move_speed = all->mlx.frame_time * 5.0;
	all->plr.rot_speed = all->mlx.frame_time * 3.0;
	all->mlx.img_ptr = mlx_new_image(all->mlx.mlx_ptr, all->res.width, all->res.height);
	all->mlx.img = mlx_get_data_addr(all->mlx.img_ptr, &all->mlx.bpp, &all->mlx.size_line, &all->mlx.endian);
	mlx_hook(all->mlx.win_ptr, 2, 0, key_press, all);
	mlx_hook(all->mlx.win_ptr, 3, 0, key_release, all);
	mlx_loop_hook(all->mlx.mlx_ptr, deal_key, all);
	mlx_loop(all->mlx.mlx_ptr);
	return (OK);
}
