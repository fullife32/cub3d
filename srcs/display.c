/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 16:57:15 by eassouli          #+#    #+#             */
/*   Updated: 2020/10/20 14:12:04 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "raycast.h"

void	draw_ceiling(t_a *a)
{
	int		y;
	int		pos;

	y = 0;
	while (y < a->img.px_start)
	{
		pos = (y * a->img.size_l + a->mlx.x * (a->img.bpp / 8));
		*(unsigned int *)(a->img.img + pos) = a->txr.c_rgb;
		y++;
	}
}

void	draw_walls(t_a *a)
{
	int		pos;
	t_atx	tx;

	tx = a->tex.tx;
	while (a->img.px_start <= a->img.px_end)
	{
		pos = (a->img.px_start * a->img.size_l + a->mlx.x * (a->img.bpp / 8));
		a->tex.y = (int)a->tex.pos & (a->tex.dim - 1);
		*(unsigned int *)(a->img.img + pos) = tx.img[a->tex.y *
		(tx.size_l / 4) + a->tex.x];
		a->tex.pos += a->tex.step;
		a->img.px_start++;
	}
}

void	draw_floor(t_a *a)
{
	int		pos;
	
	while (a->img.px_start < a->res.h)
	{
		pos = (a->img.px_start * a->img.size_l + a->mlx.x * (a->img.bpp / 8));
		*(unsigned int *)(a->img.img + pos) = a->txr.f_rgb;
		a->img.px_start++;
	}
}
