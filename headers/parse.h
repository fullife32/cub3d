/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 17:14:35 by eassouli          #+#    #+#             */
/*   Updated: 2020/12/15 17:29:27 by eassouli         ###   ########.fr       */
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
# define SAVE "--save"

# define OK 1
# define FALSE 0
# define ERR -1

# define MAX_ERROR 200

# define MISS_CUB_FILE 1
# define NOT_CUB_FILE 2

# define MLX_INIT_FAIL 3

# define NOT_ENOUGH_ARGS 4
# define NOT_VALID_ARG 5

# define TOO_MANY_RES 6
# define NOT_VALID_RES 7

# define NOT_VALID_TXR 8
# define TOO_MANY_TXR 9
# define NOT_VALID_COLOR 10
# define MALLOC_FAIL_TXR 11

# define MALLOC_FAIL_MAP 12
# define TOO_MANY_START 13
# define NOT_VALID_CHAR_MAP 14
# define NO_START 15

# define MAP_NOT_CLOSED 17
# define MUSIC_FILE_FAIL 18
# define BMP_FAIL 19

typedef struct	s_res
{
	int		w;
	int		h;
}				t_res;

typedef struct	s_txr
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	*sprite;
	char	*floor;
	char	*ceiling;
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

int		fp(t_txr *txr);
void	error(int error, t_a *a);

void	init(t_a *a);

void	cub_check(char *av, t_a *a);
void	save_check(char *av, t_a *a);

void	free_line(t_a *a);
void	parse(t_a *a);

void	res_parse(t_a *a);

int		dup_check(char c);
void	txr_cpy(char c, char *line, int len, t_txr *txr);
int		txr_malloc(char c, int len, t_txr *txr);
void	txr_parse(char c, char *line, t_a *a);

int		txr_atoi(char c, char *line, t_txr *txr);

int		add_line(char *line, t_list	**first, t_list	**lst);
int		start_p(int y, char *line, t_plr *plr, t_dir *dir);
void	map_parse(t_a *a);
int		floodfill_map(char *line, int i, char trg, char rep);

int		raycast(t_a *a);

void	play_music();

int		sprite_init(t_a *a);
void	sprite_count(t_a *a);
void	sprite_pos(t_a *a);
int		sprite_list(t_a *a);

#endif