/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 18:00:36 by eassouli          #+#    #+#             */
/*   Updated: 2020/12/18 15:24:06 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//ici , Nord = (0, -1), Sud = (0, 1);
//Est = (1, 0) et Ouest = (-1, 0);

void	find(char **map, t_frame **stack, t_vec proj)
{
	if (ft_strchr("02 ", map[proj.y][proj.x]))
		stack_push(stack, proj);
}

int		flood_fill(char **map, t_vec pos, t_vec max)
{
	t_frame		*stack;
	t_proj		p;
	int			i;

	stack = NULL;
	if (ft_strchr("NSWE0", map[pos.y][pos.x]) == NULL)
		return (FALSE);
	stack_push(&stack, pos);
	while (stack_len(stack) != 0)
	{
		p.n = stack_pop(&stack);
		map[p.n.y][p.n.x] = 'x';
		i = 0;
		while (i < 4)
		{
			p.pr = (t_vec){p.n.x + (int[4]){-1, 0, 1, 0}[i],
					p.n.y + (int[4]){0, 1, 0, -1}[i]};
			if (p.pr.x >= 0 && p.pr.x < max.x && p.pr.y >= 0 && p.pr.y < max.y)
				find(map, &stack, p.pr);
			else
				return (FALSE);
			i++;
		}
	}
	return (TRUE);
}
