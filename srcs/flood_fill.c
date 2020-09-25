/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 18:00:36 by eassouli          #+#    #+#             */
/*   Updated: 2020/09/25 14:56:27 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

//ici , Nord = (0, -1), Sud = (0, 1);
//Est = (1, 0) et Ouest = (-1, 0);

int	flood_fill(char **map, t_vec pos, int xmax, int ymax)
{
	t_vec		n;
	t_frame		*stack;
	const int	x_axis[4] = {-1, 0, 1, 0};
	const int	y_axis[4] = {0, 1, 0, -1};
	t_vec		proj;
	int			i;
	
	stack = NULL;
	if (ft_strchr("NSWE0", map[pos.y][pos.x]) == NULL)
		return (FALSE);
	stack_push(&stack, pos);
	while (stack_len(stack) != 0)
	{
		n = stack_pop(&stack);
		map[n.y][n.x] = 'x';
		i = 0;
		while (i < 4)
		{
			proj = (t_vec){n.x + x_axis[i], n.y + y_axis[i]};
			if (proj.x >= 0 && proj.x < xmax && proj.y >= 0 && proj.y < ymax)
			{
				if (ft_strchr("023 ", map[proj.y][proj.x]))
					stack_push(&stack, proj);
			}
			else
				return (FALSE);
			i++;
		}
	}
	return (TRUE);
}
