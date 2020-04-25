/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 15:25:24 by eassouli          #+#    #+#             */
/*   Updated: 2020/04/25 16:12:13 by eassouli         ###   ########.fr       */
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
	all->mlx.color = (all->mlx.side == 1) ? 0xFF6347 : 0xFF7F50; //NS blue WE pink
}

void	draw_vert_line(int x, t_mlx *mlx, t_res *res)
{
	// printf("x = %d start = %d end = %d color %d\n", x, mlx.draw_start, mlx.draw_end, color);
	int i = 0;

	while (i < mlx->draw_start)
	{
		mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, x, i, 0xAAFFFF);
		i++;
	}
	while (mlx->draw_start <= mlx->draw_end)
	{
		mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, x, mlx->draw_start, mlx->color);
		mlx->draw_start++;
	}
	i = mlx->draw_start;
	while (i < res->height)
	{
		mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, x, i, 0xA2A2A2);
		i++;
	}
}

int		keyPress(int key, void *param)
{
	t_all	*all;

	all = (t_all *)(param);
	if (key == W)
	{
		if (all->map.map[(int)all->plr.pos_y][(int)(all->plr.pos_x + all->plr.dir_x * all->plr.move_speed)] != '1')
			all->plr.pos_x += all->plr.dir_x * all->plr.move_speed;
		if (all->map.map[(int)(all->plr.pos_y + all->plr.dir_y * all->plr.move_speed)][(int)all->plr.pos_x] != '1')
			all->plr.pos_y += all->plr.dir_y * all->plr.move_speed;
	}
	if (key == S)
	{
		if (all->map.map[(int)all->plr.pos_y][(int)(all->plr.pos_x - all->plr.dir_x * all->plr.move_speed)] != '1')
			all->plr.pos_x -= all->plr.dir_x * all->plr.move_speed;
		if (all->map.map[(int)(all->plr.pos_y - all->plr.dir_y * all->plr.move_speed)][(int)all->plr.pos_x] != '1')
			all->plr.pos_y -= all->plr.dir_y * all->plr.move_speed;
	}
	if (key == LR)
	{
		all->plr.olddir_y = all->plr.dir_y;
		all->plr.dir_y = all->plr.dir_y * cos(all->plr.rot_speed) - all->plr.dir_x * sin(all->plr.rot_speed);
		all->plr.dir_x = all->plr.olddir_y * sin(all->plr.rot_speed) + all->plr.dir_x * cos(all->plr.rot_speed);
		all->mlx.oldplane_y = all->mlx.plane_y;
		all->mlx.plane_y = all->mlx.plane_y * cos(all->plr.rot_speed) - all->mlx.plane_x * sin(all->plr.rot_speed);
		all->mlx.plane_x = all->mlx.oldplane_y * sin(all->plr.rot_speed) + all->mlx.plane_x * cos(all->plr.rot_speed);
	}
	if (key == RR)
	{
		all->plr.olddir_y = all->plr.dir_y;
		all->plr.dir_y = all->plr.dir_y * cos(-all->plr.rot_speed) - all->plr.dir_x * sin(-all->plr.rot_speed);
		all->plr.dir_x = all->plr.olddir_y * sin(-all->plr.rot_speed) + all->plr.dir_x * cos(-all->plr.rot_speed);
		all->mlx.oldplane_y = all->mlx.plane_y;
		all->mlx.plane_y = all->mlx.plane_y * cos(-all->plr.rot_speed) - all->mlx.plane_x * sin(-all->plr.rot_speed);
		all->mlx.plane_x = all->mlx.oldplane_y * sin(-all->plr.rot_speed) + all->mlx.plane_x * cos(-all->plr.rot_speed);
	}
	deal_key(key, param);
	return (OK);
}

int		keyRelease(int key, void *param)
{
	(void)key;
	(void)param;
	return (OK);
}

int		deal_key(int key, void *param)
{
	t_all	*all;

	(void)key;
	all = (t_all *)param;
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
	mlx_string_put(all->mlx.mlx_ptr, all->mlx.win_ptr, 30, 20, 0xFFFFFF, ft_itoa(1 / all->mlx.frame_time));
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
	all->plr.move_speed = all->mlx.frame_time * 30.0;
	all->plr.rot_speed = all->mlx.frame_time * 18.0;
	deal_key(0, all);
	while (1)
	{
		mlx_hook(all->mlx.win_ptr, 2, 0, keyPress, all);
		mlx_hook(all->mlx.win_ptr, 3, 0, keyRelease, all);
		// mlx_loop_hook(all->mlx.mlx_ptr, deal_key, all);
		mlx_loop(all->mlx.mlx_ptr);
	}
	return (OK);
}
