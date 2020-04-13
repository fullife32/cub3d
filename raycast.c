/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 15:25:24 by eassouli          #+#    #+#             */
/*   Updated: 2020/04/13 19:47:45 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

void	raycast_init(t_mlx *mlx, t_plr *plr)
{
	plr->pos_x = 3;
	plr->pos_y = 1;
	plr->dir_x = 0;
	plr->dir_y = 1;
	mlx->plane_x = 0;
	mlx->plane_y = 0.66;
	mlx->time = 0;
	mlx->old_time = 0;
	mlx->camera_x = 0;
	mlx->camera_y = 0;
	mlx->raydir_x = 0;
	mlx->raydir_y = 0;
	mlx->map_x = 0;
	mlx->map_y = 0;
	mlx->sidedist_x = 0;
	mlx->sidedist_y = 0;
	mlx->deltadst_x = 0;
	mlx->deltadst_y = 0;
	mlx->perp_wall_dist = 0;
	mlx->step_x = 0;
	mlx->step_y = 0;
	mlx->hit = 0;
	mlx->side = 0;
	mlx->line_h = 0;
	mlx->draw_start = 0;
	mlx->draw_end = 0;
}

// void	draw_vert_line(int x, t_mlx *mlx, int color)
// {
// 	printf("x = %d start = %d end = %d color %d\n", x, mlx->draw_start, mlx->draw_end, color);
// 	while (mlx->draw_start <= mlx->draw_end)
// 	{
// 		// mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, x, mlx->draw_start, color);
// 		mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, 250, 250, 0xFFFFFF);
// 		mlx->draw_start++;
// 	}
// }

int		raycast_create(t_res *res, t_map *map)
{
	int			x;
	t_mlx		mlx;
	t_plr		plr;

	raycast_init(&mlx, &plr);
	mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, res->width, res->height, "cub3d");
	x = 0;
	while (x < 630)
	{
		while (x < res->width)
		{
			mlx.camera_x = 2 * x / (double)res->width - 1;
			mlx.raydir_x = plr.dir_x + mlx.plane_x * mlx.camera_x;
			mlx.raydir_y = plr.dir_y + mlx.plane_y * mlx.camera_x;
			mlx.map_x = (int)plr.pos_x;
			mlx.map_y = (int)plr.pos_y;
			mlx.deltadst_x = (mlx.raydir_y == 0) ? 0 : ((mlx.raydir_x) == 0) ? 1 : fabs(1 / mlx.raydir_x);
			mlx.deltadst_y = (mlx.raydir_x == 0) ? 0 : ((mlx.raydir_y) == 0) ? 1 : fabs(1 / mlx.raydir_y);
			if (mlx.raydir_x < 0)
			{
				mlx.step_x = -1;
				mlx.sidedist_x = (plr.pos_x - mlx.map_x) * mlx.deltadst_x;
			}
			else
			{
				mlx.step_x = 1;
				mlx.sidedist_x = (mlx.map_x + 1.0 - plr.pos_x) * mlx.deltadst_x;
			}
			if (mlx.raydir_y < 0)
			{
				mlx.step_y = -1;
				mlx.sidedist_y = (plr.pos_y - mlx.map_y) * mlx.deltadst_y;
			}
			else
			{
				mlx.step_y = 1;
				mlx.sidedist_y = (mlx.map_y + 1.0 - plr.pos_y) * mlx.deltadst_y;
			}
			mlx.hit = 0;
			while (mlx.hit == 0)
			{
				if (mlx.sidedist_x < mlx.sidedist_y)
				{
					mlx.sidedist_x += mlx.deltadst_x;
					mlx.map_x += mlx.step_x;
					mlx.side = 0;
				}
				else
				{
					mlx.sidedist_y += mlx.deltadst_y;
					mlx.map_y += mlx.step_y;
					mlx.side = 1;
				}
				if (map->map[mlx.map_y][mlx.map_x] == '1')
					mlx.hit = 1;
			}
			if (mlx.side == 0)
				mlx.perp_wall_dist = (mlx.map_x - plr.pos_x + (1 - mlx.step_x) / 2) / mlx.raydir_x;
			else
				mlx.perp_wall_dist = (mlx.map_y - plr.pos_y + (1 - mlx.step_y) / 2) / mlx.raydir_y;
			mlx.line_h = (int)(res->height / mlx.perp_wall_dist);
			mlx.draw_start = -mlx.line_h / 2 + res->height / 2;
			if (mlx.draw_start < 0)
				mlx.draw_start = 0;
			mlx.draw_end = mlx.line_h / 2 + res->height / 2;
			if (mlx.draw_end >= res->height)
				mlx.draw_end = res->height - 1;
			mlx.color = (mlx.side == 1) ? 0xFFFFFF / 2 : 0xFFFFFF;
			// printf("%c\n", map->map[(int)plr.pos_y][(int)plr.pos_x]);
			// printf("x = %d start = %d end = %d color %d\n", x, mlx.draw_start, mlx.draw_end, 0xFFFFFF);
			while (mlx.draw_start <= mlx.draw_end)
			{
				mlx_pixel_put(mlx.mlx_ptr, mlx.win_ptr, x, mlx.draw_start, mlx.color);
				mlx.draw_start++;
			}
			x++;
		}
	}
	mlx_loop(mlx.mlx_ptr);
	return (OK);
}
