/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/02 17:15:03 by eassouli          #+#    #+#             */
/*   Updated: 2021/01/13 16:59:34 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	txr_rgb(char c, int *rgb, t_txr *txr)
{
	if (c == 'F')
		txr->f_rgb = 65536 * rgb[0] + 256 * rgb[1] + rgb[2];
	else if (c == 'C')
		txr->c_rgb = 65536 * rgb[0] + 256 * rgb[1] + rgb[2];
}

int	txr_atoi(char c, char *line, t_txr *txr)
{
	int	i;
	int	rgb[3];

	i = -1;
	while (++i <= 2)
	{
		while (*line == ' ' || *line == '\t')
			line++;
		rgb[i] = ft_atoi(line);
		if (rgb[i] < 0 || rgb[i] > 255)
			return (ERR);
		if (!(*line >= '0' && *line <= '9'))
			return (ERR);
		while (*line >= '0' && *line <= '9')
			line++;
		while (*line == ' ' || *line == '\t')
			line++;
		if (i == 2 && *line != '\0')
			return (ERR);
		if (i != 2 && *line++ != ',')
			return (ERR);
	}
	txr_rgb(c, rgb, txr);
	return (OK);
}
