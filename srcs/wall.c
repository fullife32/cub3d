/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 15:28:48 by eassouli          #+#    #+#             */
/*   Updated: 2021/01/08 14:06:42 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_atx	wall_select(t_a *a)
{	
	if (a->map.side == 1 && a->dst.step_y == 1)
		return (a->north_txr);
	else if (a->map.side == 1 && a->dst.step_y == -1)
		return (a->south_txr);
	else if (a->map.side == 0 && a->dst.step_x == -1)
		return (a->east_txr);
	return (a->west_txr);
}
