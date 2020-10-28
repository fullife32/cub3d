/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 16:57:15 by eassouli          #+#    #+#             */
/*   Updated: 2020/10/28 16:18:25 by eassouli         ###   ########.fr       */
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

void	draw_sprite(t_a *a)
{
	int				stripe;
	int				y;
	int				pos;
	int				d;
	unsigned int	color;

	stripe = a->spr.drawStartX;
	while (stripe < a->spr.drawEndX)
	{
		a->tex.x = (int)(256 * (stripe - (-a->spr.spriteWidth / 2
		+ a->spr.spriteScreenX)) * a->tex.dim / a->spr.spriteWidth) / 256;
		if (a->spr.transformY > 0 && stripe > 0 && stripe < a->res.w
		&& a->spr.transformY < a->spr.z_buff[stripe])
		{
			y = a->spr.drawStartY;
			while (y < a->spr.drawEndY)
			{
				pos = (y * a->img.size_l + stripe * (a->img.bpp / 8));
				d = y * 256 - a->res.h * 128 + a->spr.spriteHeight * 128;
				a->tex.y = ((d * a->tex.dim) / a->spr.spriteHeight) / 256;
				color = a->spr_txr.img[a->tex.y * (a->spr_txr.size_l / 4) + a->tex.x];
				if ((color & 0xFFFFFF) != 0)
					*(unsigned int *)(a->img.img + pos) = color;
				y++;
			}
		}
		stripe++;
	}
}
