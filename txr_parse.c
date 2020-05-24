/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   txr_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/04 00:32:33 by eassouli          #+#    #+#             */
/*   Updated: 2020/05/24 20:03:43 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	err(int error)
{
	if (error != ERR)
		write(1, "Error\n", 6);
	if (error == -2)
		write(1, "Invalid texture argument\n", 25);
	else if (error == -3)
		write(1, "Too many arguments\n", 27);
	else if (error == -4)
		write(1, "Invalid color\n", 14);
	else if (error == -5)
		write(1, "Mallocing textures failed\n", 26);
	return (ERR);
}

void	txr_cpy(char c, char *line, int len, t_txr *txr)
{
	if (c == 'N')
		ft_strlcpy(txr->n, line, len + 1);
	else if (c == 'S')
		ft_strlcpy(txr->s, line, len + 1);
	else if (c == 'W')
		ft_strlcpy(txr->w, line, len + 1);
	else if (c == 'E')
		ft_strlcpy(txr->e, line, len + 1);
	else if (c == ' ')
		ft_strlcpy(txr->spt, line, len + 1);
	else if (c == 'F')
		ft_strlcpy(txr->f, line, len + 1);
	else if (c == 'C')
		ft_strlcpy(txr->c, line, len + 1);
}

int		txr_malloc(char c, int len, t_txr *txr)
{
	if (c == 'N')
		if ((txr->n = malloc(sizeof(char) * len + 1)) == NULL)
			return (ERR);
	if (c == 'S')
		if ((txr->s = malloc(sizeof(char) * len + 1)) == NULL)
			return (ERR);
	if (c == 'W')
		if ((txr->w = malloc(sizeof(char) * len + 1)) == NULL)
			return (ERR);
	if (c == 'E')
		if ((txr->e = malloc(sizeof(char) * len + 1)) == NULL)
			return (ERR);
	if (c == ' ')
		if ((txr->spt = malloc(sizeof(char) * len + 1)) == NULL)
			return (ERR);
	if (c == 'F')
		if ((txr->f = malloc(sizeof(char) * len + 1)) == NULL)
			return (ERR);
	if (c == 'C')
		if ((txr->c = malloc(sizeof(char) * len + 1)) == NULL)
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

int		txr_parse(char c, char *line, t_txr *txr)
{
	int	len;

	len = 0;
	line++;
	// A (peut etre) supprimer
	if ((c == 'N' && *line != 'O') || (c == 'W' && *line != 'E')
	|| (c == 'S' && (*line != ' ' && *line != 'O'))
	|| (c == 'E' && *line != 'A')
	|| ((c == 'F' || c == 'C') && *line != ' '))
		return (err(-2));
	c = (c == 'S' && *line == ' ') ? ' ' : c;
	c = (c == 'S' && *line == 'O') ? 'S' : c;
	if (dup_check(c) == ERR)
		return (err(-3));
	line++;
	while (*line == ' ')
		line++;
	if ((c == 'F' || c == 'C') && (*line >= '0' && *line <= '9'))
	{
		if (txr_atoi(c, line, txr) == ERR)
			return (err(-4));
	}
	else
	{
		while (*(line + len) != '\0' && *(line + len) != ' ')
			len++;
		if (txr_malloc(c, len + 1, txr) == ERR)
			return (-5);
		txr_cpy(c, line, len, txr);
	}
	return (OK);
}
