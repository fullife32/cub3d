/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 18:19:43 by eassouli          #+#    #+#             */
/*   Updated: 2020/12/15 17:29:09 by eassouli         ###   ########.fr       */
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

	// else if (error == MUSIC_FILE_FAIL) // add it to the tab
	// 	write(1, "Music file name/path is incorrect\n", 35);

static const char *test[MAX_ERROR] = 
{
	"Error\n",
	".cub file not found\n",
	"The second argument must be a .cub file\n",
	"Initialization of MLX server failed\n",
	"Not enough arguments entered\n",
	"Incorrect argument entered\n",
	"Too many resolution arguments\n",
	"Incorrect resolution\n",
	"Invalid texture argument\n",
	"Too many textures detected\n",
	"Invalid color\n",
	"Malloc failed in parse_txr\n",
	"Malloc failed in map\n",
	"There are too many starting points in the map\n",
	"Not a valid char in the map\n",
	"No starting point found in the map\n"
};

#include <unistd.h>

void	error(int error, t_a *a)
{
	(void)a;

	ft_putstr_fd((char *)test[0], STDERR_FILENO);
	ft_putstr_fd((char *)test[error], STDERR_FILENO);
	exit(-1);
}
