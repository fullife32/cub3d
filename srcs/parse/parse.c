/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 18:02:44 by eassouli          #+#    #+#             */
/*   Updated: 2020/11/13 17:44:49 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	free_line(char **line)
{
	ft_putstr_fd(*line, 1);
	if (*line)
		free(*line);
	*line = NULL;
}

void	parse(t_a *a)
{
	int		i;
	
	while (get_next_line(a->mlx.fd, &a->mlx.line) > 0)
	{
		i = 0;
		while (a->mlx.line[i] == ' ')
			i++;
		if (a->mlx.line[i] == 'R')
			res_parse(a);
		else if (a->mlx.line[i] == 'N' || a->mlx.line[i] == 'S'
		|| a->mlx.line[i] == 'W' || a->mlx.line[i] == 'E'
		|| a->mlx.line[i] == 'F' || a->mlx.line[i] == 'C')
			txr_parse(a->mlx.line[i], a->mlx.line + i, a);
		else if (a->mlx.line[i] == '0' || a->mlx.line[i] == '1'
		|| a->mlx.line[i] == '2')
		{
			if (dup_check('c') != 8)
				error(-3, a);
			map_parse(a); // add error if empty lines then something again
			sprite_list(a);
			return;
		}
		else if (a->mlx.line[i] != ' ' && a->mlx.line[i])
			error(NOT_VALID_ARG, a);
		free_line(&a->mlx.line);
	}
	error(-4, a);
}
