/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 10:57:45 by eassouli          #+#    #+#             */
/*   Updated: 2020/09/15 11:18:57 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "parse.h"

#define TRUE 1
#define FALSE 0

typedef struct	s_frame
{
	t_frame	*next;
	t_vec	pos;
}				t_frame;

t_frame	*stack_init(t_vec pos);
void	stack_push(t_frame **item, t_vec pos);
t_vec	stack_pop(t_frame **item);
int		stack_len(t_frame *item);
char	**map_cpy(t_map *map);
int		map_vfy_print(t_map *map);
int		flood_fill(char **map, t_vec pos, int xmax, int ymax);

#endif