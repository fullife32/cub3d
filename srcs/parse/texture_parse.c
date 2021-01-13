/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/04 00:32:33 by eassouli          #+#    #+#             */
/*   Updated: 2021/01/13 16:41:16 by eassouli         ###   ########.fr       */
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
	else if (c == 's')
		ft_strlcpy(txr->sprite, line, len + 1);
	else if (c == 'F')
		ft_strlcpy(txr->floor, line, len + 1);
	else if (c == 'C')
		ft_strlcpy(txr->ceiling, line, len + 1);
}

int	dup_check(char c)
{
	int			i;
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

void	txr_choice(char c, char *line, t_a *a)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	if (c == 'F' || c == 'C')
	{
		if (!(*line >= '0' && *line <= '9'))
			error(NOT_VALID_COLOR, a);
		if (txr_atoi(c, line, &a->txr) == ERR)
			error(NOT_VALID_COLOR, a);
	}
	else
	{
		while (*(line + len) != '\0' && *(line + len) != ' '
			&& *(line + len) != '\t')
			len++;
		while (*(line + len + i) == ' ' || *(line + len + i) == '\t')
			i++;
		if (*(line + len + i) != '\0')
			error(NOT_VALID_TXR_CHAR, a);
		txr_malloc(c, len, a);
		txr_cpy(c, line, len, &a->txr);
	}
}

void	txr_parse(char c, char *line, t_a *a)
{
	line++;
	if ((c == 'N' && *line != 'O') || (c == 'W' && *line != 'E')
		|| (c == 'E' && *line != 'A'))
		error(NOT_VALID_TXR, a);
	if (c == 'S' && *line != 'O')
		c = 's';
	if (dup_check(c) == ERR)
		error(TOO_MANY_TXR, a);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		line++;
	while (*line == ' ' || *line == '\t')
		line++;
	txr_choice(c, line, a);
}
