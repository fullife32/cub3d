/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 18:19:43 by eassouli          #+#    #+#             */
/*   Updated: 2020/12/17 16:54:34 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "raycast.h"
#include "stack.h"

static const char	*g_error[MAX_ERROR] =
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
	"No starting point found in the map\n",
	"Malloc failed in map_leak\n",
	"Map is not closed correctly\n",
	"Malloc failed in sprite_list\n"
};

int		destroy(t_a *a) // destroy aussi image fenetre
{
	parse_free(a);
	map_free(a->map.map);
	// ft_lstclear(&a->map.first, (void *)ft_lstdelone); try adding it
	txr_free(a);
	sprite_free(a);
	if (a->bmp.fd == -2)
		system("kill -9 $(pidof aplay) > /dev/null");
	if (a->mlx.win)
		mlx_destroy_window(a->mlx.ptr, a->mlx.win);
	if (a->img.img_ptr)
		mlx_destroy_image(a->mlx.ptr, a->img.img_ptr);
	// if (a->mlx.ptr)
	// 	free(a->mlx.ptr);
	exit(OK);
}

// void	error_raycast(int error)
// {
// 	if (error == BMP_FAIL)
// 		write(1, "Some issues happened when creating the .bmp file", 49);
// }

void	error(int error, t_a *a)
{
	(void)a;

	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd((char *)g_error[error], STDERR_FILENO);
	destroy(a);
}
