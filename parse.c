/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 18:02:44 by eassouli          #+#    #+#             */
/*   Updated: 2020/04/02 18:22:41 by eassouli         ###   ########.fr       */
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

int	txr_parse(char c, char *line, t_txr *txr)
{
	int	len;

	len = 0;
	line++;
	if ((c == 'N' && *line++ != 'O') || (c == 'W' && *line != 'E')
	|| (c == 'S' && !(*line == ' ' || *line == 'O'))
	|| (c == 'E' && *line != 'A'))
		return (ERR);
	if (c == 'S' && !(*line == ' ' || *line == 'O'))
		c = *line;
	while (*line == ' ')
		line++;
	while (*(line + len) != '\0')
		len++;
	if (c == 'N')
		ft_strlcpy(txr->north, line, len + 1);
	if (c == 'O')
		ft_strlcpy(txr->south, line, len + 1);
	if (c == 'W')
		ft_strlcpy(txr->west, line, len + 1);
	if (c == 'E')
		ft_strlcpy(txr->east, line, len + 1);
	if (c == ' ')
		ft_strlcpy(txr->sprite, line, len + 1);
	return (OK);
}

int	parse(int fd, t_res *res, t_txr *txr, t_clr *clr)
{
	char	*line;
	
	while (get_next_line(fd, &line) > 0)
	{
		printf("%s\n", line);
		printf("width = %d height = %d north = %s\n", res->width, res->height, txr->north);
		// printf("RES :\nwidth = %d\nheight = %d\n\nTXR :\nnorth = %s\nsouth = %s\nwest = %s\neast = %s\nsprite = %s\n\nCLR :\nfloor :\nr = %d, g = %d, b = %d\nfloor = %s\nceilng :\nr = %d, g = %d, b = %d\nceiling = %s\n", res->width, res->height, txr->north, txr->south, txr->west, txr->east, txr->sprite, clr->f_r, clr->f_g, clr->f_b, clr->floor, clr->c_r, clr->c_g, clr->c_b, clr->ceiling);
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
