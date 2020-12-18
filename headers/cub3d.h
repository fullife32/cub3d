/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 14:53:55 by eassouli          #+#    #+#             */
/*   Updated: 2020/12/18 15:32:28 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D
# define CUB3D

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include "../srcs/libft/libft.h"
#include "../srcs/get_next_line/get_next_line.h"

# define OK 1
# define FALSE 0
# define ERR -1

# define MAX_ERROR 200

# define NOT_ENOUGH_ARGS 0
# define TOO_MANY_ARGS 1

# define MISS_CUB_FILE 2
# define NOT_CUB_FILE 3
# define SAVE_FAIL 4

# define MLX_INIT_FAIL 5
# define MALLOC_FAIL_LINE 6

# define NOT_ENOUGH_ID 7
# define NOT_VALID_ID 8

# define TOO_MANY_RES 9
# define NOT_VALID_RES 10

# define NOT_VALID_TXR 11
# define TOO_MANY_TXR 12
# define NOT_VALID_COLOR 13
# define MALLOC_FAIL_TXR 14

# define MALLOC_FAIL_MAP 15
# define TOO_MANY_START 16
# define NOT_VALID_CHAR_MAP 17
# define NO_START 18

# define MALLOC_FAIL_FILL 19
# define MAP_NOT_CLOSE 20

# define MALLOC_FAIL_SPR 21

# define BMP_FAIL 102

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

#include "parse.h"
#include "raycast.h"
#include "stack.h"

#endif
