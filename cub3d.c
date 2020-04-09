/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/31 16:17:39 by eassouli          #+#    #+#             */
/*   Updated: 2020/04/09 17:06:16 by eassouli         ###   ########.fr       */
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
	t_res	res;
	t_txr	txr;
	t_clr	clr;
	t_map	map;

	fd = 0;
	init(&res, &txr, &clr, &map);
	if (ac == 1)
		fd = open("test.cub", O_RDONLY);
	else if (ac == 2)
		fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (err(fd, &res, &txr, &clr, &map));
	if (parse(fd, &res, &txr, &clr, &map) == ERR)
		return (err(fd, &res, &txr, &clr, &map));
	printf("\nRES :\nwidth = %d\nheight = %d\n\nTXR :\nnorth = %s\nsouth = %s\nwest = %s\neast = %s\nsprite = %s\n\nCLR :\nfloor :\nr = %d, g = %d, b = %d\nfloor = %s\nceilng :\nr = %d, g = %d, b = %d\nceiling = %s\n", res.width, res.height, txr.north, txr.south, txr.west, txr.east, txr.sprite, clr.f_r, clr.f_g, clr.f_b, clr.floor, clr.c_r, clr.c_g, clr.c_b, clr.ceiling);
	printf("\nMAP :\no---------------------------------o -\n");
	for (int i = 0; map.map[i] != NULL; i++)
		printf("|%s| %d\n", map.map[i], i);
	printf("o---------------------------------o --\n");
	mlx_test(&res);
	close(fd);
	return (0);
}
