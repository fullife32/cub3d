/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 15:25:24 by eassouli          #+#    #+#             */
/*   Updated: 2020/04/10 18:07:00 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

int	raycast_init(t_mlx *mlx, t_plr *plr)
{
	plr->pos_x = 22;
	plr->pos_y = 12;
	plr->dir_x = -1;
	plr->dir_y = 0;
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
	return (OK);
}

int	raycast_create(t_res *res, t_map *map)
{
	int			x;
	int			w;
	t_mlx		mlx;
	t_plr	plr;

	raycast_init(&mlx, &plr);
	mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, res->width, res->height, "cub3d");
	mlx_loop(mlx.mlx_ptr);
	while (1)
	{
		x = 0;
		w = 1;
		while (x < w)
		{
			mlx.camera_x = 2 * x / (double)w - 1;
			mlx.raydir_x = plr.dir_x + mlx.plane_x * mlx.camera_x;
			mlx.raydir_y = plr.dir_y + mlx.plane_y * mlx.camera_x;
		}
		mlx.map_x = ((int)plr.pos_x);
		mlx.map_y = ((int)plr.pos_y);
		mlx.deltadst_x = fabs(1 / mlx.raydir_x);
		mlx.deltadst_y = fabs(1 / mlx.raydir_y);
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
		while (mlx.hit == 0)
		{
			if (mlx.sidedist_x < mlx.sidedist_y)
			{
				mlx.sidedist_x += mlx.deltadst_x;
				mlx.map_y += mlx.step_x;
				mlx.side = 0;
			}
			else
			{
				mlx.sidedist_y += mlx.deltadst_y;
				mlx.map_y += mlx.step_y;
				mlx.side = 1;
			}
			if (map->map[mlx.map_x][mlx.map_y] > '0')
				mlx.hit = 1;
		}
	}

	return (OK);
}