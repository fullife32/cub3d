/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 15:10:31 by eassouli          #+#    #+#             */
/*   Updated: 2020/11/13 15:28:36 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "raycast.h"

void	cub_check(char *av, t_a *a)
{
	int	i;
	int	j;

	i = 0;
	j = 3;
	while (av[i])
		i++;
	i--;
	while (av[i--] == CUB[j] && j != -1)
		j--;
	if (j == -1)
	{
		if ((a->mlx.fd = open(av, O_RDONLY)) == -1)
			error(MISSING_CUB_FILE, a);
	}
	else
		if ((a->mlx.fd = -1) == ERR)
			error(NOT_CUB_FILE, a);
}

void	save_check(char *av, t_a *a)
{
	int	i;

	i = 0;
	while (SAVE[i] && av[i])
	{
		if (SAVE[i] != av[i])
			error(BMP_FAIL, a);
		i++;
	}
	if (rec_bmp_h(a) != OK)
		error(BMP_FAIL, a);
}
