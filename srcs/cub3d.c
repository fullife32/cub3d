/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/31 16:17:39 by eassouli          #+#    #+#             */
/*   Updated: 2020/09/25 14:52:31 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	fp(int fd, t_txr *txr)
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
	close (fd);
	return (ERR);
}

static int	error(int fd, int error, t_a *a)
{
	if (error != ERR)
		write(1, "Error\n", 7);
	if (error == MISSING_CUB_FILE)
		write(1, ".cub file not found\n", 21);
	else if (error == NOT_CUB_FILE)
		write(1, "The last argument must be a .cub file\n", 38);
	else if (error == MLX_INIT_FAIL)
		write(1, "Initialization of MLX server failed\n", 37);
	else if (error == MUSIC_FILE_FAIL)
		write(1, "Music file name/path is incorrect\n", 35);
	if (error == ERR)
		fp(fd, &a->txr);
	return (ERR);
}

static int	cub_check(int fd, char *av, t_a *a)
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
		if ((fd = open(av, O_RDONLY)) == -1)
			return (error(fd, MISSING_CUB_FILE, a));
	}
	else
		if ((fd = -1) == ERR)
			return (error(fd, NOT_CUB_FILE, a));
	return (fd);
}

int		main(int ac, char **av)
{
	int		fd;
	t_a		a;

	fd = 0;
	if (ac < 2 || ac > 3)
		return (error(fd, MISSING_CUB_FILE, &a));
	else if (ac == 2 || ac == 3)
		fd = cub_check(fd, av[1], &a);
	if (fd == ERR)
		return (error(fd, ERR, &a));
	if (init(&a) == ERR)
		return (error(fd, MLX_INIT_FAIL, &a));
	if (parse(fd, &a) == ERR)
		return (error(fd, ERR, &a));
	// Creer fonction pour loop musiques
	// if (play_music("sounds/bfg10k.wav") == MUSIC_FILE_FAIL)
	// 	return(error(fd, MUSIC_FILE_FAIL, &a));
	// Display infos
	printf("\nRES :\nwidth = %d\nheight = %d\n", a.res.w, a.res.h);
	printf("\nTXR :\nnorth = %s\nsouth = %s\nwest = %s\neast = %s\nsprite = %s\n", a.txr.n, a.txr.s, a.txr.w, a.txr.e, a.txr.spt);
	printf("\nCLR :\nfloor :\nr = %d, g = %d, b = %d\nfloor = %s\nceilng :\nr = %d, g = %d, b = %d\nceiling = %s\n", a.txr.f_rgb / 256 / 256 % 256, a.txr.f_rgb / 256 % 256, a.txr.f_rgb % 256, a.txr.f, a.txr.c_rgb / 256 / 256 % 256, a.txr.c_rgb / 256 % 256, a.txr.c_rgb % 256, a.txr.c);
	printf("\nMAP :\n|         10        20        30        40        50|");
	printf("\n|012345678901234567890123456789012345678901234567890|\n");
	for (int i = 0; a.map.map[i] != NULL; i++)
		printf("|%s| %d\n", a.map.map[i], i);
	// Display infos
	raycast(&a);
	close(fd);
	return (0);
}
