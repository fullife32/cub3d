/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_resolution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 17:33:18 by eassouli          #+#    #+#             */
/*   Updated: 2020/11/24 13:44:39 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "raycast.h"

void	res_parse(t_a *a)
{
	int		w;
	int		h;
	char	*line;

	line = *a->mlx.line;
	if (dup_check(*line) == ERR)
		error(-2, a);
	line++;
	while (*line == ' ')
		line++;
	mlx_get_screen_size(a->mlx.ptr, &w, &h);
	a->res.w = ft_atoi(line);
	if (a->res.w > w)
		a->res.w = w;
	while (*line >= '0' && *line <= '9')
		line++;
	while (*line == ' ')
		line++;
	a->res.h = ft_atoi(line);
	if (a->res.h > h)
		a->res.h = h;
	while (*line >= '0' && *line <= '9')
		line++;
	a->res.w = (*line != '\0') ? 0 : a->res.w;
	if (a->res.w <= 0 || a->res.h <= 0)
		error(-2, a);
}
