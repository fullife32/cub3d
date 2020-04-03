/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 18:02:44 by eassouli          #+#    #+#             */
/*   Updated: 2020/04/04 00:32:25 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	res_parse(char *line, t_res *res)
{
	line++;
	while (*line == ' ')
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

int	parse(int fd, t_res *res, t_txr *txr, t_clr *clr)
{
	char	*line;
	
	while (get_next_line(fd, &line) > 0)
	{
		printf("%s\n", line);
		while (*line == ' ')
			line++;
		if (*line == 'R')
			if (res_parse(line, res) == ERR)
				return (ERR);
		if (*line == 'N' || *line == 'S' || *line == 'W' || *line == 'E')
			if (txr_parse(*line, line, txr) == ERR)
				return (ERR);
		if (*line == 'F' || *line == 'C')
			if (clr_parse(*line, line, clr) == ERR)
				return (ERR);
		if (*line == '0' || *line == '1' || *line == '2')
			;
		free(line);
		line = NULL;
	}
	return (OK);
}
