/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clr_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/02 17:15:03 by eassouli          #+#    #+#             */
/*   Updated: 2020/04/02 17:16:36 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	clr_rgb(char c, int *rgb, t_clr *clr)
{
	if (c == 'F')
	{
		clr->f_r = rgb[0];
		clr->f_g = rgb[1];
		clr->f_b = rgb[2];
	}
	else if (c == 'C')
	{
		clr->c_r = rgb[0];
		clr->c_g = rgb[1];
		clr->c_b = rgb[2];
	}
}

int		clr_atoi(char c, char *line, t_clr *clr)
{
	int	i;
	int	rgb[3];

	i = -1;
	while (++i <= 2)
	{
		while (*line == ' ')
			line++;
		rgb[i] = ft_atoi(line);
		if (i == 2 && !(*line >= '0' && *line <= '9'))
			return (ERR);
		while (*line >= '0' && *line <= '9' && *line)
			line++;
		if (i != 2 && *line++ != ',')
			return (ERR);
	}
	clr_rgb(c, rgb, clr);
	return (OK);
}

int	clr_parse(char c, char *line, t_clr *clr)
{
	int	len;

	len = 0;
	line++;
	while (*line == ' ')
		line++;
	if (!(*line >= '0' && *line <= '9'))
	{
		while (*(line + len) != '\0')
			len++;
		if (c == 'F')
			ft_strlcpy(clr->floor, line, len);
		else if (c == 'C')
			ft_strlcpy(clr->ceiling, line, len);
	}
	else
	{
		if (clr_atoi(c, line, clr) == ERR)
			return (ERR);
	}
	return (OK);
}
