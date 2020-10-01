/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 16:22:44 by eassouli          #+#    #+#             */
/*   Updated: 2020/10/01 15:00:45 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

#include <math.h>
#include "../minilibx_linux/mlx.h"

# define ESC 65307
# define FW 119
# define BW 115
# define L 97
# define R 100
# define LR 65361
# define RR 65363

# define MOTION_NOTIFY_MASK  (1L << 13),
# define STRUCTURE_NOTIFY_MASK  (1L << 17)

# define MOTION_NOTIFY_CODE 06
# define STRUCTURE_NOTIFY_CODE 17

typedef struct	s_mlx
{
	void	*ptr;
	void	*win;
	int		x;
}				t_mlx;

typedef struct	s_plr
{
	double	pos_x;
	double	pos_y;
	double	move_spd;
	double	rot_spd;
}				t_plr;

typedef struct	s_dir
{
	double	x;
	double	y;
	double	old_x;
	double	plane_x;
	double	plane_y;
	double	oldplane_x;
	double	cam_x;
	double	cam_y;
	double	ray_x;
	double	ray_y;
}				t_dir;

typedef struct	s_dst
{
	double	side_x;
	double	side_y;
	double	delta_x;
	double	delta_y;
	double	wall;
	int		step_x;
	int		step_y;
}				t_dst;

typedef struct	s_img
{
	int		line_h;
	int		px_start;
	int		px_end;
	int		color;
	void	*img_ptr;
	int		bpp;
	int		size_l;
	int		endian;
	char	*img;
}				t_img;

typedef struct	s_mov
{
	char	mov[70000];
}				t_mov;

typedef struct	s_atx
{
	void	*ptr;
	int		bpp;
	int		size_l;
	int		endian;
	int		*img;
}				t_atx;

typedef struct	s_test
{
	int		texdim;
	t_atx	tx;
	double	wallX;
	int		tex;
	int		texX;
	int		texY;
	double	step;
	double	texPos;
}				t_test;

typedef struct	s_a
{
	t_res	res;
	t_txr	txr;
	t_map	map;
	t_mlx	mlx;
	t_plr	plr;
	t_dir	dir;
	t_dst	dst;
	t_img	img;
	t_mov	mov;
	t_atx	ntx;
	t_atx	stx;
	t_atx	wtx;
	t_atx	etx;
	t_test	test;
}				t_a;

void	rc_dir(t_a *a);
void	rc_dst(t_a *a);
void	rc_hit(t_a *a);
void	rc_line(t_a *a);
t_atx	wall_set(t_a *a);
void	free_map(char **map);

int		key_press(int key, t_a *a);
int		key_release(int key, t_a *a);
int		key_move(t_a *a);

void	px_vline(t_a *a);
int		tx_set(t_a *a);
int		destroy(t_a *a);
int		rc_loop(t_a *a);
int		raycast(t_a *a);

# endif