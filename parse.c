/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 18:02:44 by eassouli          #+#    #+#             */
/*   Updated: 2020/04/01 17:13:04 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	res_check(char *line, t_res *res)
{
	while (*line == ' ' || *line == 'R')
		line++;
	res->width = ft_atoi(line);
	if (res->width > 1920)
		res->width = 1920;
	while (*line >= '0' && *line <= '9')
		line++;
	while (*line == ' ')
		line++;
	res->height = ft_atoi(line);
	if (res->height > 1080)
		res->height = 1080;
	if (res->height <= 0 || res->width <= 0)
		return (ERR);
	return (OK);
}

int	txr_check(char c, char *line, t_txr *txr)
{
	int	len;

	len = 0;
	line++;
	if ((c == 'N' && *line != 'O')
	|| (c == 'S' && (*line != ' ' || *line != 'O') && (c = *line))
	|| (c == 'W' && *line != 'E')
	|| (c == 'E' && *line != 'A'))
		return (ERR);
	line++;
	while (*line == ' ')
		line++;
	while (line + len != '\0')
		len++;
	if (c == 'N')
		ft_strlcpy(txr->north, line, len);
	if (c == 'O')
		ft_strlcpy(txr->south, line, len);
	if (c == 'W')
		ft_strlcpy(txr->west, line, len);
	if (c == 'E')
		ft_strlcpy(txr->east, line, len);
	if (c == ' ')
		ft_strlcpy(txr->sprite, line, len);
	return (OK);
}

int	parse(int fd, t_res *res, t_txr *txr, t_clr *clr)
{
	char	*line;
	
	while (get_next_line(fd, &line) > 0)
	{
		while (*line == ' ')
			line++;
		if (*line == 'R')
		{
			if (res_check(line, res) == ERR)
				return (ERR);
		}
		if (*line == 'N' || *line == 'S' || *line == 'W' || *line == 'E')
		{
			if (txr_check(*line, line, txr) == ERR)
				return (ERR);
		}
		if (*line == 'F' || *line == 'C')

		if (*line == '0' || *line == '1' || *line == '2')
		free(line);
		line = NULL;
	}
	return (OK);
}
