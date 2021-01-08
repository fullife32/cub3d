/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_malloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 15:05:17 by eassouli          #+#    #+#             */
/*   Updated: 2021/01/08 15:27:24 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	txr_malloc2(char c, int len, t_txr *txr)
{
	if (c == ' ')
	{
		txr->sprite = malloc(sizeof(char) * len + 1);
		if (txr->sprite == NULL)
			return (ERR);
	}
	if (c == 'F')
	{
		txr->floor = malloc(sizeof(char) * len + 1);
		if (txr->floor == NULL)
			return (ERR);
	}
	if (c == 'C')
	{
		txr->ceiling = malloc(sizeof(char) * len + 1);
		if (txr->ceiling == NULL)
			return (ERR);
	}
	return (OK);
}

int	txr_malloc(char c, int len, t_txr *txr)
{
	if (c == 'N')
	{
		txr->north = malloc(sizeof(char) * len + 1);
		if (txr->north == NULL)
			return (ERR);
	}
	if (c == 'S')
	{
		txr->south = malloc(sizeof(char) * len + 1);
		if (txr->south == NULL)
			return (ERR);
	}
	if (c == 'W')
	{
		txr->west = malloc(sizeof(char) * len + 1);
		if (txr->west == NULL)
			return (ERR);
	}
	if (c == 'E')
	{
		txr->east = malloc(sizeof(char) * len + 1);
		if (txr->east == NULL)
			return (ERR);
	}
	return (txr_malloc2(c, len, txr));
}
