/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 18:02:44 by eassouli          #+#    #+#             */
/*   Updated: 2021/01/12 23:15:05 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_hub(t_a *a)
{
	if (dup_check('c') != 8)
		error(NOT_ENOUGH_ID, a);
	map_parse(a);
	sprite_list(a);
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
		else if (line[i] == '0' || line[i] == '1'
			|| line[i] == '2' || line[i] == ' ')
			return (map_hub(a));
		else if (line[i] != ' ' && line[i])
			error(NOT_VALID_ID, a);
		line_free(a);
	}
	line_free(a);
	error(NOT_ENOUGH_ID, a);
}
