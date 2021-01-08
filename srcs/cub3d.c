/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/31 16:17:39 by eassouli          #+#    #+#             */
/*   Updated: 2021/01/08 17:14:37 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_a		a;

	init(&a); //check if all functions are statics or indexed in header
	if (ac < 2) //ajouter musique
		error(NOT_ENOUGH_ARGS, &a); //peut etre changer nom map_hub dans parse
	else if (ac > 3) //peut etre changer nom texture choice dans texture_parse
		error(TOO_MANY_ARGS, &a); //diminuer vitesse
	cub_check(av[1], &a); //rassembler fonctions init
	parse(&a); //do all test
	if (ac == 3) //check leaks
		save_check(av[2], &a);
	image_loader(&a);
	if (a.bmp.fd == 0)
		play_music(&a);
	else
		rc_loop(&a);
	// Display infos
	// Display infos
	mlx_hook(a.mlx.win, 2, (1L << 0), key_press, &a);
	mlx_hook(a.mlx.win, 3, (1L << 1), key_release, &a);
	mlx_hook(a.mlx.win, 33, (1L << 0), destroy, &a); //repair it
	mlx_loop_hook(a.mlx.ptr, rc_loop, &a);
	mlx_loop(a.mlx.ptr);
	return (OK);
}

// Display infos
	// printf("\nRES :\nwidth = %d\nheight = %d\n", a.res.w, a.res.h);
	// printf("\nTXR :\nnorth = %s\nsouth = %s\nwest = %s\neast = %s\nsprite = %s\n", a.txr.north, a.txr.south, a.txr.west, a.txr.east, a.txr.sprite);
	// printf("\nCLR :\nfloor :\nr = %d, g = %d, b = %d\nfloor = %s\nceilng :\nr = %d, g = %d, b = %d\nceiling = %s\n", a.txr.f_rgb / 256 / 256 % 256, a.txr.f_rgb / 256 % 256, a.txr.f_rgb % 256, a.txr.floor, a.txr.c_rgb / 256 / 256 % 256, a.txr.c_rgb / 256 % 256, a.txr.c_rgb % 256, a.txr.ceiling);
	// printf("\nMAP :\n|         10        20        30        40        50|");
	// printf("\n|012345678901234567890123456789012345678901234567890|\n");
	// for (int i = 0; a.map.map[i] != NULL; i++)
	// 	printf("|%s| %d\n", a.map.map[i], i);
	// Display infos
