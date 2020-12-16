/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 18:02:44 by eassouli          #+#    #+#             */
/*   Updated: 2020/12/16 11:39:03 by eassouli         ###   ########.fr       */
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
				error(NOT_ENOUGH_ID, a);
			map_parse(a); // add error if empty lines then something again
			sprite_list(a);
			return;
		}
		else if (line[i] != ' ' && line[i]) //check if it works for a char between lines
			error(NOT_VALID_ID, a);
		free_line(a);
	}
	error(NOT_ENOUGH_ID, a);
}
