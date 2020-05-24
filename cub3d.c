/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/31 16:17:39 by eassouli          #+#    #+#             */
/*   Updated: 2020/05/24 18:18:29 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	init(t_all *all)
{
	all->res.h = 0;
	all->res.w = 0;
	all->txr.f_rgb = -1;
	all->txr.c_rgb = -1;
	all->txr.n = 0;
	all->txr.s = 0;
	all->txr.w = 0;
	all->txr.e = 0;
	all->txr.spt = 0;
	all->txr.f = 0;
	all->txr.c = 0;
	all->map.map = 0;
	all->dir.plane_y = 0;
	all->dir.plane_x = 0.66;
	all->mlx.frame_time = 0.004;
	all->plr.move_spd = all->mlx.frame_time * 5.0;
	all->plr.rot_spd = all->mlx.frame_time * 3.0;
	all->mov.mov[FW] = FALSE;
	all->mov.mov[BW] = FALSE;
	all->mov.mov[L] = FALSE;
	all->mov.mov[R] = FALSE;
	all->mov.mov[LR] = FALSE;
	all->mov.mov[RR] = FALSE;
	all->mov.mov[RUN] = FALSE;
}

static int	err(int fd, t_txr *txr, t_all *all)
{
	if (txr->n)
		free(txr->n);
	if (txr->s)
		free(txr->s);
	if (txr->w)
		free(txr->w);
	if (txr->e)
		free(txr->e);
	if (txr->spt)
		free(txr->spt);
	if (txr->f)
		free(txr->f);
	if (txr->c)
		free(txr->c);
	init(all);
	close (fd);
	return (ERR);
}

int		main(int ac, char **av)
{
	int		fd;
	t_all	all;

	fd = 0;
	init(&all);
	if (ac == 1)
		fd = open("test.cub", O_RDONLY);
	else if (ac == 2)
		fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (err(fd, &all.txr, &all));
	if (parse(fd, &all.res, &all.txr, &all.map, &all.plr) == ERR)
		return (err(fd, &all.txr, &all));
	// Display infos
	printf("\nRES :\nwidth = %d\nheight = %d\n", all.res.w, all.res.h);
	printf("\nTXR :\nnorth = %s\nsouth = %s\nwest = %s\neast = %s\nsprite = %s\n", all.txr.n, all.txr.s, all.txr.w, all.txr.e, all.txr.spt);
	printf("\nCLR :\nfloor :\nr = %d, g = %d, b = %d\nfloor = %s\nceilng :\nr = %d, g = %d, b = %d\nceiling = %s\n", all.txr.f_rgb / 256 / 256 % 256, all.txr.f_rgb / 256 % 256, all.txr.f_rgb % 256, all.txr.f, all.txr.c_rgb / 256 / 256 % 256, all.txr.c_rgb / 256 % 256, all.txr.c_rgb % 256, all.txr.c);
	printf("\nMAP :\n|         10        20        30        40        50|");
	printf("\n|012345678901234567890123456789012345678901234567890|\n");
	for (int i = 0; all.map.map[i] != NULL; i++)
		printf("|%s| %d\n", all.map.map[i], i);
	// Display infos
	raycast(&all);
	close(fd);
	return (0);
}
