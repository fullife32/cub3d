/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 14:17:49 by eassouli          #+#    #+#             */
/*   Updated: 2020/12/16 14:38:14 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "raycast.h"

void	free_txr(t_a *a)
{
	if (a->txr.north)
		free(a->txr.north);
	if (a->txr.south)
		free(a->txr.south);
	if (a->txr.west)
		free(a->txr.west);
	if (a->txr.east)
		free(a->txr.east);
	if (a->txr.sprite)
		free(a->txr.sprite);
	if (a->txr.floor)
		free(a->txr.floor);
	if (a->txr.ceiling)
		free(a->txr.ceiling);
}
