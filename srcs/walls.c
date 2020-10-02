/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 15:28:48 by eassouli          #+#    #+#             */
/*   Updated: 2020/10/01 15:16:25 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "raycast.h"

t_atx	wall_set(t_a *a)
{	
	if (a->map.side == 1 && a->dst.step_y == 1)
		return (a->ntx); //NORD
	else if (a->map.side == 1 && a->dst.step_y == -1)
		return (a->stx); //SUD
	else if (a->map.side == 0 && a->dst.step_x == -1)
		return (a->etx); //EST
	return (a->wtx); //OUEST
}

/*void	wall_set(t_a *a)
{	
	if (a->map.side == 1 && a->dst.step_y == 1)
		a->img.color = 0xFF0000; //NORD ROUGE
	else if (a->map.side == 1 && a->dst.step_y == -1)
		a->img.color = 0x0000FF; //SUD BLEU
	else if (a->map.side == 0 && a->dst.step_x == -1)
		a->img.color = 0x00FF00; //EST VERT
	else if (a->map.side == 0 && a->dst.step_x == 1)
		a->img.color = 0xFFFFFF; //OUEST BLANC
}*/

int		tx_set(t_a *a)
{
	a->test.texdim = 64;
	a->ntx.ptr = mlx_xpm_file_to_image(a->mlx.ptr, a->txr.n, &a->test.texdim, &a->test.texdim);
	a->stx.ptr = mlx_xpm_file_to_image(a->mlx.ptr, a->txr.s, &a->test.texdim, &a->test.texdim);
	a->etx.ptr = mlx_xpm_file_to_image(a->mlx.ptr, a->txr.e, &a->test.texdim, &a->test.texdim);
	a->wtx.ptr = mlx_xpm_file_to_image(a->mlx.ptr, a->txr.w, &a->test.texdim, &a->test.texdim);
	if (a->ntx.ptr == 0 || a->stx.ptr == 0 || a->etx.ptr == 0 || a->wtx.ptr == 0)
		return (ERR);
	a->ntx.img = (int *)mlx_get_data_addr(a->ntx.ptr, &a->ntx.bpp, &a->ntx.size_l, &a->ntx.endian);
	a->stx.img = (int *)mlx_get_data_addr(a->stx.ptr, &a->stx.bpp, &a->stx.size_l, &a->stx.endian);
	a->etx.img = (int *)mlx_get_data_addr(a->etx.ptr, &a->etx.bpp, &a->wtx.size_l, &a->etx.endian);
	a->wtx.img = (int *)mlx_get_data_addr(a->wtx.ptr, &a->wtx.bpp, &a->etx.size_l, &a->wtx.endian);
	if (a->ntx.img == 0 || a->stx.img == 0 || a->etx.img == 0 || a->wtx.img == 0)
		return (ERR);
	return (OK);
}
