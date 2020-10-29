/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/31 16:17:39 by eassouli          #+#    #+#             */
/*   Updated: 2020/10/29 16:30:38 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	fp(int fd, t_txr *txr)
{
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
	if (txr->floor)
		free(txr->floor);
	if (txr->ceiling)
		free(txr->ceiling);
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

int		save_check(char *av, t_a *a)
{
	int	i;

	i = 0;
	while (SAVE[i] && av[i])
	{
		if (SAVE[i] != av[i])
			return (BMP_FAIL);
		i++;
	}
	if (rec_bmp_h(a) != OK)
		return (BMP_FAIL);
	return (OK);
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
	if (ac == 3)
	{
		if ((save_check(av[2], &a)) != OK)
			return (BMP_FAIL);
	}
	// Creer fonction pour loop musiques
	if (play_music() == MUSIC_FILE_FAIL)
		return(error(fd, MUSIC_FILE_FAIL, &a));

	// Display infos
	printf("\nRES :\nwidth = %d\nheight = %d\n", a.res.w, a.res.h);
	printf("\nTXR :\nnorth = %s\nsouth = %s\nwest = %s\neast = %s\nsprite = %s\n", a.txr.north, a.txr.south, a.txr.west, a.txr.east, a.txr.sprite);
	printf("\nCLR :\nfloor :\nr = %d, g = %d, b = %d\nfloor = %s\nceilng :\nr = %d, g = %d, b = %d\nceiling = %s\n", a.txr.f_rgb / 256 / 256 % 256, a.txr.f_rgb / 256 % 256, a.txr.f_rgb % 256, a.txr.floor, a.txr.c_rgb / 256 / 256 % 256, a.txr.c_rgb / 256 % 256, a.txr.c_rgb % 256, a.txr.ceiling);
	printf("\nMAP :\n|         10        20        30        40        50|");
	printf("\n|012345678901234567890123456789012345678901234567890|\n");
	for (int i = 0; a.map.map[i] != NULL; i++)
		printf("|%s| %d\n", a.map.map[i], i);
	// Display infos
	raycast(&a);
	mlx_hook(&a.mlx.win, 2, (1L<<0), key_press, &a);
	mlx_hook(&a.mlx.win, 3, (1L<<1), key_release, &a);
	mlx_hook(&a.mlx.win, 17, (1L<<5), destroy, &a); // voir macro (peut etre)
	mlx_hook(&a.mlx.win, STRUCTURE_NOTIFY_CODE, STRUCTURE_NOTIFY_MASK, destroy, &a);
	mlx_loop_hook(&a.mlx.ptr, rc_loop, &a);
	mlx_loop(&a.mlx.ptr);
	close(fd);
	return (0);
}
