/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 16:22:44 by eassouli          #+#    #+#             */
/*   Updated: 2020/04/13 19:02:25 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

#include "parse.h"
#include "minilibx_mms/mlx.h"
#include <math.h>
#include <time.h>

typedef struct	s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	double	plane_x;
	double	plane_y;
	double	time;
	double	old_time;
	double	camera_x;
	double	camera_y;
	double	raydir_x;
	double	raydir_y;
	int		map_x;
	int		map_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadst_x;
	double	deltadst_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_h;
	int		draw_start;
	int		draw_end;
	int		color;
}				t_mlx;

typedef struct	s_plr
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
}				t_plr;

void	raycast_init(t_mlx *mlx, t_plr *plr);
int		raycast_create(t_res *res, t_map *map);

# endif