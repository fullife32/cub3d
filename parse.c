/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 18:02:44 by eassouli          #+#    #+#             */
/*   Updated: 2020/05/24 18:19:00 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	err(char **line, int error)
{
	if (error != ERR)
		write(1, "Error\n", 6);
	if (error == -2)
		write(1, "Incorrect resolution\n", 21);
	else if (error == -3)
		write(1, "Not enough arguments\n", 21);
	else if (error == -4)
		write(1, "Map not found\n", 14);
	if (*line)
		free(*line);
	*line = NULL;
	return (ERR);
}

// ajouter fonction pour connaitre la resolution ecran et retourner error si res > display res
int	res_parse(char *line, t_res *res)
{
	if (dup_check(*line) == ERR)
		return (ERR);
	line++;
	while (*line == ' ')
		line++;
	res->w = ft_atoi(line);
	if (res->w > 1920)
		res->w = 1920;
	while (*line >= '0' && *line <= '9')
		line++;
	while (*line == ' ')
		line++;
	res->h = ft_atoi(line);
	if (res->h > 1080)
		res->h = 1080;
	if (res->h <= 0 || res->w <= 0)
		return (ERR);
	return (OK);
}

int	parse(int fd, t_res *res, t_txr *txr, t_map *map, t_plr *plr)
{
	char	*line;
	int		i;
	
	while (get_next_line(fd, &line) > 0)
	{
		i = 0;
		while (line[i] == ' ')
			i++;
		if (line[i] == 'R')
			if (res_parse(line + i, res) == ERR)
				return (err(&line, -2));
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W'
		|| line[i] == 'E' || line[i] == 'F' || line[i] == 'C')
			if (txr_parse(line[i], line + i, txr) == ERR)
				return (err(&line, ERR));
		if (line[i] == '0' || line[i] == '1' || line[i] == '2')
		{
			if (dup_check('c') != 8)
				return (err(&line, -3));
			if (map_parse(fd, line, map, plr) == ERR)
				return (err(&line, ERR));
			else
				return (OK);
		}
		err(&line, ERR);
	}
	return (err(&line, -4));
}
