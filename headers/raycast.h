/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 16:22:44 by eassouli          #+#    #+#             */
/*   Updated: 2020/12/17 17:19:40 by eassouli         ###   ########.fr       */
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

// # define MOTION_NOTIFY_MASK (1L << 13),
// # define STRUCTURE_NOTIFY_MASK (1L << 17)

// # define MOTION_NOTIFY_CODE 06
// # define STRUCTURE_NOTIFY_CODE 17

typedef struct	s_mlx
{
	void	*ptr;
	void	*win;
	int		x;
	int		fd;
	char	**line;
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

typedef struct	s_tex
{
	int		dim;
	t_atx	tx;
	double	wall_x;
	int		x;
	int		y;
	double	step;
	double	pos;
}				t_tex;

typedef struct	s_spr
{
	double	*pos_x;
	double	*pos_y;
	double	*z_buff;
	int		*order;
	double	*dist;
	int		amount;
	double	spr_x;
	double	spr_y;
	double	inv_det;
	double	transform_x;
	double	transform_y;
	int		screen_x;
	int		height;
	int		width;
	int		px_start_y;
	int		px_end_y;
	int		px_start_x;
	int		px_end_x;
}				t_spr;

typedef struct	s_bmp
{
	int		fd;
	int		sign;
	int		size;
	int		rsv;
	int		offset;
	int		dib_size_h;
	int		dib_height;
	int		dib_width;
	int		dib_clr_pln;
	int		dib_bpp;
}				t_bmp;

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
	t_atx	north_txr;
	t_atx	south_txr;
	t_atx	west_txr;
	t_atx	east_txr;
	t_atx	spr_txr;
	t_tex	tex;
	t_spr	spr;
	t_bmp	bmp;
}				t_a;

void	rc_dir(t_a *a);
void	rc_dst(t_a *a);
void	rc_hit(t_a *a);
void	rc_line(t_a *a);
void	rc_tex(t_a *a);

t_atx	wall_set(t_a *a);
void	tx_set(t_a *a);

void	draw_ceiling(t_a *a);
void	draw_walls(t_a *a);
void	draw_floor(t_a *a);
void	draw_sprite(t_a *a);

int		key_press(int key, t_a *a);
int		key_release(int key, t_a *a);

void	key_front(t_a *a);
void	key_side(t_a *a);
void	key_rotate(t_a *a);
int		key_move(t_a *a);

int		destroy(t_a *a);
int		rc_loop(t_a *a);
int		image_loader(t_a *a);

void	sprite_swap(t_spr *spr, int min, int i);
void	sprite_sort(t_spr *spr);
void	sprite_dist(t_a *a);

void	sprite_height(t_a *a);
void	sprite_width(t_a *a);
void	sprite_raycast(t_a *a);

void	init_bmp(t_a *a);
int		rec_bmp_h(t_a *a);
void	rec_px(t_a *a);

void	txr_free(t_a *a);
void	sprite_free(t_a *a);

# endif
