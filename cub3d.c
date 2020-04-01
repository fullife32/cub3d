/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/31 16:17:39 by eassouli          #+#    #+#             */
/*   Updated: 2020/04/01 17:13:59 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	init(t_res *res, t_clr *clr)
{
	res->height = 0;
	res->width = 0;
	clr->c_b = -1;
	clr->c_g = -1;
	clr->c_r = -1;
	clr->f_b = -1;
	clr->f_g = -1;
	clr->f_r = -1;
}

int	err(int error)
{
	write(1, "Error\n", 6);
	if (error == 1)
		write(1, "Invalid Format\n", 15);
	else if (error == 2)
		write(1, "Incorrect Parsing\n", 18);
	return (ERR);
}

int	main(int ac, char **av)
{
	int		fd;
	t_res	res;
	t_txr	txr;
	t_clr	clr;

	init(&res, &clr);
	if (ac == 1)
	{
		fd = open("test.cub", O_RDONLY);
		if (fd == -1)
			return (err(1));
		if (parse(fd, &res, &txr, &clr) == ERR)
			return (err(2));
	}
	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
			return (err(1));
		if (parse(fd, &res, &txr, &clr) == ERR)
			return (err(2));
	}
	close(fd);
}