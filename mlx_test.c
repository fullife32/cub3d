/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 16:11:43 by eassouli          #+#    #+#             */
/*   Updated: 2020/04/09 18:02:31 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

int	deal_key(int key, void *params)
{
	(void)key;
	(void)params;
	ft_putnbr_fd(key, 1);
	return (OK);
}

int	mlx_test(t_res *res)
{
	t_mlx	mlx;

	mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, res->width, res->height, "WOA");
	mlx_pixel_put(mlx.mlx_ptr, mlx.win_ptr, 250, 250, 0xFFFFFF);
	mlx_key_hook(mlx.win_ptr, deal_key, (void *)0);
	mlx_loop(mlx.mlx_ptr);
	return (OK);
}