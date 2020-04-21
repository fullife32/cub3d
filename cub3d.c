/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/31 16:17:39 by eassouli          #+#    #+#             */
/*   Updated: 2020/04/21 17:52:18 by eassouli         ###   ########.fr       */
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
	t_big	big;

	fd = 0;
	init(&big.res, &big.txr, &big.clr, &big.map);
	if (ac == 1)
		fd = open("test.cub", O_RDONLY);
	else if (ac == 2)
		fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (err(fd, &big.res, &big.txr, &big.clr, &big.map));
	if (parse(fd, &big.res, &big.txr, &big.clr, &big.map) == ERR)
		return (err(fd, &big.res, &big.txr, &big.clr, &big.map));
	printf("\nRES :\nwidth = %d\nheight = %d\n\nTXR :\nnorth = %s\nsouth = %s\nwest = %s\neast = %s\nsprite = %s\n\nCLR :\nfloor :\nr = %d, g = %d, b = %d\nfloor = %s\nceilng :\nr = %d, g = %d, b = %d\nceiling = %s\n", big.res.width, big.res.height, big.txr.north, big.txr.south, big.txr.west, big.txr.east, big.txr.sprite, big.clr.f_r, big.clr.f_g, big.clr.f_b, big.clr.floor, big.clr.c_r, big.clr.c_g, big.clr.c_b, big.clr.ceiling);
	printf("\nMAP :\n|0123456789012345678901234567890|\n");
	for (int i = 0; big.map.map[i] != NULL; i++)
		printf("|%s| %d\n", big.map.map[i], i);
	raycast(&big);
	close(fd);
	return (0);
}
