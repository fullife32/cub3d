/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/31 16:17:39 by eassouli          #+#    #+#             */
/*   Updated: 2020/05/26 17:31:56 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	fp(int fd, t_txr *txr, t_a *a)
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
	init(a);
	close (fd);
	return (ERR);
}

static int	error(int fd, int error, t_a *a)
{
	if (error != ERR)
		write(1, "Error\n", 7);
	if (error == MISSING_CUB_FILE_ERR)
		write(1, "Missing .cub file\n", 19);
	else if (error == NOT_CUB_FILE_ERR)
		write(1, "The second argument must be a .cub file\n", 41);
	if (error == ERR)
		fp(fd, &a->txr, a);
	return (ERR);
}

static int	cub_check(char *av)
{
	int	i;
	int	j;
	int	fd;

	i = 0;
	j = 3;
	while (av[i])
		i++;
	i--;
	while (av[i--] == CUB[j] && j != -1)
		j--;
	if (j == -1)
		fd = open(av, O_RDONLY);
	else
		fd = -1;
	return (fd);
}

int		main(int ac, char **av)
{
	int		fd;
	t_a		a;

	fd = 0;
	init(&a);
	if (ac < 2)
		return (error(fd, MISSING_CUB_FILE_ERR, &a));
	else if (ac == 2)
		fd = cub_check(av[1]);
	if (fd == -1)
		return (error(fd, NOT_CUB_FILE_ERR, &a));
	if (parse(fd, &a) == ERR)
		return (error(fd, ERR, &a));
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
