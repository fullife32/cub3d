/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 16:22:44 by eassouli          #+#    #+#             */
/*   Updated: 2020/04/25 20:05:15 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

#include "parse.h"
#include "minilibx_mms/mlx.h"
#include <math.h>
#include <time.h>

# define FW 13
# define BW 1
# define L 0
# define R 2
# define LR 123
# define RR 124

void	raycast_dir(t_all *all);
void	raycast_dst(t_all *all);
void	raycast_hit(t_all *all);
void	raycast_line(t_all *all);

int		movement(t_all *all);
int		deal_key(t_all *all);
void	draw_vert_line(int x, t_mlx *mlx, t_res *res);
int		raycast(t_all *all);

# endif