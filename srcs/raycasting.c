/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 15:10:31 by eassouli          #+#    #+#             */
/*   Updated: 2020/10/06 16:19:19 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "raycast.h"

void	px_vline(t_a *a)
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
/*
	while (a->img.px_start <= a->img.px_end)
	{
		pos = (a->img.px_start * a->img.size_l + a->mlx.x * (a->img.bpp / 8));
		*(unsigned int *)(a->img.img + pos) = c;
		a->img.px_start++;
	}
	*/
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

int		destroy(t_a *a)
{
	system("kill -9 $(pidof aplay)");
	mlx_destroy_window(a->mlx.ptr, a->mlx.win);
	free_map(a->map.map);
	exit(OK); // Ne pas juste exit mais return error
}

int		rc_loop(t_a *a)
{
	key_move(a);
	a->mlx.x = 0;
	while (a->mlx.x < a->res.w)
	{
		rc_dir(a);
		rc_dst(a);
		rc_hit(a);
		rc_line(a);
		px_vline(a);
		a->mlx.x++;
	}
	mlx_put_image_to_window(a->mlx.ptr, a->mlx.win, a->img.img_ptr, 0, 0);
	return (OK);
}

int		image_loader(t_a *a)
{
	if (tx_set(a) == ERR)
		return(ERR);
	a->mlx.win = mlx_new_window(a->mlx.ptr, a->res.w, a->res.h, "cub3D");
	a->img.img_ptr = mlx_new_image(a->mlx.ptr, a->res.w, a->res.h);
	a->img.img = mlx_get_data_addr(a->img.img_ptr, &a->img.bpp, &a->img.size_l, &a->img.endian);
	return (OK);
}

int		raycast(t_a *a)
{
	image_loader(a);
	mlx_hook(a->mlx.win, 2, (1L<<0), key_press, a);
	mlx_hook(a->mlx.win, 3, (1L<<1), key_release, a);
	mlx_hook(a->mlx.win, 17, (1L<<5), destroy, a); // voir macro (peut etre)
	mlx_hook(a->mlx.win, STRUCTURE_NOTIFY_CODE, STRUCTURE_NOTIFY_MASK, destroy, a);
	mlx_loop_hook(a->mlx.ptr, rc_loop, a);
	mlx_loop(a->mlx.ptr);
	return (OK);
}
