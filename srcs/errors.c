/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 18:19:43 by eassouli          #+#    #+#             */
/*   Updated: 2021/01/12 15:28:33 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static const char	*g_error[MAX_ERROR] = {
	"No map path found after program name\n",
	"Too many arguments entered\n",
	"'.cub' file not found\n",
	"The second argument must be a '.cub' file\n",
	"The third argument must be '--save'\n",
	"MLX server initialization failed\n",
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
	"There are too many starting points on the map\n",
	"There is an invalid character in the map\n",
	"No starting point found on the map\n",
	"Malloc failed in map_leak\n",
	"The map is not correctly closed\n",
	"Malloc failed in sprite_list\n",
	"Cannot load a texture\n",
	"Cannot load a sprite\n",
	"Cannot generate a '.bmp' file\n"
};

void	del(void *content)
{
	if (content)
		free(content);
	content = NULL;
}

int	destroy(t_a *a)
{
	parse_free(a);
	ft_lstclear(&a->map.first, del);
	if (a->map.map)
		free(a->map.map);
	if (a->map.m_cp)
		map_free(a->map.m_cp);
	txr_free(a);
	wall_free(a);
	sprite_free(a);
	if (a->bmp.fd == -2)
		system("kill -9 $(pidof aplay)");
	if (a->img.img_ptr)
		mlx_destroy_image(a->mlx.ptr, a->img.img_ptr);
	if (a->mlx.win)
		mlx_destroy_window(a->mlx.ptr, a->mlx.win);
	if (a->mlx.ptr)
	{
		mlx_destroy_display(a->mlx.ptr);
		free(a->mlx.ptr);
	}
	a->mlx.ptr = NULL;
	if (a->mlx.fd > 0)
		close (a->mlx.fd);
	exit(OK);
}

void	error(int error, t_a *a)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd((char *)g_error[error], STDERR_FILENO);
	destroy(a);
}
