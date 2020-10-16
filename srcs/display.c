/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 16:57:15 by eassouli          #+#    #+#             */
/*   Updated: 2020/10/16 17:03:48 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "raycast.h"

// Create 2 other functions, ceiling, walls and floor

void	draw_lines(t_a *a)
{
	int		c;
	int		y;
	int		pos;
	t_atx	tx;

	y = 0;
	tx = a->tex.tx;
	while (y < a->img.px_start)
	{
		pos = (y * a->img.size_l + a->mlx.x * (a->img.bpp / 8));
		*(unsigned int *)(a->img.img + pos) = a->txr.c_rgb;
		y++;
	}
	while (a->img.px_start <= a->img.px_end)
	{
		pos = (a->img.px_start * a->img.size_l + a->mlx.x * (a->img.bpp / 8));
		a->tex.y = (int)a->tex.pos & (a->tex.dim - 1);
		c = tx.img[a->tex.y * (tx.size_l / 4) + a->tex.x];
		*(unsigned int *)(a->img.img + pos) = c;
		a->tex.pos += a->tex.step;
		a->img.px_start++;
	}
	y = a->img.px_start;
	while (y < a->res.h)
	{
		pos = (y * a->img.size_l + a->mlx.x * (a->img.bpp / 8));
		*(unsigned int *)(a->img.img + pos) = a->txr.f_rgb;
		y++;
	}
}