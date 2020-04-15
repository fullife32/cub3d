/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 15:25:24 by eassouli          #+#    #+#             */
/*   Updated: 2020/04/14 18:15:31 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

void	draw_vert_line(int x, t_mlx *mlx, int color)
{
	printf("x = %d start = %d end = %d color %d\n", x, mlx->draw_start, mlx->draw_end, color);
	while (mlx->draw_start <= mlx->draw_end)
	{
		mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, x, mlx->draw_start, mlx->color);
		mlx->draw_start++;
	}
}

int		raycast_create(t_res *res, t_map *map)
{
	int			x;
	t_mlx		mlx;
	t_plr		plr;

	mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, res->width, res->height, "cub3d");
	x = 0;
	plr.pos_x = 1; plr.pos_y = 3;
	plr.dir_x = -1; plr.dir_y = 0;
	mlx.plane_x = 0; mlx.plane_y = 0.66;
	mlx.time = 0; mlx.old_time = 0;
	while (x != res->width)
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
				mlx.sidedst_x = (plr.pos_x - mlx.map_x) * mlx.deltadst_x;
			}
			else
			{
				mlx.step_x = 1;
				mlx.sidedst_x = (mlx.map_x + 1.0 - plr.pos_x) * mlx.deltadst_x;
			}
			if (mlx.raydir_y < 0)
			{
				mlx.step_y = -1;
				mlx.sidedst_y = (plr.pos_y - mlx.map_y) * mlx.deltadst_y;
			}
			else
			{
				mlx.step_y = 1;
				mlx.sidedst_y = (mlx.map_y + 1.0 - plr.pos_y) * mlx.deltadst_y;
			}
			printf("%f\n", mlx.sidedst_y);
			mlx.hit = 0;
			while (mlx.hit == 0)
			{
				if (mlx.sidedst_x < mlx.sidedst_y)
				{
					mlx.sidedst_x += mlx.deltadst_x;
					mlx.map_x += mlx.step_x;
					mlx.side = 0;
				}
				else
				{
					mlx.sidedst_y += mlx.deltadst_y;
					mlx.map_y += mlx.step_y;
					mlx.side = 1;
				}
				if (map->map[mlx.map_x][mlx.map_y] == '1')
					mlx.hit = 1;
			}
			if (mlx.side == 0)
				mlx.perp_wall_dist = ((double)mlx.map_x - plr.pos_x + (1.0 - mlx.step_x) / 2) / mlx.raydir_x;
			else
				mlx.perp_wall_dist = ((double)mlx.map_y - plr.pos_y + (1.0 - (double)mlx.step_y) / 2) / mlx.raydir_y;
			mlx.line_h = (int)(res->height / mlx.perp_wall_dist);
			mlx.draw_start = -mlx.line_h / 2 + res->height / 2;
			if (mlx.draw_start < 0)
				mlx.draw_start = 0;
			mlx.draw_end = mlx.line_h / 2 + res->height / 2;
			if (mlx.draw_end >= res->height)
				mlx.draw_end = res->height - 1;
			mlx.color = (mlx.side == 1) ? 0xFFAAAA : 0xAAFFFF;
			printf("%c\n", map->map[(int)plr.pos_x][(int)plr.pos_y]);
			printf("x = %d start = %d end = %d color %d\n", x, mlx.draw_start, mlx.draw_end, mlx.color);
			draw_vert_line(x, &mlx, mlx.color);
			x++;
		}
	}
	mlx_loop(mlx.mlx_ptr);
	return (OK);
}
