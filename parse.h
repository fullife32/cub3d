/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 17:14:35 by eassouli          #+#    #+#             */
/*   Updated: 2020/05/03 03:25:30 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
#define PARSE_H

#include "get_next_line/get_next_line.h"
#include "libft/libft.h"
#include <stdio.h>

#define ERR -1
#define FALSE 0
#define OK 1

typedef struct	s_res
{
	int		width;
	int		height;
}				t_res;

typedef struct	s_txr
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	*sprite;
}				t_txr;

typedef struct	s_clr
{
	int		f_r;
	int		f_g;
	int		f_b;
	int		c_r;
	int		c_g;
	int		c_b;
	char	*floor;
	char	*ceiling;
}				t_clr;

typedef struct	s_map
{
	char	**map;
	int		map_y;
	int		map_x;
	int		hit;
	int		side;
}				t_map;

typedef struct	s_mlx
{
	void	*mlx;
	void	*win;
	double	time;
	int		x;
	double	frame_time;
}				t_mlx;

typedef struct	s_plr
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	olddir_y;
	double	move_spd;
	double	rot_spd;
}				t_plr;

typedef struct	s_dir
{
	double	plane_y;
	double	oldplane_y;
	double	plane_x;
	double	camera_y;
	double	camera_x;
	double	raydir_y;
	double	raydir_x;
}				t_dir;

typedef struct	s_dst
{
	double	sidedst_y;
	double	sidedst_x;
	double	deltadst_y;
	double	deltadst_x;
	double	wall_dst;
	int		step_y;
	int		step_x;
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
	char	mov[65536];
}				t_mov;

typedef struct	s_all
{
	t_res	res;
	t_txr	txr;
	t_clr	clr;
	t_map	map;
	t_mlx	mlx;
	t_plr	plr;
	t_dir	dir;
	t_dst	dst;
	t_img	img;
	t_mov	mov;
}				t_all;

void	init(t_res *res, t_txr *txr, t_clr *clr, t_map *map);

void	txr_cpy(char c, char *line, int len, t_txr *txr);
int		txr_malloc(char c, int len, t_txr *txr);
int		txr_parse(char c, char *line, t_txr *txr);

int		res_parse(char *line, t_res *res);
int		add_line(char *line, t_list	**first, t_list	**lst);
int		map_parse(int fd, char *line, t_map *map, t_plr *plr);
int		parse(int fd, t_res *res, t_txr *txr, t_clr *clr, t_map *map, t_plr *plr);

void	clr_rgb(char c, int *rgb, t_clr *clr);
int		clr_atoi(char c, char *line, t_clr *clr);
int		clr_malloc(char c, int len, t_clr *clr);
int		clr_parse(char c, char *line, t_clr *clr);

int		raycast(t_all *all);

#endif