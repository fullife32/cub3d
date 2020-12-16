/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 18:19:43 by eassouli          #+#    #+#             */
/*   Updated: 2020/12/16 14:38:39 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "raycast.h"
#include "stack.h"

static const char *test[MAX_ERROR] = 
{
	"No map path found after the program name\n",
	"Too many arguments entered\n",
	"'.cub' file not found\n",
	"The second argument must be a '.cub' file\n",
	"The third argument must be '--save'\n",
	"Initialization of MLX server failed\n",
	"Malloc failed in init\n",
	"Not enough identifier entered\n",
	"Incorrect identifier entered\n",
	"Too many display resolutions set\n",
	"Incorrect resolution\n",
	"Invalid texture identifier\n",
	"Too many textures detected\n",
	"Invalid color\n",
	"Malloc failed in parse_txr\n",
	"Malloc failed in map\n",
	"There are too many starting points in the map\n",
	"There is an invalid char in the map\n",
	"No starting point found in the map\n"
};

int		destroy(t_a *a) // destroy aussi image fenetre
{
	if (a->bmp.fd == 0)
		system("kill -9 $(pidof aplay) > /dev/null");
	if (a->mlx.win)
		mlx_destroy_window(a->mlx.ptr, a->mlx.win);
	if (a->img.img_ptr)
		mlx_destroy_image(a->mlx.ptr, a->img.img_ptr);
	free_map(a->map.map);
	exit(OK); // Ne pas juste exit mais return error
}

// void	error_raycast(int error)
// {
// 	if (error == BMP_FAIL)
// 		write(1, "Some issues happened when creating the .bmp file", 49);
// }

// else if (error == MUSIC_FILE_FAIL) // add it to the tab
	// 	write(1, "Music file name/path is incorrect\n", 35);


void	error(int error, t_a *a)
{
	(void)a;

	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd((char *)test[error], STDERR_FILENO);
	exit(-1); //link to destroy
}
