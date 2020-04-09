/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 16:11:43 by eassouli          #+#    #+#             */
/*   Updated: 2020/04/09 18:13:01 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

int	deal_key(int key, void *params)
{
	ft_putnbr_fd(key, 1);
	mlx_pixel_put(((t_mlx *)params)->mlx_ptr, ((t_mlx *)params)->win_ptr, key, key, 0xFFFFFF);
	return (OK);
}

int	mlx_test(t_res *res)
{
	t_mlx	mlx;

	mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, res->width, res->height, "WOA");
	mlx_pixel_put(mlx.mlx_ptr, mlx.win_ptr, 250, 250, 0xFFFFFF);
	mlx_key_hook(mlx.win_ptr, deal_key, &mlx);
	mlx_loop(mlx.mlx_ptr);
	return (OK);
}