/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 16:22:44 by eassouli          #+#    #+#             */
/*   Updated: 2020/04/22 17:47:44 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

#include "parse.h"
#include "minilibx_mms/mlx.h"
#include <math.h>
#include <time.h>

# define W 13
# define A 0
# define S 1
# define D 2
# define LR 123
# define RR 124

void	raycast_dir(t_big *big);
void	raycast_dst(t_big *big);
void	raycast_hit(t_big *big);
void	raycast_line(t_big *big);

int		deal_key(int key, void *param);
void	draw_vert_line(int x, t_mlx *mlx, t_res *res);
int		raycast(t_big *big);

# endif