/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   txr_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/04 00:32:33 by eassouli          #+#    #+#             */
/*   Updated: 2020/04/04 00:47:02 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	txr_cpy(char c, char *line, int len, t_txr *txr)
{
	if (c == 'N')
		ft_strlcpy(txr->north, line, len + 1);
	else if (c == 'S')
		ft_strlcpy(txr->south, line, len + 1);
	else if (c == 'W')
		ft_strlcpy(txr->west, line, len + 1);
	else if (c == 'E')
		ft_strlcpy(txr->east, line, len + 1);
	else if (c == ' ')
		ft_strlcpy(txr->sprite, line, len + 1);
}

int		txr_malloc(char c, int len, t_txr *txr)
{
	if (c == 'N')
		if ((txr->north = malloc(sizeof(char) * len + 1)) == NULL)
			return (ERR);
	if (c == 'S')
		if ((txr->south = malloc(sizeof(char) * len + 1)) == NULL)
			return (ERR);
	if (c == 'W')
		if ((txr->west = malloc(sizeof(char) * len + 1)) == NULL)
			return (ERR);
	if (c == 'E')
		if ((txr->east = malloc(sizeof(char) * len + 1)) == NULL)
			return (ERR);
	if (c == ' ')
		if ((txr->sprite = malloc(sizeof(char) * len + 1)) == NULL)
			return (ERR);
	return (OK);
}

int		txr_parse(char c, char *line, t_txr *txr)
{
	int	len;

	len = 0;
	line++;
	if ((c == 'N' && *line != 'O') || (c == 'W' && *line != 'E')
	|| (c == 'S' && (*line != ' ' && *line != 'O'))
	|| (c == 'E' && *line != 'A'))
		return (ERR);
	c = (c == 'S' && *line == ' ') ? ' ' : c;
	c = (c == 'S' && *line == 'O') ? 'S' : c;
	line++;
	while (*line == ' ')
		line++;
	while (*(line + len) != '\0' && *(line + len) != ' ')
		len++;
	if (txr_malloc(c, len + 1, txr) == ERR)
		return (ERR);
	txr_cpy(c, line, len, txr);
	return (OK);
}
