/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_malloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 15:05:17 by eassouli          #+#    #+#             */
/*   Updated: 2021/01/13 15:10:14 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	txr_malloc2(char c, int len, t_a *a)
{
	if (c == 's')
	{
		a->txr.sprite = malloc(sizeof(char) * len + 1);
		if (a->txr.sprite == NULL)
			error(MALLOC_FAIL_TXR, a);
	}
	if (c == 'F')
	{
		a->txr.floor = malloc(sizeof(char) * len + 1);
		if (a->txr.floor == NULL)
			error(MALLOC_FAIL_TXR, a);
	}
	if (c == 'C')
	{
		a->txr.ceiling = malloc(sizeof(char) * len + 1);
		if (a->txr.ceiling == NULL)
			error(MALLOC_FAIL_TXR, a);
	}
}

void	txr_malloc(char c, int len, t_a *a)
{
	if (c == 'N')
	{
		a->txr.north = malloc(sizeof(char) * len + 1);
		if (a->txr.north == NULL)
			error(MALLOC_FAIL_TXR, a);
	}
	if (c == 'S')
	{
		a->txr.south = malloc(sizeof(char) * len + 1);
		if (a->txr.south == NULL)
			error(MALLOC_FAIL_TXR, a);
	}
	if (c == 'W')
	{
		a->txr.west = malloc(sizeof(char) * len + 1);
		if (a->txr.west == NULL)
			error(MALLOC_FAIL_TXR, a);
	}
	if (c == 'E')
	{
		a->txr.east = malloc(sizeof(char) * len + 1);
		if (a->txr.east == NULL)
			error(MALLOC_FAIL_TXR, a);
	}
	txr_malloc2(c, len, a);
}
