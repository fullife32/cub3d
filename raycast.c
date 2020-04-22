/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 15:25:24 by eassouli          #+#    #+#             */
/*   Updated: 2020/04/22 18:45:36 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

void	raycast_dir(t_big *big)
{
	big->mlx.camera_x = 2 * big->mlx.x / (double)big->res.width - 1;
	big->mlx.raydir_y = big->plr.dir_y + big->mlx.plane_y * big->mlx.camera_x;
	big->mlx.raydir_x = big->plr.dir_x + big->mlx.plane_x * big->mlx.camera_x;
	big->mlx.map_y = (int)big->plr.pos_y;
	big->mlx.map_x = (int)big->plr.pos_x;
	if (big->mlx.raydir_x == 0)
		big->mlx.deltadst_y = 0;
	else if (big->mlx.raydir_y == 0)
		big->mlx.deltadst_y = 1;
	else
		big->mlx.deltadst_y = fabs(1 / big->mlx.raydir_y);
	if (big->mlx.raydir_y == 0)
		big->mlx.deltadst_x = 0;
	else if (big->mlx.raydir_x == 0)
		big->mlx.deltadst_x = 1;
	else
		big->mlx.deltadst_x = fabs(1 / big->mlx.raydir_x);
}

void	raycast_dst(t_big *big)
{
	if (big->mlx.raydir_y < 0)
	{
		big->mlx.step_y = -1;
		big->mlx.sidedst_y = big->plr.pos_y - (double)big->mlx.map_y;
		big->mlx.sidedst_y *= big->mlx.deltadst_y;
	}
	else
	{
		big->mlx.step_y = 1;
		big->mlx.sidedst_y = (double)big->mlx.map_y + 1.0 - big->plr.pos_y;
		big->mlx.sidedst_y *= big->mlx.deltadst_y;
	}
	if (big->mlx.raydir_x < 0)
	{
		big->mlx.step_x = -1;
		big->mlx.sidedst_x = big->plr.pos_x - (double)big->mlx.map_x;
		big->mlx.sidedst_x *= big->mlx.deltadst_x;
	}
	else
	{
		big->mlx.step_x = 1;
		big->mlx.sidedst_x = (double)big->mlx.map_x + 1.0 - big->plr.pos_x;
		big->mlx.sidedst_x *= big->mlx.deltadst_x;
	}
}

void	raycast_hit(t_big *big)
{
	big->mlx.hit = 0;
	while (big->mlx.hit == 0)
	{
		if (big->mlx.sidedst_y < big->mlx.sidedst_x)
		{
			big->mlx.sidedst_y += big->mlx.deltadst_y;
			big->mlx.map_y += big->mlx.step_y;
			big->mlx.side = 0;
		}
		else
		{
			big->mlx.sidedst_x += big->mlx.deltadst_x;
			big->mlx.map_x += big->mlx.step_x;
			big->mlx.side = 1;
		}
		if (big->map.map[big->mlx.map_y][big->mlx.map_x] == '1')
			big->mlx.hit = 1;
	}
}

void	raycast_line(t_big *big)
{
	if (big->mlx.side == 0)
		big->mlx.perp_wall_dist = ((double)big->mlx.map_y - big->plr.pos_y + (1.0 - big->mlx.step_y) / 2) / big->mlx.raydir_y;
	else
		big->mlx.perp_wall_dist = ((double)big->mlx.map_x - big->plr.pos_x + (1.0 - big->mlx.step_x) / 2) / big->mlx.raydir_x;
	big->mlx.line_h = (int)(big->res.height / big->mlx.perp_wall_dist);
	big->mlx.draw_start = -big->mlx.line_h / 2 + big->res.height / 2;
	if (big->mlx.draw_start < 0)
		big->mlx.draw_start = 0;
	big->mlx.draw_end = big->mlx.line_h / 2 + big->res.height / 2;
	if (big->mlx.draw_end >= big->res.height)
		big->mlx.draw_end = big->res.height - 1;
	big->mlx.color = (big->mlx.side == 1) ? 0xFF6347 : 0xFF7F50; //NS blue WE pink
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
	t_big	*big;

	big = (t_big *)(param);
	if (key == W)
	{
		if (big->map.map[(int)big->plr.pos_y][(int)(big->plr.pos_x + big->plr.dir_x * big->plr.move_speed)] != '1')
			big->plr.pos_x += big->plr.dir_x * big->plr.move_speed;
		if (big->map.map[(int)(big->plr.pos_y + big->plr.dir_y * big->plr.move_speed)][(int)big->plr.pos_x] != '1')
			big->plr.pos_y += big->plr.dir_y * big->plr.move_speed;
	}
	if (key == S)
	{
		if (big->map.map[(int)big->plr.pos_y][(int)(big->plr.pos_x - big->plr.dir_x * big->plr.move_speed)] != '1')
			big->plr.pos_x -= big->plr.dir_x * big->plr.move_speed;
		if (big->map.map[(int)(big->plr.pos_y - big->plr.dir_y * big->plr.move_speed)][(int)big->plr.pos_x] != '1')
			big->plr.pos_y -= big->plr.dir_y * big->plr.move_speed;
	}
	if (key == LR)
	{
		big->plr.olddir_y = big->plr.dir_y;
		big->plr.dir_y = big->plr.dir_y * cos(big->plr.rot_speed) - big->plr.dir_x * sin(big->plr.rot_speed);
		big->plr.dir_x = big->plr.olddir_y * sin(big->plr.rot_speed) + big->plr.dir_x * cos(big->plr.rot_speed);
		big->mlx.oldplane_y = big->mlx.plane_y;
		big->mlx.plane_y = big->mlx.plane_y * cos(big->plr.rot_speed) - big->mlx.plane_x * sin(big->plr.rot_speed);
		big->mlx.plane_x = big->mlx.oldplane_y * sin(big->plr.rot_speed) + big->mlx.plane_x * cos(big->plr.rot_speed);
	}
	if (key == RR)
	{
		big->plr.olddir_y = big->plr.dir_y;
		big->plr.dir_y = big->plr.dir_y * cos(-big->plr.rot_speed) - big->plr.dir_x * sin(-big->plr.rot_speed);
		big->plr.dir_x = big->plr.olddir_y * sin(-big->plr.rot_speed) + big->plr.dir_x * cos(-big->plr.rot_speed);
		big->mlx.oldplane_y = big->mlx.plane_y;
		big->mlx.plane_y = big->mlx.plane_y * cos(-big->plr.rot_speed) - big->mlx.plane_x * sin(-big->plr.rot_speed);
		big->mlx.plane_x = big->mlx.oldplane_y * sin(-big->plr.rot_speed) + big->mlx.plane_x * cos(-big->plr.rot_speed);
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
	t_big	*big;

	(void)key;
	big = (t_big *)param;
	big->mlx.x = 0;
	while (big->mlx.x < big->res.width)
	{
		// printf("%f\n", big->mlx.sidedst_x);
		// printf("%c\n", big->map->map[(int)big->plr.pos_y][(int)big->plr.pos_x]);
		// printf("x = %d start = %d end = %d color %d\n", x, big->mlx.draw_start, big->mlx.draw_end, big->mlx.color);
		
		raycast_dir(big);
		raycast_dst(big);
		raycast_hit(big);
		raycast_line(big);
		draw_vert_line(big->mlx.x, &big->mlx, &big->res);
		big->mlx.x++;
	}
	mlx_string_put(big->mlx.mlx_ptr, big->mlx.win_ptr, 30, 20, 0xFFFFFF, ft_itoa(1 / big->mlx.frame_time));
	return (OK);
}

int		raycast(t_big *big)
{
	big->mlx.mlx_ptr = mlx_init();
	big->mlx.win_ptr = mlx_new_window(big->mlx.mlx_ptr, big->res.width, big->res.height, "cub3d");
	big->plr.pos_y = 9.5; big->plr.pos_x = 9.5;
	big->plr.dir_y = -1; big->plr.dir_x = 0;
	big->mlx.plane_y = 0; big->mlx.plane_x = 0.66;
	big->mlx.time = 0; big->mlx.old_time = 0;
	big->mlx.frame_time = 0.008;
	big->plr.move_speed = big->mlx.frame_time * 30.0;
	big->plr.rot_speed = big->mlx.frame_time * 18.0;
	deal_key(0, big);
	while (1)
	{
		mlx_hook(big->mlx.win_ptr, 2, 0, keyPress, big);
		mlx_hook(big->mlx.win_ptr, 3, 0, keyRelease, big);
		// mlx_loop_hook(big->mlx.mlx_ptr, deal_key, big);
		mlx_loop(big->mlx.mlx_ptr);
	}
	return (OK);
}
