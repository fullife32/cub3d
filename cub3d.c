/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/31 16:17:39 by eassouli          #+#    #+#             */
/*   Updated: 2020/04/04 00:42:05 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	init(t_res *res, t_txr *txr, t_clr *clr)
{
	res->height = 0;
	res->width = 0;
	txr->north = 0;
	txr->south = 0;
	txr->west = 0;
	txr->east = 0;
	txr->sprite = 0;
	clr->c_b = -1;
	clr->c_g = -1;
	clr->c_r = -1;
	clr->f_b = -1;
	clr->f_g = -1;
	clr->f_r = -1;
	clr->floor = 0;
	clr->ceiling = 0;
}

int	err(int error, t_res *res, t_txr *txr, t_clr *clr)
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

	init(&res, &txr, &clr);
	if (ac == 1)
	{
		fd = open("test.cub", O_RDONLY);
		if (fd == -1)
			return (err(1));
		if (parse(fd, &res, &txr, &clr) == ERR)
			return (err(2, &res, &txr, &clr));
	}
	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
			return (err(1));
		if (parse(fd, &res, &txr, &clr) == ERR)
			return (err(2, &res, &txr, &clr));
	}
	printf("\nRES :\nwidth = %d\nheight = %d\n\nTXR :\nnorth = %s\nsouth = %s\nwest = %s\neast = %s\nsprite = %s\n\nCLR :\nfloor :\nr = %d, g = %d, b = %d\nfloor = %s\nceilng :\nr = %d, g = %d, b = %d\nceiling = %s\n", res.width, res.height, txr.north, txr.south, txr.west, txr.east, txr.sprite, clr.f_r, clr.f_g, clr.f_b, clr.floor, clr.c_r, clr.c_g, clr.c_b, clr.ceiling);
	close(fd);
}