/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 10:57:45 by eassouli          #+#    #+#             */
/*   Updated: 2020/12/17 14:29:30 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include "parse.h"

# define TRUE 1
# define FALSE 0

typedef struct		s_vec
{
	int				x;
	int				y;
}					t_vec;

typedef struct		s_frame
{
	struct s_frame	*next;
	t_vec			pos;
}					t_frame;

typedef struct		s_proj
{
	t_vec	pr;
	t_vec	n;
}					t_proj;

t_frame				*stack_init(t_vec pos);
void				stack_push(t_frame **item, t_vec pos);
t_vec				stack_pop(t_frame **item);
int					stack_len(t_frame *item);
void				map_cpy(t_a *a);
void				map_vfy_print(t_a *a);
int					flood_fill(char **map, t_vec pos, t_vec max);

#endif
