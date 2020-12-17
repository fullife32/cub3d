/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 11:30:07 by eassouli          #+#    #+#             */
/*   Updated: 2020/12/17 17:18:33 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "raycast.h"

void	spr_init(t_a *a)
{
	a->spr_txr.ptr = 0;
	a->spr.pos_x = 0;
	a->spr.pos_y = 0;
	a->spr.z_buff = 0;
	a->spr.dist = 0;
	a->spr.order = 0;
}

void	sprite_init(t_a *a)
{
	a->spr_txr.ptr = mlx_xpm_file_to_image(a->mlx.ptr, a->txr.sprite,
	&a->tex.dim, &a->tex.dim);
	if (a->spr_txr.ptr == 0)
		error(-1, a);
	a->spr_txr.img = (int *)mlx_get_data_addr(a->spr_txr.ptr,
	&a->spr_txr.bpp, &a->spr_txr.size_l, &a->spr_txr.endian);
	if (a->spr_txr.img == 0)
		error(-1, a);
	if ((a->spr.z_buff = malloc(sizeof(double) * (a->res.w + 1))) == NULL)
		error(-1, a);
	if ((a->spr.dist = malloc(sizeof(double) * (a->spr.amount + 1))) == NULL)
		error(-1, a);
	a->spr.dist[a->spr.amount] = '\0';
	if ((a->spr.order = malloc(sizeof(int) * a->spr.amount + 1)) == NULL)
		error(-1, a);
	a->spr.order[a->spr.amount] = '\0';
}

void	sprite_count(t_a *a)
{
	int	y;
	int	x;

	y = 0;
	a->spr.amount = 0;
	while (a->map.map[y])
	{
		x = 0;
		while (a->map.map[y][x])
		{
			if (a->map.map[y][x] == '2')
				a->spr.amount++;
			x++;
		}
		y++;
	}
}

void	sprite_pos(t_a *a)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	y = 0;
	while (a->map.map[y])
	{
		x = 0;
		while (a->map.map[y][x])
		{
			if (a->map.map[y][x] == '2')
			{
				a->spr.pos_x[i] = x + 0.5;
				a->spr.pos_y[i] = y + 0.5;
				i++;
			}
			x++;
		}
		y++;
	}
	a->spr.pos_x[i] = '\0';
	a->spr.pos_y[i] = '\0';
}

void	sprite_list(t_a *a)
{
	sprite_count(a);
	if ((a->spr.pos_x = malloc(sizeof(double) * (a->spr.amount + 1))) == NULL)
		error(MALLOC_FAIL_SPR, a);
	if ((a->spr.pos_y = malloc(sizeof(double) * (a->spr.amount + 1))) == NULL)
		error(MALLOC_FAIL_SPR, a);
	sprite_pos(a);
}
