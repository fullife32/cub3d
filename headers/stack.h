/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 10:57:45 by eassouli          #+#    #+#             */
/*   Updated: 2020/12/19 19:05:52 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

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

#endif
