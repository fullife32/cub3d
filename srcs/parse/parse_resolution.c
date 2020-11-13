/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_resolution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 17:33:18 by eassouli          #+#    #+#             */
/*   Updated: 2020/11/13 16:33:47 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "raycast.h"

void	res_parse(t_a *a)
{
	int	w;
	int h;

	if (dup_check(*a->mlx.line) == ERR)
		error(-2, a);
	a->mlx.line++;
	while (*a->mlx.line == ' ')
		a->mlx.line++;
	mlx_get_screen_size(a->mlx.ptr, &w, &h);
	a->res.w = ft_atoi(a->mlx.line);
	if (a->res.w > w)
		a->res.w = w;
	while (*a->mlx.line >= '0' && *a->mlx.line <= '9')
		a->mlx.line++;
	while (*a->mlx.line == ' ')
		a->mlx.line++;
	a->res.h = ft_atoi(a->mlx.line);
	if (a->res.h > h)
		a->res.h = h;
	while (*a->mlx.line >= '0' && *a->mlx.line <= '9')
		a->mlx.line++;
	a->res.w = (*a->mlx.line != '\0') ? 0 : a->res.w;
	if (a->res.w <= 0 || a->res.h <= 0)
		error(-2, a);
}
