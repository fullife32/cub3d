/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 18:02:44 by eassouli          #+#    #+#             */
/*   Updated: 2020/11/24 15:33:30 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	free_line(t_a *a)
{
	if (*a->mlx.line)
		free(*a->mlx.line);
	*a->mlx.line = NULL;
}

void	parse(t_a *a)
{
	int		i;
	char	*line;

	while (get_next_line(a->mlx.fd, a->mlx.line) > 0)
	{
		i = 0;
		line = *a->mlx.line;
		while (line[i] == ' ')
			i++;
		if (line[i] == 'R')
			res_parse(a);
		else if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W'
		|| line[i] == 'E' || line[i] == 'F' || line[i] == 'C')
			txr_parse(line[i], line + i, a);
		else if (line[i] == '0' || line[i] == '1' || line[i] == '2' || line[i] == ' ')
		{
			if (dup_check('c') != 8)
				error(-3, a);
			map_parse(a); // add error if empty lines then something again
			sprite_list(a);
			return;
		}
		else if (line[i] != ' ' && line[i])
			error(NOT_VALID_ARG, a);
		free_line(a);
	}
	error(-4, a);
}
