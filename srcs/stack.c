/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 15:01:25 by eassouli          #+#    #+#             */
/*   Updated: 2020/09/25 15:01:35 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/stack.h"

t_frame	*stack_init(t_vec pos)
{
	t_frame *frame;

	frame = malloc(sizeof(t_frame));
	if (frame == NULL)
		return (NULL);
	frame->next = NULL;
	frame->pos = pos;
	return (frame);
}

void	stack_push(t_frame **item, t_vec pos)
{
	t_frame	*old;

	old = *item;
	*item = stack_init(pos);
	(*item)->next = old;
}

t_vec	stack_pop(t_frame **item)
{
	t_vec	pos;
	t_frame	*old;

	if (*item == NULL)
		return ((t_vec){INT_MAX, INT_MIN});
	old = *item;
	*item = (*item)->next;
	pos = old->pos;
	free(old);
	return(pos);
}

int	stack_len(t_frame *item)
{
	int	i;

	i = 0;
	while (item != NULL)
	{
		item = item->next;
		i++;
	}
	return (i);
}
