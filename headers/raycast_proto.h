/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_proto.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 15:18:39 by eassouli          #+#    #+#             */
/*   Updated: 2020/12/19 19:06:57 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_PROTO_H
# define RAYCAST_PROTO_H

void	dir_init(t_a *a);
void	mov_init(t_a *a);

void	rc_dir(t_a *a);
void	rc_dst(t_a *a);
void	rc_hit(t_a *a);
void	rc_line(t_a *a);
void	rc_wal(t_a *a);

t_atx	wall_select(t_a *a);
void	wall_set(t_a *a);

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
void	wall_free(t_a *a);
void	sprite_free(t_a *a);

void	wall_init(t_a *a);
void	sprite_init(t_a *a);

#endif