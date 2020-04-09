/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 16:11:43 by eassouli          #+#    #+#             */
/*   Updated: 2020/04/09 17:18:42 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

int	mlx_test(t_res *res)
{
	void	*mlx_ptr;
	void	*win_ptr;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, res->width, res->height, "WOA");
	mlx_pixel_put(mlx_ptr, win_ptr, 250, 250, 0xFFFFFF)
;	mlx_loop(mlx_ptr);
	return (OK);
}