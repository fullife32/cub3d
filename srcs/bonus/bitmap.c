/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 14:19:36 by eassouli          #+#    #+#             */
/*   Updated: 2021/01/13 15:48:17 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Create a structure for the .bmp file created when --save is used in the 3rd
** argument of the program.
**
** In that case, we make a DIB (device-dependant bitmap) file, because it is
** easier to use and is readeable by most of the image editors/visualizers.
** First, we will edit its header's components in the dib part of the structure.
**
** - header's size (4 bytes) is 28 en hexadecimal -> 40 in decimal
** - resolution of the header is the same than for the image
** - the number of color planes (2 bytes) is always 1
** - the bpp is in 32 bits
*/

void	hub_bmp(t_a *a)
{
	init_bmp(a);
	rec_bmp_h(a);
	rec_px(a);
	close(a->bmp.fd);
	destroy(a);
}

void	init_bmp(t_a *a)
{
	a->bmp.fd = 0;
	a->bmp.sign = 19778;
	a->bmp.size = 54 + 3 * a->res.w * a->res.h;
	a->bmp.rsv = 0;
	a->bmp.offset = 54;
	a->bmp.dib_size_h = 40;
	a->bmp.dib_height = a->res.h;
	a->bmp.dib_width = a->res.w;
	a->bmp.dib_clr_pln = 1;
	a->bmp.dib_bpp = 32;
}

/*
** record the initialization of the .bmp structure's file
*/

void	rec_bmp_h(t_a *a)
{
	a->bmp.fd = open("save.bmp", O_RDWR | O_CREAT, S_IRWXU | O_TRUNC);
	if (a->bmp.fd < 0)
		error(BMP_FAIL, a);
	write(a->bmp.fd, &a->bmp.sign, 2);
	write(a->bmp.fd, &a->bmp.size, 4);
	write(a->bmp.fd, &a->bmp.rsv, 4);
	write(a->bmp.fd, &a->bmp.offset, 4);
	write(a->bmp.fd, &a->bmp.dib_size_h, 4);
	write(a->bmp.fd, &a->bmp.dib_width, 4);
	write(a->bmp.fd, &a->bmp.dib_height, 4);
	write(a->bmp.fd, &a->bmp.dib_clr_pln, 2);
	write(a->bmp.fd, &a->bmp.dib_bpp, 2);
	write(a->bmp.fd, &a->bmp.rsv, 4);
	write(a->bmp.fd, &a->bmp.rsv, 4);
	write(a->bmp.fd, &a->bmp.rsv, 4);
	write(a->bmp.fd, &a->bmp.rsv, 4);
	write(a->bmp.fd, &a->bmp.rsv, 4);
	write(a->bmp.fd, &a->bmp.rsv, 4);
}

void	rec_px(t_a *a)
{
	int	j;
	int	pos;

	j = 1;
	while (j <= a->res.h)
	{
		pos = a->res.w * (a->res.h - j);
		write(a->bmp.fd, &a->img.img[4 * pos], 4 * a->res.w);
		j++;
	}
}
