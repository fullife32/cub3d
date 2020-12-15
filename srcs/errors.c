/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 18:19:43 by eassouli          #+#    #+#             */
/*   Updated: 2020/11/24 18:46:18 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "raycast.h"
#include "stack.h"

int		destroy(t_a *a) // destroy aussi image fenetre
{
	if (a->bmp.fd == 0)
		system("kill -9 $(pidof aplay) >> /dev/null");
	if (a->mlx.win)
		mlx_destroy_window(a->mlx.ptr, a->mlx.win);
	if (a->img.img_ptr)
		mlx_destroy_image(a->mlx.ptr, a->img.img_ptr);
	free_map(a->map.map);
	exit(OK); // Ne pas juste exit mais return error
}

void	error_raycast(int error)
{
	if (error == BMP_FAIL)
		write(1, "Some issues happened when creating the .bmp file", 49);
}

void	free_parse(t_a *a)
{
	if (*a->mlx.line)
		free(*a->mlx.line);
	*a->mlx.line = NULL;
	if (a->mlx.line)
		free(a->mlx.line);
	a->mlx.line = NULL;
}

void	free_txr(t_a *a)
{
	if (a->txr.north)
		free(a->txr.north);
	if (a->txr.south)
		free(a->txr.south);
	if (a->txr.west)
		free(a->txr.west);
	if (a->txr.east)
		free(a->txr.east);
	if (a->txr.sprite)
		free(a->txr.sprite);
	if (a->txr.floor)
		free(a->txr.floor);
	if (a->txr.ceiling)
		free(a->txr.ceiling);
}

void	error_map(int error)
{
	if (error == -2)
		write(1, "\n", 21);
	else if (error == -3)
		write(1, "\n", 21);
}

void	error_txr(int error)
{
	if (error == -2)
		write(1, "Invalid texture argument\n", 25);
	else if (error == -3)
		write(1, "Too many textures detected\n", 28);
	else if (error == -4)
		write(1, "Invalid color\n", 14);
	else if (error == -5)
		write(1, "Mallocing textures failed\n", 26);
}

void	error_res(int error)
{
	if (error == -2) // A changer en macro
		write(1, "Incorrect resolution\n", 21);
	else if (error == -3)
		write(1, "Not enough arguments\n", 21);
	else if (error == -4)
		write(1, "Map not found\n", 14);
	else if (error == NOT_VALID_ARG)
		write(1, "Incorrect argument entered\n", 28);
}

void	error(int error, t_a *a)
{
	(void)a;
	
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
	exit(-1);
}
