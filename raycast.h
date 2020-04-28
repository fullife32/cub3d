/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 16:22:44 by eassouli          #+#    #+#             */
/*   Updated: 2020/04/28 18:25:21 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

#include "parse.h"
#include "minilibx_mms/mlx.h"
#include <math.h>

# define FW 13
# define BW 1
# define L 0
# define R 2
# define LR 123
# define RR 124
# define RUN 257

void	rc_dir(t_all *all);
void	rc_dst(t_all *all);
void	rc_hit(t_all *all);
void	rc_line(t_all *all);

int		key_press(int key, t_all *all);
int		key_unpress(int key, t_all *all);
int		key_move(t_all *all);

void	px_vline(t_all *all);
int		rc_loop(t_all *all);
int		raycast(t_all *all);

# endif