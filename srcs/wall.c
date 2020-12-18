/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 15:28:48 by eassouli          #+#    #+#             */
/*   Updated: 2020/12/18 15:30:41 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_atx	wall_select(t_a *a)
{	
	if (a->map.side == 1 && a->dst.step_y == 1)
		return (a->north_txr); //NORD
	else if (a->map.side == 1 && a->dst.step_y == -1)
		return (a->south_txr); //SUD
	else if (a->map.side == 0 && a->dst.step_x == -1)
		return (a->east_txr); //EST
	return (a->west_txr); //OUEST
}
