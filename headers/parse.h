/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 17:14:35 by eassouli          #+#    #+#             */
/*   Updated: 2020/09/25 15:08:12 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
#define PARSE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "../srcs/libft/libft.h"
#include "../srcs/get_next_line/get_next_line.h"

# define CUB ".cub"

# define OK 1
# define FALSE 0
# define ERR -1
# define MISSING_CUB_FILE -2
# define NOT_CUB_FILE -3
# define MLX_INIT_FAIL -4
# define MAP_NOT_CLOSED -5
# define MUSIC_FILE_FAIL -6


# define NOT_VALID_ARG -10


typedef struct	s_res
{
	int		w;
	int		h;
}				t_res;

typedef struct	s_txr
{
	char	*n;
	char	*s;
	char	*w;
	char	*e;
	char	*spt;
	char	*f;
	char	*c;
	int		f_rgb;
	int		c_rgb;
}				t_txr;

typedef struct	s_map
{
	char	**map;
	int		y;
	int		x;
	int		hit;
	int		side;
}				t_map;

#include "raycast.h"

int		init(t_a *a);

int		res_parse(char *line, t_res *res, t_mlx *mlx);
int		parse(int fd, t_a *a);

int		dup_check(char c);
void	txr_cpy(char c, char *line, int len, t_txr *txr);
int		txr_malloc(char c, int len, t_txr *txr);
int		txr_parse(char c, char *line, t_txr *txr);

int		txr_atoi(char c, char *line, t_txr *txr);

int		add_line(char *line, t_list	**first, t_list	**lst);
int		start_p(int y, char *line, t_plr *plr, t_dir *dir);
int		map_parse(int fd, char *line, t_map *map, t_plr *plr, t_dir *dir);
int		floodfill_map(char *line, int i, char trg, char rep);

int		raycast(t_a *a);

int		play_music(const char *music_name);

#endif