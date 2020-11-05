/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 18:02:44 by eassouli          #+#    #+#             */
/*   Updated: 2020/11/05 17:48:08 by eassouli         ###   ########.fr       */
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
	if (error == -2) // A changer en macro
		write(1, "Incorrect resolution\n", 21);
	else if (error == -3)
		write(1, "Not enough arguments\n", 21);
	else if (error == -4)
		write(1, "Map not found\n", 14);
	else if (error == NOT_VALID_ARG)
		write(1, "Incorrect argument entered\n", 28);
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
		{
			if (res_parse(line + i, &a->res, &a->mlx) == ERR)
				return (error(&line, -2));
		}
		else if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W'
		|| line[i] == 'E' || line[i] == 'F' || line[i] == 'C')
		{
			if (txr_parse(line[i], line + i, &a->txr) == ERR)
				return (error(&line, ERR));
		}
		else if (line[i] == '0' || line[i] == '1' || line[i] == '2')
		{
			if (dup_check('c') != 8)
				return (error(&line, -3));
			if (map_parse(fd, line, a) == ERR)
				return (error(&line, ERR)); // add error if empty lines then something again
			else
			{
				sprite_list(a);
				return (OK);
			}
		}
		else if (line[i] != ' ' && line[i])
			return (error(&line, NOT_VALID_ARG));
		error(&line, ERR);
	}
	return (error(&line, -4));
}
