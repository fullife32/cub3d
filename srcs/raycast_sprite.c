/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_sprite.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 14:25:15 by eassouli          #+#    #+#             */
/*   Updated: 2020/10/28 15:10:47 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "raycast.h"

void	sprite_height(t_a *a)
{
	a->spr.spriteHeight = abs((int)(a->res.h / a->spr.transformY));
	a->spr.drawStartY = -a->spr.spriteHeight / 2 + a->res.h / 2;
	if (a->spr.drawStartY < 0)
		a->spr.drawStartY = 0;
	a->spr.drawEndY = a->spr.spriteHeight / 2 + a->res.h / 2;
	if (a->spr.drawEndY >= a->res.h)
	a->spr.drawEndY = a->res.h - 1;
}

void	sprite_width(t_a *a)
{
	a->spr.spriteWidth = abs((int)(a->res.h / a->spr.transformY));
	a->spr.drawStartX = -a->spr.spriteWidth / 2 + a->spr.spriteScreenX;
	if (a->spr.drawStartX < 0)
		a->spr.drawStartX = 0;
	a->spr.drawEndX = a->spr.spriteWidth / 2 + a->spr.spriteScreenX;
	if (a->spr.drawEndX >= a->res.w)
		a->spr.drawEndX = a->res.w - 1;
}

void	sprite_raycast(t_a *a)
{
	int	i;

	i = 0;
	sprite_dist(a);
	sprite_sort(&a->spr);
	while (i < a->spr.amount - 1)
	{
		a->spr.spriteX = a->spr.pos_x[a->spr.order[i]] - a->plr.pos_x;
		a->spr.spriteY = a->spr.pos_y[a->spr.order[i]] - a->plr.pos_y;
		a->spr.invDet = 1.0 / (a->dir.plane_x * a->dir.y
		- a->dir.x * a->dir.plane_y);
		a->spr.transformY = a->spr.invDet * (a->dir.y * a->spr.spriteX
		- a->dir.x * a->spr.spriteY);
		a->spr.transformX = a->spr.invDet * (-a->dir.plane_y * a->spr.spriteX
		+ a->dir.plane_x * a->spr.spriteY);
		a->spr.spriteScreenX = (int)((a->res.w / 2)
		* (1 + a->spr.transformX / a->spr.transformY));
		sprite_height(a);
		sprite_width(a);
		draw_sprite(a);
		i++;
	}
}