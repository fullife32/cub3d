/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 15:10:31 by eassouli          #+#    #+#             */
/*   Updated: 2020/10/16 17:03:06 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "raycast.h"

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
		draw_lines(a);
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
