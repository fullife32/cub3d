/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolution_parse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 17:33:18 by eassouli          #+#    #+#             */
/*   Updated: 2021/01/13 16:27:27 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*size_check(char *line, int *res, int screen)
{
	*res = ft_atoi(line);
	if (*res > screen)
		*res = screen;
	while (*line >= '0' && *line <= '9')
		line++;
	return (line);
}

void	res_parse(t_a *a)
{
	int		w;
	int		h;
	char	*line;

	line = *a->mlx.line;
	if (dup_check(*line) == ERR)
		error(TOO_MANY_RES, a);
	line++;
	while (*line == ' ' || *line == '\t')
		line++;
	mlx_get_screen_size(a->mlx.ptr, &w, &h);
	line = size_check(line, &a->res.w, w);
	while (*line == ' ' || *line == '\t')
		line++;
	line = size_check(line, &a->res.h, h);
	while (*line == ' ' || *line == '\t')
		line++;
	if (*line != '\0')
		error(NOT_VALID_RES_NB, a);
	if (a->res.w <= 0)
		error(NOT_VALID_RES_W, a);
	else if (a->res.h <= 0)
		error(NOT_VALID_RES_H, a);
}
