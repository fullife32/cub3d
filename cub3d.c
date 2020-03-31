/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/31 16:17:39 by eassouli          #+#    #+#             */
/*   Updated: 2020/03/31 17:52:35 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	err(int error)
{
	write(1, "Error\n", 6);
	if (error == 1)
		write(1, "Invalid Format\n", 15);
	else if (error == 2)
		write(1, "Invalid File\n", 13);
	return (ERR);
}

int	main(int ac, char **av)
{
	int		fd;
	t_res	res;
	t_txr	txr;
	t_clr	clr;

	// if (ac == 1)
	// {
	// 	fd = 1;
	// 	if (parse(fd, &res, &txr, &clr) == ERR)
	// 		return (err(2));
	// }
	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == ERR)
			return (err(1));
		if (parse(fd, &res, &txr, &clr) == ERR)
			return (err(2));
	}
}