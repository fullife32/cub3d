/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   res_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 17:33:18 by eassouli          #+#    #+#             */
/*   Updated: 2020/06/22 16:12:28 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "raycast.h"

int	res_parse(char *line, t_res *res, t_mlx *mlx)
{
	int	w;
	int h;

	if (dup_check(*line) == ERR)
		return (ERR);
	line++;
	while (*line == ' ')
		line++;
	mlx_get_screen_size(mlx->ptr, &w, &h);
	res->w = ft_atoi(line);
	if (res->w > w)
		res->w = w;
	while (*line >= '0' && *line <= '9')
		line++;
	while (*line == ' ')
		line++;
	res->h = ft_atoi(line);
	if (res->h > h)
		res->h = h;
	while (*line >= '0' && *line <= '9')
		line++;
	res->w = (*line != '\0') ? 0 : res->w;
	if (res->w <= 0 || res->h <= 0)
		return (ERR);
	return (OK);
}