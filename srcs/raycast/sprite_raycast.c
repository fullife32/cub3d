/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_raycast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 14:25:15 by eassouli          #+#    #+#             */
/*   Updated: 2021/01/08 13:22:50 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sprite_height(t_a *a)
{
	a->spr.height = abs((int)(a->res.h / a->spr.transform_y));
	a->spr.px_start_y = -a->spr.height / 2 + a->res.h / 2;
	if (a->spr.px_start_y < 0)
		a->spr.px_start_y = 0;
	a->spr.px_end_y = a->spr.height / 2 + a->res.h / 2;
	if (a->spr.px_end_y >= a->res.h)
		a->spr.px_end_y = a->res.h - 1;
}

void	sprite_width(t_a *a)
{
	a->spr.width = abs((int)(a->res.h / a->spr.transform_y));
	a->spr.px_start_x = -a->spr.width / 2 + a->spr.screen_x;
	if (a->spr.px_start_x < 0)
		a->spr.px_start_x = 0;
	a->spr.px_end_x = a->spr.width / 2 + a->spr.screen_x;
	if (a->spr.px_end_x >= a->res.w)
		a->spr.px_end_x = a->res.w - 1;
}

void	sprite_raycast(t_a *a)
{
	int	i;

	i = 0;
	sprite_dist(a);
	sprite_sort(&a->spr);
	while (i < a->spr.amount)
	{
		a->spr.spr_x = a->spr.pos_x[a->spr.order[i]] - a->plr.pos_x;
		a->spr.spr_y = a->spr.pos_y[a->spr.order[i]] - a->plr.pos_y;
		a->spr.inv_det = 1.0 / (a->dir.plane_x * a->dir.y
				- a->dir.x * a->dir.plane_y);
		a->spr.transform_x = a->spr.inv_det * (a->dir.y * a->spr.spr_x
				- a->dir.x * a->spr.spr_y);
		a->spr.transform_y = a->spr.inv_det * (-a->dir.plane_y * a->spr.spr_x
				+ a->dir.plane_x * a->spr.spr_y);
		a->spr.screen_x = (int)(a->res.w / 2 * (1 + a->spr.transform_x
					/ a->spr.transform_y));
		sprite_height(a);
		sprite_width(a);
		draw_sprite(a);
		i++;
	}
}
