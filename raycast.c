/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 15:25:24 by eassouli          #+#    #+#             */
/*   Updated: 2020/04/20 18:16:54 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

int	deal_key(int key, void *params)
{
	(void)params;
	ft_putnbr_fd(key, 1);
	return (OK);
}

void	draw_vert_line(int x, t_mlx *mlx)
{
	// printf("x = %d start = %d end = %d color %d\n", x, mlx->draw_start, mlx->draw_end, color);
	while (mlx->draw_start <= mlx->draw_end)
	{
		mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, x, mlx->draw_start, mlx->color);
		mlx->draw_start++;
	}
}

int		raycast_create(t_res *res, t_map *map)
{
	int			x;
	t_big		big;

	big.mlx.mlx_ptr = mlx_init();
	big.mlx.win_ptr = mlx_new_window(big.mlx.mlx_ptr, res->width, res->height, "cub3d");
	x = 0;
	big.plr.pos_y = 2.5; big.plr.pos_x = 2.5;
	big.plr.dir_y = 1; big.plr.dir_x = 0;
	big.mlx.plane_y = 0; big.mlx.plane_x = 0.66;
	big.mlx.time = 0; big.mlx.old_time = 0;
	while (1)
	{
		while (x < res->width)
		{
			big.mlx.camera_x = 2 * x / (double)res->width - 1;
			big.mlx.raydir_y = big.plr.dir_y + big.mlx.plane_y * big.mlx.camera_x;
			big.mlx.raydir_x = big.plr.dir_x + big.mlx.plane_x * big.mlx.camera_x;
			big.mlx.map_y = (int)big.plr.pos_y;
			big.mlx.map_x = (int)big.plr.pos_x;
			big.mlx.deltadst_y = (big.mlx.raydir_x == 0) ? 0 : ((big.mlx.raydir_y) == 0) ? 1 : fabs(1 / big.mlx.raydir_y);
			big.mlx.deltadst_x = (big.mlx.raydir_y == 0) ? 0 : ((big.mlx.raydir_x) == 0) ? 1 : fabs(1 / big.mlx.raydir_x);
			if (big.mlx.raydir_y < 0)
			{
				big.mlx.step_y = -1;
				big.mlx.sidedst_y = (big.plr.pos_y - (double)big.mlx.map_y) * big.mlx.deltadst_y;
			}
			else
			{
				big.mlx.step_y = 1;
				big.mlx.sidedst_y = ((double)big.mlx.map_y + 1.0 - big.plr.pos_y) * big.mlx.deltadst_y;
			}
			if (big.mlx.raydir_x < 0)
			{
				big.mlx.step_x = -1;
				big.mlx.sidedst_x = (big.plr.pos_x - (double)big.mlx.map_x) * big.mlx.deltadst_x;
			}
			else
			{
				big.mlx.step_x = 1;
				big.mlx.sidedst_x = ((double)big.mlx.map_x + 1.0 - big.plr.pos_x) * big.mlx.deltadst_x;
			}
			// printf("%f\n", big.mlx.sidedst_x);
			big.mlx.hit = 0;
			while (big.mlx.hit == 0)
			{
				if (big.mlx.sidedst_y < big.mlx.sidedst_x)
				{
					big.mlx.sidedst_y += big.mlx.deltadst_y;
					big.mlx.map_y += big.mlx.step_y;
					big.mlx.side = 0;
				}
				else
				{
					big.mlx.sidedst_x += big.mlx.deltadst_x;
					big.mlx.map_x += big.mlx.step_x;
					big.mlx.side = 1;
				}
				if (map->map[big.mlx.map_y][big.mlx.map_x] == '1')
					big.mlx.hit = 1;
			}
			if (big.mlx.side == 0)
				big.mlx.perp_wall_dist = ((double)big.mlx.map_y - big.plr.pos_y + (1.0 - big.mlx.step_y) / 2) / big.mlx.raydir_y;
			else
				big.mlx.perp_wall_dist = ((double)big.mlx.map_x - big.plr.pos_x + (1.0 - big.mlx.step_x) / 2) / big.mlx.raydir_x;
			big.mlx.line_h = (int)(res->height / big.mlx.perp_wall_dist);
			big.mlx.draw_start = -big.mlx.line_h / 2 + res->height / 2;
			if (big.mlx.draw_start < 0)
				big.mlx.draw_start = 0;
			big.mlx.draw_end = big.mlx.line_h / 2 + res->height / 2;
			if (big.mlx.draw_end >= res->height)
				big.mlx.draw_end = res->height - 1;
			big.mlx.color = (big.mlx.side == 1) ? 0xFFAAAA : 0xAAFFFF; //NS blue WE pink
			// printf("%c\n", map->map[(int)big.plr.pos_y][(int)big.plr.pos_x]);
			// printf("x = %d start = %d end = %d color %d\n", x, big.mlx.draw_start, big.mlx.draw_end, big.mlx.color);
			draw_vert_line(x, &big.mlx);
			x++;
		}
		big.mlx.frame_time = 0.016;
		mlx_string_put(big.mlx.mlx_ptr, big.mlx.win_ptr, res->width - 30, 20, 0xFFFFFF, ft_itoa(1 / big.mlx.frame_time));
		// mlx_hook(big.mlx.mlx_ptr, 2, 0, deal_key, &big);
		
		// big.plr.move_speed = big.mlx.frame_time
		mlx_loop(big.mlx.mlx_ptr);
	}
	return (OK);
}
