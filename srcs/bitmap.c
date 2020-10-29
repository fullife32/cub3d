/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 14:19:36 by eassouli          #+#    #+#             */
/*   Updated: 2020/10/29 14:26:34 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "raycast.h"

/*
** Créer une structure pour enregistrer l'image em .bmp & prendre en compte
** --save a la fin dans le parsing
**
** Ici, nous allons créer un DIB (device-dependant bitmap), car facile à
** utiliser et est lisible par la plupart des visualiseurs/éditeurs d'images.
** Pour ce faire, on va éditer les caractéristiques de son header dans la
** partie dib de la structure.
**
** - la taille de son header (sur 4 octets) est de 28 en hexadécimal -> 40 en
** décimal
** - les résolutions sont les mêmes que pour l'image
** - le nombre de plans (sur 2 octets) est toujours à 1
** - le bpp est en 32 bits
*/

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
** donner les indications d'initialisation de la structure a enregistrer pour
** le .bmp
*/

int		rec_bmp_h(t_a *a)
{
	if ((a->bmp.fd = open("save.bmp", O_RDWR | O_CREAT, S_IRWXU | O_TRUNC)) < 0)
		return (BMP_FAIL);
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
	return (OK);
}

int		rec_px(t_a *a)
{
	int	i;
	int	j;
	int	pos;

	j = 0;
	while (j < a->res.h)
	{
		i = a->res.w;
		pos = a->res.w * (a->res.h - j);
		while (i-- > 0)
		{
			write(a->bmp.fd, &a->img.img[4 * pos], 4);
			pos++;
		}
		j++;
	}
	return (OK);
}

// int	rec_bmp(t_a a)
// {
// 	raycast(&a);
// 	rec_bmp_h(&a);
// 	rec_px(&a);
// 	close(a.bmp.fd);
// 	destroy(&a);
// 	return (OK);
// }
