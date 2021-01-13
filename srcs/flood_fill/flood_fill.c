/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 18:00:36 by eassouli          #+#    #+#             */
/*   Updated: 2021/01/13 17:15:15 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** North = (0, -1), South = (0, 1);
** East = (1, 0), West = (-1, 0);
*/

int	free_stack(t_frame *stack, t_proj p)
{
	while (stack_len(stack) != 0)
		p.n = stack_pop(&stack);
	return (FALSE);
}

int	find(char **map, t_frame **stack, t_vec proj)
{
	if (ft_strchr("02 ", map[proj.y][proj.x]))
	{
		if (stack_push(stack, proj) == ERR)
			return (ERR);
	}
	return (OK);
}

int	flood_fill(char **map, t_vec pos, t_vec max, t_frame *stack)
{
	t_proj		p;
	int			i;

	stack = NULL;
	if (stack_push(&stack, pos) == ERR)
		return (FALSE);
	while (stack_len(stack) != 0)
	{
		p.n = stack_pop(&stack);
		map[p.n.y][p.n.x] = 'x';
		i = 0;
		while (i < 4)
		{
			p.pr = (t_vec){p.n.x + (int [4]){-1, 0, 1, 0}[i]
				, p.n.y + (int [4]){0, 1, 0, -1}[i]};
			if (p.pr.x >= 0 && p.pr.x < max.x && p.pr.y >= 0 && p.pr.y < max.y
				&& find(map, &stack, p.pr) != ERR)
				;
			else
				return (free_stack(stack, p));
			i++;
		}
	}
	return (TRUE);
}
