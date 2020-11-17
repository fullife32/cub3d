/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 18:02:44 by eassouli          #+#    #+#             */
/*   Updated: 2020/11/17 12:20:36 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	free_line(char **line)
{
	if (*line)
		free(*line);
	*line = NULL;
}

void	parse(t_a *a)
{
	int		i;
	char	**line;
	
	*line = a->mlx.line;
	while (get_next_line(a->mlx.fd, line) > 0)
	{
		i = 0;
		while (*line[i] == ' ')
			i++;
		if (*line[i] == 'R')
			res_parse(a);
		else if (*line[i] == 'N' || *line[i] == 'S' || *line[i] == 'W'
		|| *line[i] == 'E' || *line[i] == 'F' || *line[i] == 'C')
			txr_parse(*line[i], *line + i, a);
		else if (*line[i] == '0' || *line[i] == '1' || *line[i] == '2')
		{
			if (dup_check('c') != 8)
				error(-3, a);
			map_parse(a); // add error if empty lines then something again
			sprite_list(a);
			return;
		}
		else if (*line[i] != ' ' && *line[i])
			error(NOT_VALID_ARG, a);
		free_line(line);
	}
	error(-4, a);
}
