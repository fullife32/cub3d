/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/31 16:17:39 by eassouli          #+#    #+#             */
/*   Updated: 2021/01/13 17:35:26 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_a		a;

	init(&a); //check if all functions are statics or indexed in header
	if (ac < 2)
		error(NOT_ENOUGH_ARGS, &a);
	else if (ac > 3)
		error(TOO_MANY_ARGS, &a);
	cub_check(av[1], &a);
	parse(&a); //do all test
	if (ac == 3)
		save_check(av[2], &a);
	image_loader(&a); //recompiler si header change
	if (a.bmp.fd == 0)
		play_music(&a);
	else
		rc_loop(&a);
	mlx_hook(a.mlx.win, 2, (1L << 0), key_press, &a);
	mlx_hook(a.mlx.win, 3, (1L << 1), key_release, &a);
	mlx_hook(a.mlx.win, 33, (5L << 0), destroy, &a);
	mlx_loop_hook(a.mlx.ptr, rc_loop, &a);
	mlx_loop(a.mlx.ptr);
	return (OK);
}
