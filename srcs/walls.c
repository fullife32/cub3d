/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 15:28:48 by eassouli          #+#    #+#             */
/*   Updated: 2020/09/25 15:31:17 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "raycast.h"

void	wall_set(t_a *a)
{	
	if (a->map.side == 1 && a->dst.step_y == 1)
		a->img.color = 0xFF0000; //NORD ROUGE
	else if (a->map.side == 1 && a->dst.step_y == -1)
		a->img.color = 0x0000FF; //SUD BLEU
	else if (a->map.side == 0 && a->dst.step_x == -1)
		a->img.color = 0x00FF00; //EST VERT
	else if (a->map.side == 0 && a->dst.step_x == 1)
		a->img.color = 0xFFFFFF; //OUEST BLANC
}

int		tx_set(t_a *a)
{
	a->ntx.ptr = mlx_xpm_file_to_image(a->mlx.ptr, a->txr.n, &a->img.px_start, &a->img.px_end);
	a->stx.ptr = mlx_xpm_file_to_image(a->mlx.ptr, a->txr.s, &a->img.px_start, &a->img.px_end);
	a->etx.ptr = mlx_xpm_file_to_image(a->mlx.ptr, a->txr.e, &a->img.px_start, &a->img.px_end);
	a->wtx.ptr = mlx_xpm_file_to_image(a->mlx.ptr, a->txr.w, &a->img.px_start, &a->img.px_end);
	if (a->ntx.ptr == 0 || a->stx.ptr == 0 || a->etx.ptr == 0 || a->wtx.ptr == 0)
		return (ERR);
	a->ntx.img = mlx_get_data_addr(a->ntx.ptr, &a->ntx.bpp, &a->ntx.size_l, &a->ntx.endian);
	a->stx.img = mlx_get_data_addr(a->stx.ptr, &a->stx.bpp, &a->stx.size_l, &a->stx.endian);
	a->etx.img = mlx_get_data_addr(a->etx.ptr, &a->etx.bpp, &a->wtx.size_l, &a->etx.endian);
	a->wtx.img = mlx_get_data_addr(a->wtx.ptr, &a->wtx.bpp, &a->etx.size_l, &a->wtx.endian);
	if (a->ntx.img == 0 || a->stx.img == 0 || a->etx.img == 0 || a->wtx.img == 0)
		return (ERR);
	return (OK);
}
