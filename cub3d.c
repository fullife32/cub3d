/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/31 16:17:39 by eassouli          #+#    #+#             */
/*   Updated: 2020/05/03 03:26:33 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	init(t_res *res, t_txr *txr, t_clr *clr, t_map *map)
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
	map->map = 0;
}

static int	err(int fd, t_res *res, t_txr *txr, t_clr *clr, t_map *map)
{
	write(1, "Error\n", 6);
	if (fd == -1)
		write(1, "Invalid Format\n", 15);
	else
		write(1, "Incorrect Parsing\n", 18);
	if (txr->north)
		free(txr->north);
	if (txr->south)
		free(txr->south);
	if (txr->west)
		free(txr->west);
	if (txr->east)
		free(txr->east);
	if (txr->sprite)
		free(txr->sprite);
	if (clr->floor)
		free(clr->floor);
	if (clr->ceiling)
		free(clr->ceiling);
	init(res, txr, clr, map);
	close (fd);
	return (ERR);
}

int	main(int ac, char **av)
{
	int		fd;
	// t_res	res;
	// t_txr	txr;
	// t_clr	clr;
	// t_map	map;
	t_all	all;

	fd = 0;
	init(&all.res, &all.txr, &all.clr, &all.map);
	if (ac == 1)
		fd = open("test.cub", O_RDONLY);
	else if (ac == 2)
		fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (err(fd, &all.res, &all.txr, &all.clr, &all.map));
	if (parse(fd, &all.res, &all.txr, &all.clr, &all.map, &all.plr) == ERR)
		return (err(fd, &all.res, &all.txr, &all.clr, &all.map));
	printf("\nRES :\nwidth = %d\nheight = %d\n", all.res.width, all.res.height);
	printf("\nTXR :\nnorth = %s\nsouth = %s\nwest = %s\neast = %s\nsprite = %s\n", all.txr.north, all.txr.south, all.txr.west, all.txr.east, all.txr.sprite);
	printf("\nCLR :\nfloor :\nr = %d, g = %d, b = %d\nfloor = %s\nceilng :\nr = %d, g = %d, b = %d\nceiling = %s\n", all.clr.f_r, all.clr.f_g, all.clr.f_b, all.clr.floor, all.clr.c_r, all.clr.c_g, all.clr.c_b, all.clr.ceiling);
	printf("\nMAP :\n|         10        20        30        40        50|");
	printf("\n|012345678901234567890123456789012345678901234567890|\n");
	for (int i = 0; all.map.map[i] != NULL; i++)
		printf("|%s| %d\n", all.map.map[i], i);
	raycast(&all);
	close(fd);
	return (0);
}
