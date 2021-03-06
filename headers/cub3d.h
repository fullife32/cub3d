/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 14:53:55 by eassouli          #+#    #+#             */
/*   Updated: 2021/01/13 17:56:45 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <math.h>
# include "get_next_line.h"
# include "libft.h"
# include "mlx.h"
# include "parse.h"
# include "raycast.h"
# include "stack.h"

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
# define NOT_VALID_RES_NB 29
# define NOT_VALID_RES_W 10
# define NOT_VALID_RES_H 30

# define NOT_VALID_TXR 11
# define TOO_MANY_TXR 12
# define NOT_VALID_COLOR 13
# define MALLOC_FAIL_TXR 14
# define NOT_VALID_TXR_CHAR 31

# define MALLOC_FAIL_MAP 15
# define TOO_MANY_START 16
# define NOT_VALID_CHAR_MAP 17
# define NO_START 18
# define MAP_END_OF_FILE 24

# define MALLOC_FAIL_FILL 19
# define MAP_NOT_CLOSE 20

# define MALLOC_FAIL_SPR 21

# define MALLOC_FAIL_NO 25
# define MALLOC_FAIL_SO 26
# define MALLOC_FAIL_EA 27
# define MALLOC_FAIL_WE 28
# define MALLOC_FAIL_SPRITE 22

# define BMP_FAIL 23

typedef struct s_a
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
	t_vec	vec;
	t_frame	stk;
}				t_a;

/*
** destroy prototypes
*/

void			del(void *content);
void			destroy_parse(t_a *a);
int				destroy(t_a *a);
void			error(int error, t_a *a);

void			line_free(t_a *a);
void			parse_free(t_a *a);
void			map_free(char **map);

void			txr_free(t_a *a);
void			wall_free(t_a *a);
void			sprite_free(t_a *a);

/*
** parse prototypes
*/

void			map_init(t_a *a);
void			txr_init(t_a *a);
void			plr_init(t_a *a);
void			init(t_a *a);

void			cub_check(char *av, t_a *a);
void			save_check(char *av, t_a *a);

void			map_hub(t_a *a);
void			parse(t_a *a);

char			*size_check(char *line, int *res, int screen);
void			res_parse(t_a *a);

void			txr_cpy(char c, char *line, int len, t_txr *txr);
int				dup_check(char c);
void			txr_choice(char c, char *line, t_a *a);
void			txr_parse(char c, char *line, t_a *a);

void			txr_malloc(char c, int len, t_a *a);
void			txr_malloc2(char c, int len, t_a *a);

void			txr_rgb(char c, int *rgb, t_txr *txr);
int				txr_atoi(char c, char *line, t_txr *txr);

int				add_line(char *line, t_list	**first, t_list	**lst);
int				map_char(char *line);
int				empty_line(char *line);
void			map_create(t_a *a);
void			map_parse(t_a *a);

void			start_dir(t_dir *dir, char *line, int x);
int				start_p(int y, char *line, t_plr *plr, t_dir *dir);

void			sprite_count(t_a *a);
void			sprite_pos(t_a *a);
void			sprite_list(t_a *a);

/*
** floodfill prototypes
*/

void			map_dim(t_map *map);
void			map_cpy(t_a *a);
void			map_vfy_print(t_a *a);

int				free_stack(t_frame *stack, t_proj p);
int				find(char **map, t_frame **stack, t_vec proj);
int				flood_fill(char **map, t_vec pos, t_vec max, t_frame *stack);

t_frame			*stack_init(t_vec pos);
int				stack_push(t_frame **item, t_vec pos);
t_vec			stack_pop(t_frame **item);
int				stack_len(t_frame *item);

/*
** raycast prototypes
*/

void			dir_init(t_a *a);
void			mov_init(t_a *a);
void			wall_init(t_a *a);
void			sprite_init(t_a *a);

int				rc_loop(t_a *a);
int				image_loader(t_a *a);

void			wall_set2(t_a *a);
void			wall_set(t_a *a);
void			sprite_set(t_a *a);

void			rc_dir(t_a *a);
void			rc_dst(t_a *a);
void			rc_hit(t_a *a);
void			rc_line(t_a *a);
void			rc_wal(t_a *a);

t_atx			wall_select(t_a *a);

void			sprite_swap(t_spr *spr, int min, int i);
void			sprite_sort(t_spr *spr);
void			sprite_dist(t_a *a);

void			sprite_height(t_a *a);
void			sprite_width(t_a *a);
void			sprite_raycast(t_a *a);

void			draw_ceiling(t_a *a);
void			draw_walls(t_a *a);
void			draw_floor(t_a *a);
void			draw_sprite_loop(t_a *a, int stripe);
void			draw_sprite(t_a *a);

/*
** events prototypes
*/

int				key_press(int key, t_a *a);
int				key_release(int key, t_a *a);

void			key_front(t_a *a);
void			key_side(t_a *a);
void			key_rotate(t_a *a);
int				key_move(t_a *a);

/*
** bonus prototypes
*/

void			hub_bmp(t_a *a);
void			init_bmp(t_a *a);
void			rec_bmp_h(t_a *a);
void			rec_px(t_a *a);

void			play_music(t_a *a);

#endif
