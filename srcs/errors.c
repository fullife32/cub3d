/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 18:19:43 by eassouli          #+#    #+#             */
/*   Updated: 2020/11/13 15:16:58 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "raycast.h"
#include "stack.h"

int		destroy(t_a *a)
{
	system("kill -9 $(pidof aplay) > /dev/null");
	mlx_destroy_window(a->mlx.ptr, a->mlx.win);
	free_map(a->map.map);
	exit(OK); // Ne pas juste exit mais return error
}

int	fp(t_txr *txr)
{
	if (txr->north)
		free(txr->north);
	if (txr->south)
		free(txr->south);
	if (txr->west)
		free(txr->west);
	if (txr->east)
		free(txr->east);
	if (txr->sprite)
		free(txr->sprite);
	if (txr->floor)
		free(txr->floor);
	if (txr->ceiling)
		free(txr->ceiling);
	return (ERR);
}

void	error(int error, t_a *a)
{
	if (error != ERR)
		write(1, "Error\n", 7);
	if (error == MISSING_CUB_FILE)
		write(1, ".cub file not found\n", 21);
	else if (error == NOT_CUB_FILE)
		write(1, "The last argument must be a .cub file\n", 38);
	else if (error == MLX_INIT_FAIL)
		write(1, "Initialization of MLX server failed\n", 37);
	else if (error == MUSIC_FILE_FAIL)
		write(1, "Music file name/path is incorrect\n", 35);
	if (error == ERR)
		fp(fd, &a->txr);
	if (error == OK)
		exit(0);
	exit(-1);
}
