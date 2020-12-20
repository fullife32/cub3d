/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_proto.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 19:04:33 by eassouli          #+#    #+#             */
/*   Updated: 2020/12/19 19:06:17 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_PROTO_H
#define STACK_PROTO_H

t_frame				*stack_init(t_vec pos);
void				stack_push(t_frame **item, t_vec pos);
t_vec				stack_pop(t_frame **item);
int					stack_len(t_frame *item);
void				map_cpy(t_a *a);
void				map_vfy_print(t_a *a);
int					flood_fill(char **map, t_vec pos, t_vec max);

#endif