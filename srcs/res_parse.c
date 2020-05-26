/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   res_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 17:33:18 by eassouli          #+#    #+#             */
/*   Updated: 2020/05/26 17:33:41 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

// ajouter fonction pour connaitre la resolution ecran et retourner error si res > display res
int	res_parse(char *line, t_res *res)
{
	if (dup_check(*line) == ERR)
		return (ERR);
	line++;
	while (*line == ' ')
		line++;
	res->w = ft_atoi(line);
	if (res->w > 1920)
		res->w = 1920;
	while (*line >= '0' && *line <= '9')
		line++;
	while (*line == ' ')
		line++;
	res->h = ft_atoi(line);
	if (res->h > 1080)
		res->h = 1080;
	if (res->h <= 0 || res->w <= 0)
		return (ERR);
	return (OK);
}
