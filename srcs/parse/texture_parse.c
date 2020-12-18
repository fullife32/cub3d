/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/04 00:32:33 by eassouli          #+#    #+#             */
/*   Updated: 2020/12/18 15:22:44 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	else if (c == 'F')
		ft_strlcpy(txr->floor, line, len + 1);
	else if (c == 'C')
		ft_strlcpy(txr->ceiling, line, len + 1);
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
	if (c == 'F')
		if ((txr->floor = malloc(sizeof(char) * len + 1)) == NULL)
			return (ERR);
	if (c == 'C')
		if ((txr->ceiling = malloc(sizeof(char) * len + 1)) == NULL)
			return (ERR);
	return (OK);
}

int	dup_check(char c)
{
	int i;
	static char	tab[10];

	i = 0;
	while (tab[i] != '\0')
	{
		if (tab[i] == c)
			return (ERR);
		i++;
	}
	tab[i] = c;
	return (i);
}

void	txr_parse(char c, char *line, t_a *a)
{
	int	len;

	len = 0;
	line++;
	if ((c == 'N' && *line != 'O') || (c == 'W' && *line != 'E')
	|| (c == 'S' && (*line != ' ' && *line != 'O'))
	|| (c == 'E' && *line != 'A')
	|| ((c == 'F' || c == 'C') && *line != ' '))
		error(NOT_VALID_TXR, a);
	c = (c == 'S' && *line == 'O') ? 'S' : c;
	c = (c == 'S' && *line == ' ') ? ' ' : c;
	if (dup_check(c) == ERR)
		error(TOO_MANY_TXR, a);
	line++;
	while (*line == ' ')
		line++;
	if ((c == 'F' || c == 'C') && (*line >= '0' && *line <= '9'))
	{
		if (txr_atoi(c, line, &a->txr) == ERR)
			error(NOT_VALID_COLOR, a);
	}
	else
	{
		while (*(line + len) != '\0' && *(line + len) != ' ')
			len++;
		if (txr_malloc(c, len + 1, &a->txr) == ERR)
			error(MALLOC_FAIL_TXR, a);
		txr_cpy(c, line, len, &a->txr);
	}
}
