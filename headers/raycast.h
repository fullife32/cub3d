/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 16:22:44 by eassouli          #+#    #+#             */
/*   Updated: 2020/05/26 18:55:53 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

#include "parse.h"
#include "../minilibx_mac/mlx.h"
#include <math.h>

void	rc_dir(t_a *a);
void	rc_dst(t_a *a);
void	rc_hit(t_a *a);
void	rc_line(t_a *a);

int		key_press(int key, t_a *a);
int		key_release(int key, t_a *a);
int		key_move(t_a *a);

void	px_vline(t_a *a);
int		rc_loop(t_a *a);
int		raycast(t_a *a);

# endif