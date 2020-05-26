/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 18:02:44 by eassouli          #+#    #+#             */
/*   Updated: 2020/05/26 17:33:38 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	error(char **line, int error)
{
	if (error == ERR)
	{
		if (*line)
			free(*line);
		*line = NULL;
	}
	else
		write(1, "Error\n", 6);
	if (error == -2)
		write(1, "Incorrect resolution\n", 21);
	else if (error == -3)
		write(1, "Not enough arguments\n", 21);
	else if (error == -4)
		write(1, "Map not found\n", 14);
	return (ERR);
}

int	parse(int fd, t_a *a)
{
	char	*line;
	int		i;
	
	while (get_next_line(fd, &line) > 0)
	{
		i = 0;
		while (line[i] == ' ')
			i++;
		if (line[i] == 'R')
			if (res_parse(line + i, &a->res) == ERR)
				return (error(&line, -2));
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W'
		|| line[i] == 'E' || line[i] == 'F' || line[i] == 'C')
			if (txr_parse(line[i], line + i, &a->txr) == ERR)
				return (error(&line, ERR));
		if (line[i] == '0' || line[i] == '1' || line[i] == '2')
		{
			if (dup_check('c') != 8)
				return (error(&line, -3));
			if (map_parse(fd, line, &a->map, &a->plr) == ERR)
				return (error(&line, ERR));
			else
				return (OK);
		}
		error(&line, ERR);
	}
	return (error(&line, -4));
}
